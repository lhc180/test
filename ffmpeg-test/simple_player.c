#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

int main(int argc, char *argv[])
{
	AVFormatContext *pFormatCtx;
	int i, videoStream;
	AVCodecContext *pCodecCtx;
	AVCodec *pCodec;
	AVFrame *pFrame;
	AVFrame *pFrameRGB;
	AVPacket packet;

	int frameFinished = 0;
	int numBytes;
	uint8_t *buffer;
	struct SwsContext *pSwsCtx;

	av_register_all();
	const char *filename = "";

	pFormatCtx = avformat_alloc_context();
	if(avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0)
		return -1;
	if(avformat_find_stream_info(pFormatCtx, NULL) < 0)
		return -1;
	av_dump_format(pFormatCtx, 0, filename, 0);

	videoStream = -1;
	for(i = 0; i < pFormatCtx->nb_streams; i++){
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO){
			videoStream = i;
			break;
		}
	}

	if(videoStream == -1)
		return -1;

	pCodecCtx = pFormatCtx->streams[videoStream]->codec;

	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

	if(pCodec == NULL) {
		fprintf(stderr, "Unsupported codec!\n");
		return -1;
	}

	if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
		return -1;

	pFrame = avcodec_alloc_frame();
	pFrameRGB = avcodec_alloc_frame();

	if(pFrameRGB == NULL)
		return -1;
	
	numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

	buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

	avpicture_fill((AVPicture *)pFrameRGB, buffer, PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

	while(av_read_frame(pFormatCtx, &packet) >= 0)
	{
		if(packet.stream_index == videoStream)
		{
			pFrame = avcodec_alloc_frame();
			int w = pCodecCtx->width;
			int h = pCodecCtx->height;

			avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
			pSwsCtx = sws_getContext(w, h, pCodecCtx->pix_fmt, w, h, PIX_FMT_RGB565, SWS_POINT, NULL, NULL, NULL);
			
			if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
			{
				fprintf(stderr, "Could not initialize SDL -%s\n", SDL_GetError());
				exit(1);
			}

			SDL_Surface *screen;
			screen = SDL_SetVideoMode(pCodecCtx->width, pCodecCtx->height, 0, 0);
			if(!screen)
			{
				fprintf(stderr, "SDL: could not set video mode - exiting\n");
				exit(1);
			}

			SDL_Overlay *bmp;
			bmp = SDL_CreateYUVOverlay(pCodecCtx->width, pCodecCtx->height, SDL_YV12_OVERLAY, screen);
			SDL_Rect rect;
			if(frameFinished)
			{
				SDL_LockYUVOverlay(bmp);
				AVPicture pict;
				pict.data[0] = bmp->pixels[0];
				pict.data[1] = bmp->pixels[1];
				pict.data[2] = bmp->pixels[2];

				pict.linesize[0] = bmp->pitches[0];
				pict.linesize[1] = bmp->pitches[1];
				pict.linesize[2] = bmp->pitches[2];

				img_convert(&pict, PIX_FMT_YUV420P, (AVPicture *)pFrame, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height);
				SDL_DisplayYUVOverlay(bmp, &rect);
			}

			SDL_Event event;
			av_free_packet(&packet);
			SDL_PollEvent(&event);
			switch (event.type){
				case SDL_QUIT:
					SDL_Quit();
					exit(0);
					break;
				default:
					break;
			
			}

		}
	}

	av_free(buffer);
	av_free(pFrameRGB);
	av_free(pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);

	return 0;
}

int img_convert(AVPicture *dst, enum PixelFormat dst_pix_fmt, const AVPicture *src, enum PixelFormat src_pix_fmt, int src_width, int src_height)
{
	int w;
	int h;
	struct SwsContext *pSwsCtx;

	w = src_width;
	h = src_height;
	pSwsCtx = sws_getContext(w, h ,src_pix_fmt, w, h, dst_pix_fmt, SWS_BICUBIC, NULL, NULL, NULL);
	sws_scale(pSwsCtx, (const uint8_t *const*)src->data, src->linesize, 0, h, dst->data, dst->linesize);

	return 0;
}

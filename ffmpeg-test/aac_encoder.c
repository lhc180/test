/*
	@LIDE
	aac encoder
	2015.3.6
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <libavutil/opt.h>
#include <libavutil/mathematics.h>
#include <libavformat/avformat.h>

#define DEBUG 0
#ifdef  DEBUG
#define lide_printf printf
#else
#define lide_printf(fmt...)
#endif


FILE* fp_in = NULL;
FILE* fp_out = NULL;

static int frame_count;

int main(int argc, char **argv)
{
	int ret;
	AVCodec *audio_codec;
	AVCodecContext *c;
	AVFrame *frame;
	AVPacket pkt;
	int got_output;

	av_register_all();
	avcodec_register_all();

	audio_codec = avcodec_find_encoder(AV_CODEC_ID_AAC);
	c = avcodec_alloc_context3(audio_codec);

	c->codec_id = AV_CODEC_ID_AAC;
	c->sample_fmt = AV_SAMPLE_FMT_S16;
	c->sample_rate = 44100;
	c->channels = 2;
	c->channel_layout = AV_CH_LAYOUT_STEREO;
//	c->bit_rate = 6400;


	ret = avcodec_open2(c, audio_codec, NULL);
	if(ret < 0) {
		fprintf(stderr, "Could not open video codec: %s\n", av_err2str(ret));
		exit(1);
	}


	frame = avcodec_alloc_frame();
	frame->format = c->sample_fmt;
	frame->channels = c->channels;
	frame->channel_layout = c->channel_layout;
	frame->linesize[0] = 4096;
	frame->extended_data = frame->data[0] = av_malloc((size_t)frame->linesize[0]);

	av_init_packet(&pkt);

//	fp_in = fopen("nibawoguanzui-dengziqi.wav", "rb");
	fp_in = fopen("live.wav", "rb");
	fp_out = fopen("out.aac", "wb");

	while(1)
	{
		frame_count++;
		bzero(frame->data[0], frame->linesize[0]);
		ret = fread(frame->data[0], frame->linesize[0], 1, fp_in);
		if(ret <= 0)
		{
			printf("read over!\n");
			break;
		}

		ret = avcodec_encode_audio2(c, &pkt, frame, &got_output);

		if(ret < 0)
		{
			fprintf(stderr, "Error encoding audio frame: %s\n", av_err2str(ret));
			exit(1);
		}
	
		if(got_output > 0)
		{
			lide_printf("data: %p, size: %d\n", pkt.data, pkt.size);
			fwrite(pkt.data, pkt.size, 1, fp_out);
			av_free_packet(&pkt);
		}
	}

	avcodec_close(c);
	av_free(c);
	avcodec_free_frame(&frame);

	fclose(fp_in);
	fclose(fp_out);

	return 0;

}

#include <gst/gst.h>
int main (int argc, char *argv[])
{
	GMainLoop *loop;
	GstElement *pipeline, *filesrc, *decoder, *audiosink;

	gst_init(&argc, &argv);
	loop = g_main_loop_new(NULL,FALSE);//创建主循环，在执行 g_main_loop_run后正式开始循环

	if (argc != 2) {
		g_print ("usage: %s <mp3 filename>\n", argv[0]);
		exit (-1);
	}
	/* 创建一条新的管道 */
	pipeline = gst_pipeline_new ("pipeline");
	/* 生成用于读取硬盘数据的元件 */
	filesrc = gst_element_factory_make ("filesrc", "disk_source");
	g_object_set (G_OBJECT (filesrc), "location", argv[1], NULL);
	/* 创建解码器元件 */
	decoder = gst_element_factory_make ("mad", "decoder");
	/* 创建音频回放元件 */
	audiosink = gst_element_factory_make ("appsink", "play_audio");
	/* 将生成的元件添加到管道中 */
	gst_bin_add_many (GST_BIN (pipeline), filesrc, decoder, audiosink, NULL);
	/* 连接各个元件 */
	gst_element_link_many (filesrc, decoder, audiosink, NULL);
	/* 开始播放 */
	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	g_main_loop_run(loop);
	/* 停止管道处理流程 */
	gst_element_set_state (pipeline, GST_STATE_NULL);
	/* 释放占用的资源 */
	gst_object_unref (GST_OBJECT (pipeline));
	exit (0);
}

#include <gst/gst.h>

int main()
{
	GMainLoop *loop;
	GError *error = NULL;

	GstBus *bus;
	GstElement *pipe;

	gst_init(NULL, NULL);
	loop = g_main_loop_new(NULL,FALSE);

	char * caps;
	char *pipeline;
	//sprintf(caps, "");
//	pipeline = getenv("GST_REGISTRY_UPDATE");
	sprintf(pipeline, "playbin2 uri=file:///home/lucid/work/test/gstreamer/夜空中最亮的星.mp3");


	pipe = gst_parse_launch(pipeline, &error);

	bus = gst_element_get_bus (pipe);
	gst_element_set_state(pipe, GST_STATE_PLAYING);
	g_main_loop_run(loop);
	gst_element_set_state (pipe, GST_STATE_NULL);
	gst_object_unref (GST_OBJECT (pipe));

}

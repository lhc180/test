#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>

int main()
{
	char * ch = (char*)malloc(256);
	g_print("GLib version: %d.%d.%d\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);
	g_log(G_LOG_DOMAIN, G_LOG_LEVEL_MESSAGE, "GLib version: %d.%d.%d\n", GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION);

	GSList *list	=	NULL;
	g_mem_set_vtable(glib_mem_profiler_table);
	g_atexit(g_mem_profile);
	list	=	(GSList*)g_malloc(sizeof(GSList));
	list->next	=	(GSList*)g_malloc(sizeof(GSList));

	g_free(list->next);

	return 0;
}

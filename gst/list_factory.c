#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElementFactory *factory;
	GList	*plug_list;
	GstRegistry *registry;
	gst_init(&argc, &argv);

	registry = gst_registry_get_default();
	plug_list = gst_registry_get_plugin_list(registry);
	while(plug_list != NULL)
	{
		printf("%d : %s \n", i, plug_list->

	return 0;
}

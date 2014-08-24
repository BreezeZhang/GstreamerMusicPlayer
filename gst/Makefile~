AS	=gas
LD	=gld
CC	=gcc
CFLAGS	=

all:	gst_play
gst_play:	gst_play.o
	$(LD)  -L /root/gstreamer_lib_for_x86/lib -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgthread-2.0 
gst_play.o:	gst_play.c
 	$(CC) gcc gst_play.c -I /root/gstreamer_lib_for_x86/include/glib-2.0  -I /root/gstreamer_lib_for_x86/include -I /root/gstreamer_lib_for_x86/lib/glib-2.0/include -I  /root/gstreamer_lib_for_x86/include/gstreamer-0.10  -L /root/gstreamer_lib_for_x86/lib -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgthread-2.0 -o gst_play

gcc gst_play.c -I /root/gstreamer_lib_for_x86/include/glib-2.0  -I /root/gstreamer_lib_for_x86/include -I /root/gstreamer_lib_for_x86/lib/glib-2.0/include -I  /root/gstreamer_lib_for_x86/include/gstreamer-0.10  -L /root/gstreamer_lib_for_x86/lib -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgthread-2.0 -L /root/gstreamer_lib_for_x86/lib/gstreamer-0.10 -lgstmad -o gst_play 

arm-linux-gcc gst_play.c -I /root/gstreamer_lib_for_arm/include/glib-2.0  -I /root/gstreamer_lib_for_arm/include -I /root/gstreamer_lib_for_arm/lib/glib-2.0/include -I  /root/gstreamer_lib_for_arm/include/gstreamer-0.10  -L /root/gstreamer_lib_for_arm/lib -lgstreamer-0.10 -lglib-2.0 -lgmodule-2.0 -lgobject-2.0 -lgthread-2.0 -L /root/gstreamer_lib_for_arm/lib/gstreamer-0.10 -lgstmad -o gst_play_arm

	

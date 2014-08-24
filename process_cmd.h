#ifndef __PROCESS_CMD_H__
#define __PROCESS_CMD_H__
#include "mmplay.h"

#ifndef GST_PLAY_FILE 
#define	GST_PLAY_FILE	"/root/work/gst2/source/gst_play"
#endif

void prog_cmd_process(cmd_t cmd, int shmid, struct share_info *share);
	
#endif

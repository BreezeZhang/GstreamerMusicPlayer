#ifndef	__MMPLAY_H__
#define __MMPLAY_H__

#include "util.h"


#define SHM_ID	3


/*** share child*********/
struct share_info{
	pid_t	gst_pid;
	pid_t	child_pid;
	char	s_name[MAX_LEN];
};
/***share child end *********/

#endif

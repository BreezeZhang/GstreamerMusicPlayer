#ifndef __UTIL_H__
#define __UTIL_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

#define FTOK_FILE "util.h"
#define FTOK_ID	7
#define SHM_LEN	64
#define	SHM_MODE	S_IRUSR|S_IWUSR		//0666

#ifndef MAX_LEN
#define MAX_LEN	1024 
#endif 

typedef	int	cmd_t;

struct shm_cmd
{
	cmd_t	cmd;
	pid_t	pid;
	char cmd_text[SHM_LEN];
};


/*************************cmd macro*****************/
#define	PLAY	1
#define	PAUSE	2
#define	EXIT	3	
#define PREV	4	
#define	NEXT	5
#define	CONTINUE	6
#define ADD_VOLUME	16
#define	DEC_VOLUME	17
#define	OTHER	-1
#define INVALID_CMD	0
/************************cmd macro end*****************/

#define  err_msg(MSG)	{	\
		perror(MSG);	\
		DPRINT("");	\
		exit(errno);	\
}

#define DEBUG_ENABLE 
#ifdef DEBUG_ENABLE
#define DPRINT(info)	do{	\
	printf("Info : File = %s, Line = %d, Info = %s\n",\
			__FILE__, __LINE__, info);	\
}while(0)

#define	DPRINTD(INFO, num)	do{	\
	printf(INFO"%d\n", num);	\
}while(0)

#define DPRINTS(INFO, info)	do{	\
	printf(INFO"%s\n", info);	\
}while(0)

#else
#define	DPRINT(info)
#endif

#endif

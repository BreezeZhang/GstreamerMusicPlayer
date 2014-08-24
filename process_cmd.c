#include "process_cmd.h"
#include "list.h"

extern struct s_list* s_head;
/***-----default loop play -----******/
static volume = 0;
int play_audio(int shmid, struct share_info *share)
{
	int exit_status;
	pid_t pid;
	struct s_list *cur_node;
	
	cur_node = find_node(s_head, share->s_name);

	if((pid=fork()) < 0)
		err_msg("play audio fork() error");
	if(pid == 0)
	{
		while(1)
		{
			if((pid = fork()) < 0)
				err_msg("create thread failed");
			if(pid == 0)
			{
				printf("pid = %d", getpid());
				DPRINT("gst_play start pid ");
				gst_play(shmid);
			}
			else{
				share->child_pid = pid;
				wait(&exit_status);
				if(exit_status == 0)
				{
					cur_node = cur_node->next;
					strcpy(share->s_name, cur_node->name);
				}
				DPRINTD("------------- exit_status is ", exit_status);
			}
		}
	}
	return 0;
}

int play_next(int shmid, struct	share_info *share)
{
	struct s_list*	cur_node;
	cur_node = find_node(s_head, share->s_name);
	strcpy(share->s_name, cur_node->next->name);
	kill(share->gst_pid, SIGKILL);
	return 0;
}

int play_prev(int shmid, struct	share_info *share)
{
	struct s_list*	cur_node;
	cur_node = find_node(s_head, share->s_name);
	strcpy(share->s_name, cur_node->prev->name);
	kill(share->gst_pid, SIGKILL);
	return 0;
}
int pause_audio(int shmid, struct	share_info *share)
{
	kill(share->gst_pid, SIGSTOP);
	return 0;
}
int continue_audio(int shmid, struct	share_info *share)
{
	kill(share->gst_pid, SIGCONT);
	return 0;
}

int add_volume(int shmid, struct share_info *share)
{
	volume++;
	kill(share->gst_pid, SIGUSR1);
	return 0;
}
int dec_volume(int shmid, struct share_info *share)
{
	volume--;
	kill(share->gst_pid, SIGUSR2);
	return 0;
}
int gst_play(int shmid)
{
	struct share_info *share;
	if((share = (struct share_info*)shmat(shmid, 0, 0)) == (void *)-1)
	{
		shmctl(shmid, IPC_RMID, NULL);
		err_msg("shmat error");
	}
	share->gst_pid = getpid();
	char name[MAX_LEN]; 
	printf("info: %d, %s\n", getpid(), share->s_name);
	strcpy(name, share->s_name);
	if(execlp(GST_PLAY_FILE, "gst_play", name, NULL) < 0)
	   err_msg("execlp error");	
	return 0;
}

static	struct {
	cmd_t	cmd;
	int	(*handler)(int shmid, struct share_info *share);
} cmd_handler_tbl[] = {
	PLAY, play_audio,
	NEXT, play_next,
	PREV, play_prev,
	PAUSE, pause_audio,
	CONTINUE, continue_audio,
	ADD_VOLUME, add_volume,
	DEC_VOLUME, dec_volume,
};	

void prog_cmd_process(cmd_t cmd, int shmid, struct share_info* share)
{
	DPRINT(" START prog_cmd_process");
	int i = 0;	
	for(i = 0; i < sizeof(cmd_handler_tbl) / sizeof(cmd_handler_tbl[0]); i++)
	{
		if(cmd == cmd_handler_tbl[i].cmd && cmd_handler_tbl[i].handler)
		{
			cmd_handler_tbl[i].handler(shmid, share);
		}
	}
}

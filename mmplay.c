#include "mmplay.h"
#include "parase_file.h"
#include "process_cmd.h"

static void sig_cmd(int);

static int cmd	= INVALID_CMD;
static struct shm_cmd *cmd_ds;

struct s_list *s_head;

int main(int argc, char *argv[])
{
	int		nadd;
	key_t	key;
	key_t	key2;
 	int		shmid = 0;
	int		shmid2 = 0;
	struct	share_info *share;
	struct	s_list *add_list = NULL;
	struct s_list *cur_node;
	s_head = NULL;

	if(argc != 2)
	{
		printf("Usag: mmplay dir path\n");
		exit(1);
	}
	if(signal(SIGUSR1, sig_cmd) == SIG_ERR)
		err_msg("can't catch SIGUSR1 ");

	if((key=ftok(FTOK_FILE, FTOK_ID)) == -1)
		err_msg("ftok error");
	printf("mmplay key = %d\n", key);
	if((shmid=shmget(key, sizeof(struct shm_cmd),IPC_CREAT|IPC_EXCL|SHM_MODE)) == -1)
		err_msg("shmget cmd error");
	if((cmd_ds=shmat(shmid, 0, 0)) == (void *)-1)
	{
		perror("shmat");
		if (shmctl(shmid, IPC_RMID, NULL) == -1)
			perror("Failed to  remove memory segment");
		err_msg("shmat error");
	}
	/* save mmplay pid to cmd_ds, for other user send cmd*/
	cmd_ds->pid = getpid();

	if((key2=ftok(FTOK_FILE, SHM_ID) == -1))
		err_msg("ftok error");
	if((shmid2=shmget(key2, sizeof(struct shm_cmd),IPC_CREAT|IPC_EXCL|SHM_MODE)) == -1)
		err_msg("shmget cmd error");
	if((share=shmat(shmid2, 0, 0)) == (void *)-1)
	{
		perror("shmat");
		if (shmctl(shmid2, IPC_RMID, NULL) == -1)
			perror("Failed to  remove memory segment");
		err_msg("shmat error");
	}

	DPRINT("parase_path");	
	if((nadd=parase_path(argv[1], &add_list)) == -1)
	{
		err_msg("parase_dir error");
	}

	s_head = link_list(s_head, add_list);
	DPRINT("STRAR print_music_list");
	print_music_list(s_head);
	cur_node = s_head;
	strcpy(share->s_name, cur_node->name);

	/**** play audio ****/
	for( ; ; )
	{
		pause();
		prog_cmd_process(cmd, shmid2, share);
		printf("wait a signal others, is a cmd？\n");
	}

	
	return 0;
}

static void sig_cmd(int	signal)
{
	if(signal == SIGUSR1)
	{
		cmd = cmd_ds->cmd;
		cmd_ds->cmd = INVALID_CMD;
	}
	else
	{
		printf("received signal %d\n", signal);
		err_msg("signal error");
	}
}

#include "util.h"

int main()
{
	int cmd;
	int shmid;
	key_t	key;
	int n;
	struct shm_cmd *share;

	if((key = ftok(FTOK_FILE, FTOK_ID)) == -1)
		err_msg("ftokk error");
	printf("key = %x\n", key);
	if((shmid=shmget(key, sizeof(struct shm_cmd), SHM_MODE)) == -1)
		err_msg("shmget error");
	if((share = shmat(shmid, 0, 0)) == (void *)-1)
		err_msg("shmat error");

	printf("xxxxxxxxxxxxxxxxx     cmd    prompt		xxxxxxxxxxxxxxxxx\n");
	printf("\n\n  1---PLAY				2---PAUSE\n");
	printf("\n\n  3---EXIT				4---PREV\n");
	printf("\n\n  5---NEXT				6---CONT\n");
	printf("\n\n  7---ADD_VOLUME		8---DEC VOLUME");
	
	while(1)
	{
		printf("Please input your cmd: ");
		scanf("%d", &n);
		switch(n)
		{
			case 1:
				share->cmd = PLAY;
				break;
			case 2:
				share->cmd = PAUSE;
				break;
			case 3:
				share->cmd = EXIT;
				break;
			case 4:
				share->cmd = PREV;
				break;
			case 5:
				share->cmd = NEXT;
				break;
			case 6:
				share->cmd = CONTINUE;
				break;
			case 7:
				share->cmd = ADD_VOLUME;
				break;
			case 8:
				share->cmd = DEC_VOLUME;
				break;
			default:
				continue;
		}	
		kill(share->pid, SIGUSR1);
		printf("cmd had send\n");
	}

}	

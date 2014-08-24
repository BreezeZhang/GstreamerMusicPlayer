#include "parase_file.h"
#include <dirent.h>

int is_music_file(char *path)
{
	char *ans;
	ans = strrchr(path, '.');
	if(ans == NULL)
		return 0;
	if(strcmp(++ans, "mp3") == 0)
		return 1;
	return 0;
}

/* can't do */
int parase_dir(char *path, struct s_list **tmp_list)
{
	DIR *db;
	struct dirent *dir_info;
	char name[MAX_LEN];
	int num = 0;

	db = opendir(path);
	if(NULL == db)
		err_msg("open dir failed");

	while((dir_info = readdir(db)))
	{
		if((strcmp(dir_info->d_name, ".") == 0) || (strcmp(dir_info->d_name, "..") == 0))
			continue;
		else
		{
			sprintf(name, "%s/%s", path, dir_info->d_name);
			if(is_music_file(name))
			{
				if(*tmp_list == NULL)
				{
					*tmp_list = (struct s_list *)malloc(sizeof(struct s_list));
					if(!(*tmp_list))
						err_msg("malloc tmp_list failed");
					strcpy((*tmp_list)->name, name);
					(*tmp_list)->prev = *tmp_list;
					(*tmp_list)->next = *tmp_list;
					continue;
				}
				if(add_inode((*tmp_list)->prev, name) == -1)
					err_msg("add_inode failed");
				num++;
			}
		}
	}
	closedir(db);
	return num;
}

int parase_path(char *path, struct s_list **tmp_list)
{
	struct stat file_stat;
	if(lstat(path, &file_stat) == -1)
		err_msg("lstat error");
	if( S_ISREG(file_stat.st_mode) )
	{
		DPRINT("is_music_file");
		if(is_music_file(path))
		{
			if(*tmp_list == NULL)
			{
				*tmp_list = (struct s_list *)malloc(sizeof(struct s_list));
				if(!*tmp_list)
					err_msg("malloc tmp_list failed");
				strcpy((*tmp_list)->name, path);
				(*tmp_list)->prev = *tmp_list;
				(*tmp_list)->next = *tmp_list;
				return 1;
			}
			/*-------------error code---------------*/
			DPRINT("add_inode");
			if(add_inode((*tmp_list)->prev, path) == -1)
				err_msg("add_inode failed");
			return 1;
			/*-------------error code---------------*/
		}
		else
		{
			printf("it is not a music file, or not support\n");
			exit(1);
		}
	}
	else if(S_ISDIR(file_stat.st_mode))
	{
		DPRINT("parase_dir");
		return parase_dir(path, tmp_list);
	}
	else
	{
		printf("Usage: mmplay file, file mode must dir or regular");
		exit(2);
	}
}
			

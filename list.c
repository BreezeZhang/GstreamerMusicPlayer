#include "list.h"
#include "util.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

int add_inode(struct s_list *prev_inode, char *name)
{
	struct s_list *add_inode;
	add_inode = (struct s_list *)malloc(sizeof(struct s_list));
	if(!add_inode)
	{
		printf("malloc s_list failed\n");
		return (-1);
	}
	strcpy(add_inode->name, name);
	DPRINT("In add_inode");
	prev_inode->next->prev = add_inode;
	add_inode->next = prev_inode->next;
	add_inode->prev = prev_inode;
	prev_inode->next = add_inode;
	DPRINT("Out add_inode");
	
	return 0;
}

struct s_list* find_node(struct s_list * head, char *name)
{
	struct s_list *tmp;
	tmp = head;
	do{
		if(!strcmp(tmp->name, name))
			return tmp;
	}while((tmp = tmp->next) != head);
	return NULL;
}

struct s_list* link_list(struct s_list *head, struct s_list* add_list)
{
	if(!head && !add_list)
		return NULL;
	if(!head)
		return add_list;
	if(!add_list)
		return head;
	head->prev->next = add_list;
	head->prev = add_list->prev->next;
	add_list->prev->next = head;
	add_list->prev = head->prev;
	
	return head;
}
	
void print_music_list(struct s_list *s_head)
{
	if(s_head == NULL)
	{
		printf("no music added\n");
		return;
	}
	struct s_list *inode = s_head;
	do{
		printf("%s\n", inode->name);
		inode = inode->next;
	}while(inode != s_head);
}

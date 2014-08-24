#ifndef	__LIST_H
#define	__LIST_H

#ifndef MAX_LEN
#define MAX_LEN	1024
#endif
struct s_list{
	char	name[MAX_LEN];
	struct	s_list	*next;
	struct	s_list	*prev;
};

int add_inode(struct s_list *prev_inode, char *name);	
struct s_list* find_node(struct s_list *head, char *name);
struct s_list* link_list(struct s_list *head, struct s_list *add_list); 
void print_music_list(struct s_list *s_head);


#endif

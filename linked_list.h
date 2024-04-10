#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value);
node_t *find_entry(node_t *head, int value);
void remove_entry(node_t **head, node_t *entry);
void swap_pair(node_t **head);
void reverse(node_t **head);
void print_list(node_t *head);
void delete_list(node_t **head);

#endif

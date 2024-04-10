#include "linked_list.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
 * add_entry - add a new entry to tail
 * @head: list head to add it before
 * @new_value: new value for assigning to new entry
 *
 * Insert a new entry before the specific head.
 *
 * Create a new entry and assign new_value to it.
 * Traverse the entire list until reaching the last node whose next pointer
 * is NULL.
 * Set the next pointer of the last node to new_node.
 */
void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    /*
     * In the long run, you'd really want a proper unit testing framework
     * for this kind of thing instead of assert
     * but it's useful as a temporary debugging tool
     */
    assert(new_node);

    new_node->value = new_value;
    new_node->next = NULL;

    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

/*
 * find_entry -  find an entry in the list
 * @head: list head to start the search from
 * @value: value to search for in the list
 *
 * Traverse the list until either the value is found
 * or the end of the list is reached.
 */
node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

/*
 * remove_entry - remove an entry from the list
 * @head: list head
 * @entry: entry to be removed
 *
 * Traverse the list until the specified entry is found,
 * re-linking the previous node's next pointer to the next node,
 * then free its memory.
 */
void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

/*
 * swap_pair - replace the position of each two pairs of entries
 * @head: list head
 *
 * Description:
 *  node_t **node = &head;      // a(*node) -> b -> c -> d
 *  node_t *tmp = *node;        // a(*node, tmp) -> b -> c -> d
 *  *node = (*node)->next;      // a(tmp) -> b(*node) -> c -> d
 *  tmp->next = (*node)->next;  // a(tmp) -> c, b(*node) -> c -> d
 *  (*node)->next = tmp;        // b(*node) -> a(tmp) -> c -> d
 */
void swap_pair(node_t **head)
{
    for (; *head && (*head)->next; head = &(*head)->next->next) {
        node_t *tmp = *head;
        *head = (*head)->next;
        tmp->next = (*head)->next;
        (*head)->next = tmp;
    }
}

/*
 * reverse - reverse the sequence of the list
 * @head: list head
 *
 * Description:
 *  node_t *next = head->next;  // a(head) -> b(next) -> c -> d
 *  head->next = cursor;        // a(head) -> cursor(NULL), b(next) -> c -> d
 *  cursor = head;              // a(head, cursor) -> NULL, b(next) -> c -> d
 *  head = next;                // a(cursor) -> NULL, b(next, head) -> c -> d
 * Next round:
 *  node_t *next = head->next;  // a(cursor) -> NULL, b(head) -> c(next) -> d
 *  head->next = cursor;        // b(head) -> a(cusor) -> NULL, c(next) -> d
 *  cursor = head;              // b(head, cursor) -> a -> NULL, c(next) -> d
 *  head = next;                // b(cursor) -> a -> NULL, c(next, head) -> d
 */
void reverse(node_t **head)
{
    node_t *cursor = NULL;
    while (*head) {
        node_t *next = (*head)->next;
        (*head)->next = cursor;
        cursor = *head;
        *head = next;
    }
    *head = cursor;
}

static void __reverse_recursive(node_t *curr, node_t *prev, node_t **head)
{
    if (!curr) {
        *head = prev;
        return;
    }

    node_t *next = curr->next;
    curr->next = prev;

    __reverse_recursive(next, curr, head);
}

void reverse_recursive(node_t **head)
{
    __reverse_recursive(*head, NULL, head);
}

static void swap_values(node_t *node1, node_t *node2)
{
    int temp = node1->value;
    node1->value = node2->value;
    node2->value = temp;
}

void shuffle(node_t **head)
{
    /* Count the length of the list */
    node_t **indirect = head;
    int len = 0;
    while (*indirect) {
        len++;
        indirect = &(*indirect)->next;
    }

    /*
     * Perform Fisher-Yates shuffle
     *
     * See https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
     */
    srand(time(NULL));

    node_t *curr = *head;

    while (len--) {
        int random = rand() % (len + 1);

        node_t *node_rand = *head;
        for (int j = 0; j < random; j++)
            node_rand = node_rand->next;

        swap_values(curr, node_rand);

        curr = curr->next;
    }
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

void delete_list(node_t **head)
{
    while (*head) {
        node_t *next = (*head)->next;
        free(*head);
        *head = next;
    }
}

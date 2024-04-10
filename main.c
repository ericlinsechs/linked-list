#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    node_t *head = NULL;

    print_list(head);

    for (int i = 1; i <= 10; i++) {
        add_entry(&head, i);
    }

    print_list(head);

    node_t *entry = find_entry(head, 3);
    remove_entry(&head, entry);

    entry = find_entry(head, 7);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    reverse_recursive(&head);
    print_list(head);

    shuffle(&head);
    print_list(head);

    delete_list(&head);

    return 0;
}

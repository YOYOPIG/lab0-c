#include <string.h>

#include "sort.h"

list_ele_t *merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    // Find and split the list in the middle
    list_ele_t *middle = NULL;
    list_ele_t *slow = head;
    list_ele_t *fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    middle = slow->next;
    slow->next = NULL;
    // Sort the two parts and then merge
    list_ele_t *first = merge_sort(head);
    list_ele_t *second = merge_sort(middle);
    return merge(first, second);
}

list_ele_t *merge(list_ele_t *first, list_ele_t *second)
{
    list_ele_t *ordered = NULL;
    list_ele_t *cur = NULL;

    while (first && second) {
        list_ele_t *tmp;

        // Acquire the smallest element
        if (strcmp(first->value, second->value) < 0) {
            tmp = first;
            first = first->next;
            tmp->next = NULL;
        } else {
            tmp = second;
            second = second->next;
            tmp->next = NULL;
        }

        // Append it to ordered list
        if (!ordered) {
            ordered = tmp;
            cur = tmp;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    // Append the only remaining list to back
    cur->next = (first) ? first : second;
    return ordered;
}
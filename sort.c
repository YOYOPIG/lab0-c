#include <stdio.h>
#include <stdlib.h>
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

list_ele_t *trie_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;
    trie_node *root = trie_new();
    list_ele_t *cur = head;
    while (cur) {
        list_ele_t *tmp = cur->next;
        insert_element(root, cur);
        cur = tmp;
    }

    return retrieve_sorted(root);
}



int get_max_length(list_ele_t *head, int n)
{
    list_ele_t *cur = head;
    int max = strlen(cur->value);
    while (cur->next) {
        if (strlen(cur->value) > max)
            max = strlen(cur->value);
        cur = cur->next;
    }
    return max;
}

void counting_sort(list_ele_t *head, int size, int k, int max)
{
    char **tmp = NULL;
    list_ele_t **nodes = NULL;
    list_ele_t *cur = head;
    tmp = malloc(sizeof(char *) * size);
    nodes = malloc(sizeof(list_ele_t *) * size);
    for (int i = 0; i < size; ++i) {
        tmp[i] = malloc(sizeof(char) * max);
        nodes[i] = malloc(sizeof(list_ele_t));
    }
    int count[257];  // Support 256 ASCII code. Change this according to the
                     // data

    for (int i = 0; i < 257; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        // printf("%\n", nodes[i]->value); ///bug
        nodes[i] = cur;
        if (k < strlen(cur->value))
            count[(int) (unsigned char) cur->value[k] + 1]++;
        else
            count[0]++;
        cur = cur->next;
    }

    for (int f = 1; f < 257; f++) {
        count[f] += count[f - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        // printf("%s\n", nodes[i]->value);
        if (k < strlen(nodes[i]->value)) {
            tmp[count[(int) (unsigned char) nodes[i]->value[k] + 1] - 1] =
                nodes[i]->value;
            count[(int) (unsigned char) nodes[i]->value[k] + 1]--;
        } else {
            tmp[count[0] - 1] = nodes[i]->value;
            count[0]--;
        }
    }

    for (int i = 0; i < size; ++i) {
        nodes[i]->value = tmp[i];
    }
    //  printf("yee\n");
    free(tmp);
}


void radix_sort(queue_t *q)
{
    int max = get_max_length(q->head, q->size);

    for (int digit = max; digit > 0;
         digit--) {  // size_t is unsigned, so avoid using digit >= 0, which is
                     // always true
        counting_sort(q->head, q->size, digit - 1, max);
        // list_ele_t *cur = q->head;
        // while(cur)
        // {
        //     printf("%s ", cur->value);
        //     cur = cur->next;
        // }
        // printf("\n");
    }
}

// int main(void) {
//     char *data[] = {
//         "aaaba",
//         "dfjasdlifjai",
//         "jiifjeogiejogp",
//         "aabaaaa",
//         "gsgj",
//         "gerph",
//         "aaaaaaa",
//         "htjltjlrth",
//         "joasdjfisdjfdo",
//         "hthe",
//         "aaaaaba",
//         "jrykpjl",
//         "hkoptjltp",
//         "aaaaaa",
//         "lprrjt"
//     };
//     puts("before sorting:");
//     for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
//         printf("    %s\n", data[i]);
//     }
//     radix_sort(data, (int)(sizeof(data) / sizeof(data[0])));
//     puts("after sorting:");
//     for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
//         printf("    %s\n", data[i]);
//     }
//     return 0;
// }

#ifndef LAB0_SORT_H
#define LAB0_SORT_H
#include <stdio.h>

#include "queue.h"
#include "trie.h"

list_ele_t *merge_sort(list_ele_t *head);
list_ele_t *merge(list_ele_t *first, list_ele_t *second);
list_ele_t *trie_sort(list_ele_t *head);
int get_max_length(list_ele_t *head, int n);
void counting_sort(list_ele_t *head, int size, int k, int max);
void radix_sort(queue_t *q);

#endif /* LAB0_SORT_H */
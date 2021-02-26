#ifndef LAB0_SORT_H
#define LAB0_SORT_H
#include <stdio.h>

#include "queue.h"
#include "trie.h"

list_ele_t *merge_sort(list_ele_t *head);
list_ele_t *merge(list_ele_t *first, list_ele_t *second);
list_ele_t *trie_sort(list_ele_t *head);

#endif /* LAB0_SORT_H */
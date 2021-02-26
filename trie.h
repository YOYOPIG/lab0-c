#ifndef LAB0_TRIE_H
#define LAB0_TRIE_H
#include <stdio.h>
#include "queue.h"

typedef struct NODE {
    char value;
    struct NODE *child[26];
    list_ele_t *list_head;
} trie_node;


trie_node *trie_new();
trie_node *new_node(char val);
void insert_element(trie_node *root, list_ele_t *element);
list_ele_t *retrieve_sorted(trie_node *root);

#endif
#include "trie.h"
#include <stdlib.h>
#include <string.h>
trie_node *trie_new()
{
    trie_node *root = new_node('0');
    return root;
}

trie_node *new_node(char val)
{
    trie_node *node = malloc(sizeof(trie_node));
    if (!node)
        return NULL;
    node->value = val;
    for (int i = 0; i < 26; ++i)
        node->child[i] = NULL;
    node->list_head = NULL;
    return node;
}

void insert_element(trie_node *root, list_ele_t *element)
{
    trie_node *cur = root;
    for (int i = 0; i < strlen(element->value); ++i) {
        char ch = element->value[i];
        if (!cur->child[ch - 'a'])
            cur->child[ch - 'a'] = new_node(ch);
        cur = cur->child[ch - 'a'];
    }
    if (!cur->list_head) {
        cur->list_head = element;
        element->next = NULL;
    } else {
        list_ele_t *tmp = cur->list_head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = element;
        tmp->next->next = NULL;
    }
}

list_ele_t *retrieve_sorted(trie_node *root)
{
    if (!root)
        return NULL;
    list_ele_t *result = NULL;
    list_ele_t *cur = result;
    for (int i = 0; i < 26; ++i) {
        list_ele_t *tmp = retrieve_sorted(root->child[i]);
        if (tmp) {
            if (!result) {
                result = tmp;
                cur = result;
            } else {
                cur->next = tmp;
            }
            while (cur->next)
                cur = cur->next;
        }
    }
    if (!result) {
        result = root->list_head;
    } else {
        cur->next = root->list_head;
    }
    return result;
}

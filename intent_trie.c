#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end_of_word;
    char route_destination[32];
} TrieNode;

TrieNode* create_trie_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_end_of_word = false;
    strcpy(node->route_destination, "fallback_index");
    for (int i = 0; i < ALPHABET_SIZE; i++) node->children[i] = NULL;
    return node;
}

#ifdef _WIN32
    __declspec(dllexport) TrieNode* init_trie_parser();
    __declspec(dllexport) void insert_routing_intent(TrieNode* root, const char* word, const char* index_target);
    __declspec(dllexport) const char* evaluate_query_intent(TrieNode* root, const char* word);
    __declspec(dllexport) void free_trie_parser(TrieNode* root);
#endif

TrieNode* init_trie_parser() { return create_trie_node(); }

void insert_routing_intent(TrieNode* root, const char* word, const char* index_target) {
    TrieNode* current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) continue; // Boundary filter for basic strings
        if (!current->children[index]) current->children[index] = create_trie_node();
        current = current->children[index];
    }
    current->is_end_of_word = true;
    strncpy(current->route_destination, index_target, sizeof(current->route_destination) - 1);
}

const char* evaluate_query_intent(TrieNode* root, const char* word) {
    TrieNode* current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= ALPHABET_SIZE) continue;
        if (!current->children[index]) return "fallback_index";
        current = current->children[index];
    }
    if (current != NULL && current->is_end_of_word) return current->route_destination;
    return "fallback_index";
}

void free_trie_parser(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free_trie_parser(root->children[i]);
    }
    free(root);
}

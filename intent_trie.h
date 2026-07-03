#ifndef INTENT_TRIE_H
#define INTENT_TRIE_H

typedef struct TrieNode TrieNode;
TrieNode* init_trie_parser();
void insert_routing_intent(TrieNode* root, const char* word, const char* index_target);
const char* evaluate_query_intent(TrieNode* root, const char* word);
void free_trie_parser(TrieNode* root);

#endif

from trie_bridge import TrieBridge

if __name__ == "__main__":
    parser = TrieBridge()

    # Map intent words to targeted document collection indexes via C Prefix Trees
    parser.add_intent_route("database", "vector_db_index_shard_1_sql")
    parser.add_intent_route("firewall", "vector_db_index_shard_2_networks")

    # Simulate unstructured user search requests
    user_query_stream = ["database", "unknownkey"]

    print("=== LEXINTENT-PARSER INTENT-BASED INDEX SHARD ROUTER ===")
    for token in user_query_stream:
        target_shard = parser.route_query_string(token)
        print(f" -> Query Keyword Token Extracted: [{token}]")
        print(f" -> Dynamic Intent Sub-Graph Shard Path Selected: {target_shard}\n")

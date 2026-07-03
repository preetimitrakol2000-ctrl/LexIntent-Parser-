import ctypes
import os
import sys

class TrieBridge:
    def __init__(self):
        if not os.path.exists("./libtrie.so") and not os.path.exists("./libtrie.dll"):
            if sys.platform.startswith("win"):
                os.system("gcc -shared -o libtrie.dll intent_trie.c")
                lib_path = "./libtrie.dll"
            else:
                os.system("gcc -shared -fPIC -o libtrie.so intent_trie.c")
                lib_path = "./libtrie.so"
        else:
            lib_path = "./libtrie.dll" if sys.platform.startswith("win") else "./libtrie.so"

        self.lib = ctypes.CDLL(lib_path)
        self.lib.init_trie_parser.restype = ctypes.c_void_p
        self.lib.insert_routing_intent.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
        self.lib.evaluate_query_intent.argtypes = [ctypes.c_void_p, ctypes.c_char_p]
        self.lib.evaluate_query_intent.restype = ctypes.c_char_p
        self.lib.free_trie_parser.argtypes = [ctypes.c_void_p]
        
        self.trie_ptr = self.lib.init_trie_parser()

    def add_intent_route(self, intent_word: str, target_vector_db_index: str):
        self.lib.insert_routing_intent(self.trie_ptr, intent_word.lower().encode('utf-8'), target_vector_db_index.encode('utf-8'))

    def route_query_string(self, word: str) -> str:
        return self.lib.evaluate_query_intent(self.trie_ptr, word.lower().encode('utf-8')).decode('utf-8')

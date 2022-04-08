

#include "KaryTree.h"

#define tiny_tree ".data/tiny_tree.json"
#define small_tree ".data/small_tree.json"
#define big_tree ".data/big_tree.json"

#define dataset big_tree


// uint32_t getTreeKeys(nlohmann::json jsonObject);
extern node* loadCompressedJSON(const char fileName[], node **NodeArray);
extern node* convertCompressedJSON2tree(nlohmann::json rootObject , node **NodeArray, int depth);

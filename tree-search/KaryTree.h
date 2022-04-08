
#define TYPE int16_t // must be signed type
#define uint32_t unsigned int

typedef struct node node;
struct node{
    int child_num;
    TYPE* childs_keys;
    // max value is 549, store them in
    node** childs; 
    // use to verify the search function find correct Node
    TYPE key;
};


void initNode(node* n){
    n->child_num = 0;
    n->childs_keys = NULL;
    n->childs = NULL;
};
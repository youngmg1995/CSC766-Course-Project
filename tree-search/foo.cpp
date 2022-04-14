// =====================================================================================
// accelerate searching of k-ary Heap tree using wasm SIMD instructions
// author: Zong-Ru Li
// date:  3/21/2022
// edition: v1.0
// description: 
//              data storage structure:   static array
//              tree type:                Max 4-ary heap
//              compare 4 child nodes from the same parent node using wasm_i32x4_eq instruction,
//              and then use wasm_i32x4_bitmask filter output into 4 bit
// =====================================================================================

// -------------------------------------------------
// #define SIMD // or you can use -DSIMD during em++/g++ compile
// -------------------------------------------------
// include header
#ifdef SIMD
#include <wasm_simd128.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "json.hpp"
#include <unordered_map>
#include <ctime>
typedef std::chrono::high_resolution_clock clock_;
typedef std::chrono::duration<double, std::ratio<1> > second_;
typedef std::chrono::time_point<clock_> timepoint_;
typedef std::chrono::microseconds ms;
using namespace std;
//using namespace std::chrono;

#include "foo.h"
// -------------------------------------------------
void printFindArray( vector<node* >FindArray, int find ){
    if(find==0) return;

    for(int i=0;i<FindArray.size();i++) {
        std::cout<< (int) FindArray[i]->key<<" ";
    }
    std::cout<<endl;
}
int get_golden_find( node* n, int size, TYPE search_key ){
    int find_ans=0;
    // cout<<search_key<<endl;
    for(int i=0;i<size;i++, n++ ) {
        if( n->key == search_key ){ find_ans++;} 
    }
    return find_ans;
}

bool compareFindArray( vector<node* > ans, vector<node* > in , TYPE search_key){
    if(ans.size()!=in.size()) return false;

    for(int i=0;i<ans.size();i++) {
        if( ans[i]->key != search_key ) return false;
        if( ans[i]->key != in[i]->key ) return false;
    }
    return true;
}

void printTree( node* root , int depth =0 ){
    std::cout<< "depth: "<<depth<<std::endl;
    
    std::cout<<"root key: "<<root->key<<std::endl;
    std::cout<<"root child num: "<<root->child_num<<std::endl;
    for(int i=0;i<root->child_num;i++)
        std::cout<<"root child keys["<<i<<"]: "<<root->childs_keys[i]<<std::endl;
    for(int i=0;i<root->child_num;i++)
        printTree(root->childs[i], depth + 1 );
}
int originalSearchTree( node* root , vector<node*> & FindArray, TYPE key ){
    int find = 0;
    if( root->key == key ){ 
        FindArray.push_back(root);
        //cout<<key<<" "<< root->key<<endl;
        find++; 
    }
    for(int i=0;i<root->child_num;i++){
        find += originalSearchTree(root->childs[i], FindArray, key );
    }
    return find;
}

TYPE getTreeKeys(nlohmann::json jsonObject)
{
    if (jsonObject.size() <= 0) return 0;
    
    uint32_t totalNodes = 1;
    // TYPE key = jsonObject["n"];
    nlohmann::json children = jsonObject["c"];

    for (auto child : children){
        totalNodes += getTreeKeys( child );
    }
    return totalNodes;
}
int get_child_num(nlohmann::json rootObject){
    int total_child_num=0;
    nlohmann::json childrenObject = rootObject["c"];
    for (auto childObject : childrenObject){
        //   std::cout<<"child key: "<<childObject["n"]<<std::endl;
        if(childObject["n"] != NULL) total_child_num ++;
    }
    // std::cout<<"total_child_num: "<<total_child_num<<std::endl;
    return total_child_num;
}
node* convertCompressedJSON2tree(nlohmann::json rootObject , node **NodeArray)
{
    if (rootObject.size() <= 0) return NULL;
    
    int i=0;
    node *root = *NodeArray;

     
    (*NodeArray)++;
    initNode(root);
    // std::cout<<"fffffffffffff: "<<std::endl;


    root->key = rootObject["n"];
    // std::cout<<rootObject<<std::endl;
    nlohmann::json childrenObject = rootObject["c"];
    // root->child_num=1;
    // root->childs_keys = (TYPE*) malloc( root->child_num*sizeof(TYPE) );
    // root->childs_keys[0] =  value
    // root->childs = (node**) malloc(1*sizeof(node*));
    // std::cout<<"44444444444444444: "<<std::endl;
    // std::cout<<"depth: "<<depth<<std::endl;
    root->child_num = get_child_num( rootObject );
    // std::cout<<"child num: "<<root->child_num<<std::endl;

    if(root->child_num == 0){ return root; }
    int expanded_size = root->child_num + ( 8 - (root->child_num % 8) );
    if(expanded_size % 8 != 0) {cout<<"error ! size is not times of 8!!"<<endl; exit(0); }
    root->childs_keys = (TYPE *)malloc(expanded_size*sizeof(TYPE));
    for(i=0;i<expanded_size;i++) root->childs_keys[i] =-1;
    root->childs = (node**) malloc(root->child_num*sizeof(node*));

    i=0;
    for (auto childObject : childrenObject)
    {
        root->childs_keys[i] = childObject["n"];
        // std::cout<<"child key: "<<root->childs_keys[i]<<std::endl;
        i ++;        
    }

    i=0;
    for (auto childObject : childrenObject)
    {
        root->childs[i] = convertCompressedJSON2tree(childObject, NodeArray );
        // root->children = insertNode(root->children, child);
        i ++;
    }
    return root;
}

node* loadCompressedJSON(const char fileName[], node **NodeArray, int* total_size)
{
    // cout<<"555555555555555"<<fileName<<endl;;
    string line;
    ifstream inputStream;

    inputStream.open(dataset);
    if (!inputStream.is_open()) exit(0);
    
    
    cout<<"file is open"<<endl;
    nlohmann::json jsonObject = nlohmann::json::parse(inputStream);
    nlohmann::json childrenObject = jsonObject["c"];
    inputStream.close();

    *total_size = 1 + getTreeKeys( jsonObject );
    *NodeArray = (node*)malloc(*total_size*sizeof(node));
    node* root = *NodeArray;
    (*NodeArray)++;
    initNode(root);
    // root->child_num = get_child_num( childrenObject );
    root->key = -1; // no key in virtual root!
    root->child_num = 1;
    // std::cout<<"child num: "<<  root->child_num  <<std::endl;
    
     //cout<< jsonObject<<endl;
    
    // root->child_num=1;
    root->childs_keys = (TYPE*) malloc( 32*sizeof(TYPE) );
    for(int k=0;k<32;k++)  root->childs_keys[k] =-1;

    root->childs_keys[0] = jsonObject["n"];
    root->childs = (node**) malloc( 1*sizeof(node*) );    
    root->childs[0] = *NodeArray;

    convertCompressedJSON2tree(jsonObject, NodeArray);
    return root;
}

int searchTree(node* root, vector<node* > &FindArray, TYPE* search_key){
    int find = 0;
    for(int i=0;i<root->child_num;i++){
        if(root->childs_keys[i] == search_key[0] ) 
        {
            FindArray.push_back(root->childs[i]);
            find++;
        }// std::cout<<"root child keys["<<i<<"]: "<<root->childs_keys[i]<<std::endl;
    }
        
    for(int i=0;i<root->child_num;i++)
        find += searchTree(root->childs[i], FindArray, search_key );

    return find;
};
#ifdef SIMD

int searchTree_SIMD8(node* root, vector<node* > &FindArray, TYPE* search_key){
    int find = 0;
    // int k=0;

    if(root->child_num == 0) return 0;

    for( int i=0; i< root->child_num; i+=8 ){
        
        v128_t a = wasm_v128_load(&root->childs_keys[i+0]);
        v128_t b = wasm_v128_load(&search_key[0]);

        v128_t cmp = wasm_i16x8_eq(a, b);
        uint16_t mask = wasm_i16x8_bitmask(cmp);
        // uint16_t mask = wasm_i32x4_bitmask(cmp);
        
        // logics to verify SIMD comparison
        // int find_bits = 0;
        // for( k=0; (k<8) && ((i+k)<root->child_num) ; k++ ){
        //     if(root->childs_keys[i+k] == search_key[0] ) find_bits += (1<<k);
        // }

        // if( find_bits !=mask ) {
        //     cout<<"child_num: "<<root->child_num<<" i+k: "<<i+8<<endl;
        //     cout<<"find_bits: "<<find_bits<<" mask: "<<mask<<endl;
        //     for( k=0;k<8;k++) cout<<root->childs_keys[i+k]<<" ";
        //     cout<<endl<<" ------"<<endl;
        //     for( k=0;k<8;k++) cout<<search_key[0]<<" ";
        //     cout<<endl<<" ------"<<endl;
        //     exit(0);
        // }

        // switch(mask){
        //     case 0: continue;
        //     case 1:  FindArray.push_back(root->childs[i+0]); 
        //         find++;  
        //         break;
        //     case 2:  FindArray.push_back(root->childs[i+1]); 
        //         find++;  
        //         break;
        //     case 4:  FindArray.push_back(root->childs[i+2]);
        //         find++;  
        //         break;
        //     case 3: FindArray.push_back(root->childs[i+0]);
        //         FindArray.push_back(root->childs[i+1]);
        //         find+=2;  
        //         break;
        //     case 5: FindArray.push_back(root->childs[i+0]);
        //         FindArray.push_back(root->childs[i+2]);
        //         find+=2;  
        //         break;
        //     case 7: 
        //         FindArray.push_back(root->childs[i+0]);
        //         FindArray.push_back(root->childs[i+1]);
        //         FindArray.push_back(root->childs[i+2]);
        //         find+=3;  
        //         break;
        //     default:
        //         for( k=3; (k<8) && ((i+k)<root->child_num) ; k++){
        //             if( (mask & (1<<k) ) > 0 ){
        //                 FindArray.push_back(root->childs[i+k]);
        //                 find++;  
        //             }
        //         }
        //         break;
        // }
        if( (mask & (1)) ){ FindArray.push_back(root->childs[i+0]); find++; }
        if( (mask & (2)) ){ FindArray.push_back(root->childs[i+1]); find++; }
        if( (mask & (4)) ){ FindArray.push_back(root->childs[i+2]); find++; }
        if( (mask & (8)) ){ FindArray.push_back(root->childs[i+3]); find++; }
        if( (mask & (16)) ){ FindArray.push_back(root->childs[i+4]); find++; }
        if( (mask & (32)) ){ FindArray.push_back(root->childs[i+5]); find++; }
        if( (mask & (64)) ){ FindArray.push_back(root->childs[i+6]); find++; }
        if( (mask & (128)) ){ FindArray.push_back(root->childs[i+7]); find++; }

        // for( k=0; (k<8) && ((i+k)<root->child_num) ; k++){
        //     if( (mask & (1<<k) ) ){
        //         FindArray.push_back(root->childs[i+k]);
        //         find++;                
        //     }
        // }
        // std::cout<<"root child keys["<<i<<"]: "<<root->childs_keys[i]<<std::endl;
    }
        
    for(int i=0;i<root->child_num;i++)
        find += searchTree_SIMD8(root->childs[i], FindArray, search_key );

    return find;
};
int searchTree_SIMD4(node* root, vector<node* > &FindArray, TYPE* search_key){
    int find = 0;
    // int k=0;

    if(root->child_num == 0) return 0;

    for( int i=0; i< root->child_num; i+=4 ){
        
        v128_t a = wasm_v128_load(&root->childs_keys[i+0]);
        v128_t b = wasm_v128_load(&search_key[0]);

        v128_t cmp = wasm_i16x8_eq(a, b);
        uint16_t mask = wasm_i16x8_bitmask(cmp);
        // uint16_t mask = wasm_i32x4_bitmask(cmp);
        
        if( (mask & (1)) ){ FindArray.push_back(root->childs[i+0]); find++; }
        if( (mask & (2)) ){ FindArray.push_back(root->childs[i+1]); find++; }
        if( (mask & (4)) ){ FindArray.push_back(root->childs[i+2]); find++; }
        if( (mask & (8)) ){ FindArray.push_back(root->childs[i+3]); find++; }

    }
        
    for(int i=0;i<root->child_num;i++)
        find += searchTree_SIMD8(root->childs[i], FindArray, search_key );

    return find;
};

#endif

int main()
{
    srand(time(0));
    timepoint_ start1,start2,end1,end2,start3,end3,start4,end4;

    double duration1, duration2, duration3,duration4, cpu_time_used_4,cpu_time_used_3, cpu_time_used_1 ,cpu_time_used_2;
    cpu_time_used_4 = cpu_time_used_3 = cpu_time_used_1 = cpu_time_used_2 =0;
    // const int capacity = 1000000;
    //node arr[capacity];
    node *arr = NULL;
    node *virtual_root = NULL;
    vector<node*> FindArray_ans;
    vector<node*> FindArray_test;
    vector<node*> FindArray_simd;
    int find1, find2 ,find3,find4, golden_find=0;
    int arr_size=0;
    // std::unordered_map<std::string, int> keyMap;
    // int treeSize = loadJSON(tree_input_file, keyMap, &splayArray, &root);

    //arr = malloc(capacity*sizeof(node));

    virtual_root = loadCompressedJSON( dataset, &arr, &arr_size);
    cout<<"arr size: "<<arr_size<<endl;
    // printTree(virtual_root, 0);

    // find1 = searchTree(virtual_root, FindArray_ans, search_key);
    // cout<<"find1: "<<find1<<endl;
    // printFindArray(FindArray_ans, find1);
    
    // find2 = searchTree_SIMD8(virtual_root, FindArray_simd, search_key);
    // cout<<"find2: "<<find2<<endl;
    // printFindArray(FindArray_simd, find2);
    
    TYPE search_key;
    TYPE* search_key_arr;
    search_key_arr = (TYPE*)malloc(32*sizeof(TYPE));
//     find1 = originalSearchTree(virtual_root, FindArray_ans, 0 );
//     find3 = searchTree(virtual_root, FindArray_test,search_key_arr);
    find1 = originalSearchTree(virtual_root, FindArray_ans, 0 );
#ifdef SIMD
    find2 = searchTree_SIMD8(virtual_root, FindArray_simd, search_key_arr);
    find4 = searchTree_SIMD4(virtual_root, FindArray_simd, search_key_arr);
#endif
    find1 = originalSearchTree(virtual_root, FindArray_ans, 0 );
#ifdef SIMD
    find2 = searchTree_SIMD8(virtual_root, FindArray_simd, search_key_arr);
    find4 = searchTree_SIMD4(virtual_root, FindArray_simd, search_key_arr);
#endif
    find1 = originalSearchTree(virtual_root, FindArray_ans, 0 );
#ifdef SIMD
    find2 = searchTree_SIMD8(virtual_root, FindArray_simd, search_key_arr);
    find4 = searchTree_SIMD4(virtual_root, FindArray_simd, search_key_arr);
#endif

    int repeat_times = 2;
    for(int k=0;k<repeat_times;k++)
    {
        FindArray_ans.clear();
        FindArray_test.clear();
        FindArray_simd.clear();
        search_key = rand()% 549;//399;
        if(search_key<0) continue;

        golden_find = get_golden_find( virtual_root, arr_size, search_key);
        cout<<"search key: "<<search_key<<" golden find: "<<golden_find<<endl;
        for(int i=0;i<32;i++) search_key_arr[i] = search_key;

        start1 = clock_::now();
        find1 = originalSearchTree(virtual_root, FindArray_ans,search_key);
        end1 = clock_::now();
        duration1= ((double) duration_cast<ms>( end1 - start1 ).count() );// / CLOCKS_PER_SEC;
        cpu_time_used_1 += duration1/repeat_times;
        cout << "Duration of binary search: (ms)"<<duration1 << endl;
        cout<<"find "<<find1<<" elements in binary search"<<endl;

        // if ( golden_find == find1 ){
        //     cout<<"PASS"<<endl;
        // }else {
            
        //     cout<<"FAIL in original test "<<endl;
        // }

        // start3 = clock_::now();
        // find3 = searchTree(virtual_root, FindArray_test,search_key_arr);
        // end3 = clock_::now();
        // duration3= ((double) duration_cast<ms>( end3 - start3 ).count() );// / CLOCKS_PER_SEC;
        // cpu_time_used_3 += duration3/repeat_times;
        // cout << "Duration of same level child search: (ms)"<<duration3 << endl;
        // cout<<"find "<<find3<<" elements in same level child search"<<endl;
        // // printFindArray(FindArray_test, find1);

        // if ( golden_find == find2 ){
        //     cout<<"PASS"<<endl;
        // }else {
        //     cout<<"FAIL in search test "<<endl;
        //     printFindArray(FindArray_ans, find1);
        //     cout<<"--------"<<endl;
        //     printFindArray(FindArray_test, find2);
        //     exit(0);
        // }
#ifdef SIMD
        start2 = clock_::now();
        find2 = searchTree_SIMD8(virtual_root, FindArray_simd, search_key_arr);
        end2 = clock_::now();
        duration2 = ((double) duration_cast<ms>( end2 - start2 ).count() );// / CLOCKS_PER_SEC;
        cpu_time_used_2 += duration2/repeat_times;
        cout << "Duration of SIMD8 search: (ms)"<<duration2 << endl;
        cout<<"find "<<find2<<" elements in SIMD8 search"<<endl;
        // printFindArray(FindArray_simd, find2);

        if (  golden_find == find2 ){
            cout<<"PASS"<<endl;
        }else {
            
            cout<<"FAIL in simd test "<<endl;
            printFindArray(FindArray_ans, find1);
            printFindArray(FindArray_simd, find2);
            exit(0);
        }

        start4 = clock_::now();
        find4 = searchTree_SIMD4(virtual_root, FindArray_simd, search_key_arr);
        end4 = clock_::now();
        duration4 = ((double) duration_cast<ms>( end4 - start4 ).count() );// / CLOCKS_PER_SEC;
        cpu_time_used_4 += duration4/repeat_times;
        cout << "Duration of SIMD4 search: (ms)"<<duration4 << endl;
        cout<<"find "<<find4<<" elements in SIMD4 search"<<endl;
        // printFindArray(FindArray_simd, find2);

        if (  golden_find == find4 ){
            cout<<"PASS"<<endl;
        }else {
            
            cout<<"FAIL in simd test "<<endl;
            printFindArray(FindArray_ans, find1);
            printFindArray(FindArray_simd, find4);
            exit(0);
        }
#endif
    }
    cout << "avg Duration of original search: (ms)"<<cpu_time_used_1 << endl;
    // cout << "avg Duration of serial slow search: (ms)"<<cpu_time_used_3 << endl;
#ifdef SIMD
    cout << "avg Duration of SIMD8 search: (ms)"<<cpu_time_used_2 << endl;
    cout << "avg Duration of SIMD4 search: (ms)"<<cpu_time_used_4 << endl;
#endif
    return 0;
}

#include "Hashmap.h"

unsigned int hash(const char* str) {
    //自定义哈希函数（JS Hash Function）
    unsigned int hash = 1315423911;

    while (*str) {
        hash ^= ((hash << 5) + (*str++) + (hash >> 2));
    }
    return (hash & 0x7FFFFFFF);
}

HashMap* hashmap_create() {
    return calloc(1, sizeof(HashMap));
}

void hashmap_destroy(HashMap* map) {
    free(map);
}

V hashmap_put(HashMap* map, K key, V val) {
    int index = hash(key) % N;
    //遍历链表
    Node* curr = map->table[index];

    while (curr) {

        if (strcmp(curr->key, key) == 0) {
            //如果相等就更新哈希的值
            V oldvalue = curr->val;
            curr->val = val;
            return oldvalue;
        }
        curr = curr->next;
    }
    //创建新的结点
    Node* new_node = malloc(sizeof(Node));

    if (new_node == NULL) {
        printf("malloc failed in hashmap_put.\n");
        exit(1);
    }
    //初始化新的结点
    new_node->key = key;
    new_node->val = val;
    //头插法
    new_node->next = map->table[index];
    map->table[index] = new_node;
    return NULL;
}

V hashmap_get(HashMap* map, K key) {
    int index = hash(key) % N;
    Node* curr = map->table[index];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            return curr->val;
        }
        curr = curr->next;
    }
    return NULL;
}

void hashmap_delete(HashMap* map, K key) {
    int index = hash(key) % N;
    Node* curr = map->table[index];
    Node* pre = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) {//相同就删除
            if (pre == NULL) {
                //删除第一个结点
                map->table[index] = curr->next;
                free(curr);
            }
            else {
                pre->next = curr->next;
                free(curr);
            }
            return;
         }
        pre = curr;
        curr = curr->next;
    }
    printf("can not find this key\n");
    return;
}

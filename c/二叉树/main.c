#include "BST.h"
#include "Queue.h"

int main() {
    BST* bst = bst_creat();
    bst_insert(bst, 9);
    bst_insert(bst, 5);
    bst_insert(bst, 42);
    bst_insert(bst, 3);
    bst_insert(bst, 13);
    bst_insert(bst, 57);
    TreeNode* node_1 = bst_search(bst, 42);
    TreeNode* node_2 = bst_search(bst, 44);

    if (node_1) {
        printf("node_1的key值=%d.\n", node_1->
            key);
    }
    else {
        printf("符合key值的node不存在\n");
    }

    if (node_2) {
        printf("node_2的key值=%d.\n", node_2->key);
    }
    else {
        printf("符合key值的node不存在\n");
    }
    bst_preorder(bst);
    bst_inorder(bst);
    bst_postorder(bst);
    bst_levelorder(bst);
    bst_delete(bst, 3);
    //bst_delete(bst, 5);
    bst_delete(bst, 9);
    int preorder[] = {
        9,5,3,42,13,57
    }
    ;
    int inorder[] = {
        3,5,9,13,42,57
    }
    ;
    BST* tree = bst_buildTree(preorder, inorder, 6);
    return 0;
}

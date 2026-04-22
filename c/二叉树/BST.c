#include "BST.h"
#include "Queue.h"

BST* bst_creat() {
    //创建BST
    return calloc(1, sizeof(BST));
}

void bst_destroy(BST* tree) {
    //销毁BST
}

void bst_insert(BST* tree, K key) {
    //插入结点
    TreeNode* pre = NULL;
    TreeNode* curr = tree->
        root;

    while (curr) {
        //查找结点
        int cmp = key - curr->key;

        if (cmp < 0) {
            pre = curr;
            curr = curr->left;
        }

        else if (cmp > 0) {
            pre = curr;
            curr = curr->right;
        }
        else {
            //相等的情况
            return;
        }
    }
    //最后就是curr=NULL
    TreeNode* new_node = calloc(1, sizeof(TreeNode));

    if (new_node == NULL) {
        printf("calloc failed in bst_insert.\n");
        exit(1);
    }
    new_node->key = key;

    if (pre == NULL) {
        //此时BST没有结点
        tree->root = new_node;
        return;
    }

    else if (pre->key > key) {
        pre->left = new_node;
    }
    else {
        //pre->key < key   因为相等的情况在上面排除掉了
        pre->right = new_node;
    }
}

TreeNode* bst_search(BST* tree, K key) {
    //查找结点
    TreeNode* curr = tree->root;

    while (curr) {
        //查找结点
        int cmp = key - curr->key;

        if (cmp < 0) {
            curr = curr->left;
        }

        else if (cmp > 0) {
            curr = curr->right;
        }
        else {
            //相等的情况
            return curr;
        }
    }
    //循环结束后就是没有找到  curr=NULL
    return NULL;
}

void bst_delete(BST* tree, K key) {
    //删除结点  分三种情况 度分别为 0 1 2
    TreeNode* parent = NULL;
    TreeNode* curr = tree->root;

    while (curr) {
        int cmp = key - curr->key;

        if (cmp < 0) {
            parent = curr;
            curr = curr->left;
        }

        else if (cmp > 0) {
            parent = curr;
            curr = curr->right;
        }
        else {
            //找到目标结点
            break;
        }
    }

    if (curr == NULL) {
        printf("删除失败\n");
        return;
    }
    //此时curr是要删除的结点
    //将度为2的结点退化成度为1或0的结点情况

    if (curr->left && curr->right) {
        TreeNode* min_of_right_parent = curr;
        TreeNode* min_of_right = curr->right;

        while (min_of_right->left != NULL) {
            //找到右子树的最小结点
            min_of_right_parent = min_of_right;
            min_of_right = min_of_right->left;
        }
        curr->key = min_of_right->key;
        //退化  实际上是要跟度为1或者0的结点一起操作
        parent = min_of_right_parent;
        curr = min_of_right;
    }
    //删除度为1或者0的结点
    TreeNode* child = curr->left ? curr->left : curr->right;
    //很巧妙的将度为1和0的情况都结合 如果度为0那就是传入NULL

    if (parent == NULL) {
        //表示删除 单只树的 根结点
        tree->root = child;
    }

    else if (curr->key < parent->key) {
        parent->left = child;
    }
    else {
        parent->right = child;
    }
    free(curr);
}

void preorder_helper(TreeNode* node) {
    //边界条件
    if (node == NULL) return;
    //根
    printf("%d ", node->key);
    //左
    preorder_helper(node->left);
    //右
    preorder_helper(node->right);
}

void inorder_helper(TreeNode* node) {
    //边界条件
    if (node == NULL) return;
    //左
    inorder_helper(node->left);
    //根
    printf("%d ", node->key);
    //右
    inorder_helper(node->right);
}

void postorder_helper(TreeNode* node) {
    //边界条件
    if (node == NULL) return;
    //左
    postorder_helper(node->left);
    //右
    postorder_helper(node->right);
    //根
    printf("%d ", node->key);
}

void bst_preorder(BST* tree) {
    printf("前序:");
    preorder_helper(tree->root);
    printf("\n");
}

void bst_inorder(BST* tree) {
    printf("中序:");
    inorder_helper(tree->root);
    printf("\n");
}

void bst_postorder(BST* tree) {
    printf("后序:");
    postorder_helper(tree->root);
    printf("\n");
}

void bst_levelorder(BST* tree) {
    if (tree->root == NULL) return;
    Queue* q = queue_create();
    //创建队列
    TreeNode* curr = tree->root;
    queue_push(q, tree->root);
    printf("层序:");

    while (!queue_empty(q)) {
        TreeNode* node = queue_pop(q);
        printf("%d ", node->key);

        if (node->left) {
            queue_push(q, node->left);
        }

        if (node->right) {
            queue_push(q, node->right);
        }
    }
    queue_destroy(q);
    // 释放队列内存
    printf("\n");
}

TreeNode* build(K preorder[], K inorder[], int n) {
    //边界条件
    if (n == 0) return NULL;
    //构建根节点
    K key = preorder[0];
    TreeNode* node = malloc(sizeof(TreeNode));

    if (node == NULL) {
        printf("malloc failed in build.\n");
        exit(1);
    }
    int index = 0;

    while (inorder[index] != key) {
        index++;
    }
    //构建左子树
    node->left = build(preorder + 1, inorder, index);
    //构建右子树
    node->right = build(preorder + 1 + index, inorder + 1 + index, n - 1 - index);
    node->key = key;
    return node;
}

BST* bst_buildTree(K preorder[], K inorder[], int n) {
    BST* tree = malloc(sizeof(BST));

    if (tree == NULL) {
        return NULL;
    }
    tree->root = build(preorder, inorder, n);
    return tree;
}
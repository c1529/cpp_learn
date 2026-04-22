#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int K;
typedef struct tree_node {
	K key;
	struct tree_node* left;
	struct tree_node* right;
} TreeNode;
typedef struct {
	TreeNode* root;
} BST;

//API
BST* bst_creat();//创建BST
void bst_destroy(BST* tree);//销毁BST

void bst_insert(BST* tree, K key);//插入结点
TreeNode* bst_search(BST* tree, K key);//查找结点
void bst_delete(BST* tree, K key);//删除结点
//二叉树的遍历
void bst_preorder(BST* tree);//前序
void bst_inorder(BST* tree);//中序
void bst_postorder(BST* tree);//后序
void bst_levelorder(BST* tree);//层次
BST* bst_buildTree(K preorder[], K inorder[], int n);//根据先序和中序建树
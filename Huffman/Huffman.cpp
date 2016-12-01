/*
#include<stdio.h>
#include<malloc.h>


//huffman tree node
typedef struct node{
	int value;
	char letter;
	struct node *left, *right;
}NODE, *TreeNode;

void input(int *w, char *l, int n)
{
	int i;
	printf("Please enter letters:");
	for(i = 0; i < n; i++ )
		scanf("%c",&l[i]);
	printf("Please enter letter's weight:");
	for(i = 0; i < n; i++ )
		scanf("%d",&w[i]);
}

int main()
{
	int n;
	int *w, *l;
}*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

//--------huffman tree的编码存储表示---------
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, *HuffmanTree;               //动态分配数组存储huffman tree

typedef char * *HuffmanCode;		//动态分配数组存储huffman 编码表

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int * w, int n) {
	if (n <= 1)
		return;

}
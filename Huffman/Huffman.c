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
	for(i = 0; i < n; i++0)
		scanf("%c",&l[i]);
	printf("Please enter letter's weight:");
	for(i = 0; i < n; i++0)
		scanf("%d",&w[i]);
}

int main()
{
	int n;
	int *w,*l;

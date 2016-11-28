#include<stdio.h>
#include<malloc.h>
#define N 27
#define Max 1024


typedef struct HF
{
	int weight;
	int parent;
	int lchild,rchild;
};
struct Char
{
	char ch[N];
	int start;
};

void main()
{
	struct HF hf[2*N+1];

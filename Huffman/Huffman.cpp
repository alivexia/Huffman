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
#include<string.h>

//--------huffman tree�ı���洢��ʾ---------
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;               //��̬��������洢huffman tree

typedef char * *HuffmanCode;		//��̬��������洢huffman �����

void Select(HuffmanTree HT, int i, int s1, int s2) {

}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int * w, int n) {
	//w���n���ַ���Ȩֵ����>0),����HT�������n���ַ���huffman coding
	int m, i, c ,s1 ,s2 ,start ,f ;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0�ŵ�Ԫδʹ��
	for (p = HT + 1,i = 1; i <= n; ++i, ++p, ++w)
		* p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		*p = { 0,0,0,0 };
	for (i = n + 1; i <= m; i++) {		//��huffman tree
		//ѡ��parentΪ0��weight��С�������ڵ㣬����ŷֱ�Ϊs1��s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//----- ��Ҷ�ӵ���������ÿ���ַ���huffman coding -----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));			//����n���ַ������ͷָ������
	cd = (char *)malloc(n * sizeof(char));					//���������Ĺ����ռ�
	cd[n - 1] = '\0';										//���������
	for (i = 1; i < n; ++i) {								//����ַ���huffman coding
		start = n - 1;										//���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//��Ҷ�ӵ���������huffman coding
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));		//Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);							//��cd���Ʊ��뵽HC
	}
	free(cd);		//�ͷŹ����ռ�
}//HuffmanCoding

void main() {
	return;
}
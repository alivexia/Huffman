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

//--------huffman tree的编码存储表示---------
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;               //动态分配数组存储huffman tree

typedef char * *HuffmanCode;		//动态分配数组存储huffman 编码表

void Select(HuffmanTree &HT, int n, int &s1, int &s2) {
	// 在HT[1...n]选择parent为0且weight最小的两个结点，其序号分别为s1，和s2
	int i;
	s1 = s2 = 0;
	for (i = 1; i <= n && (s1 == 0 || s2 == 0); i++) {
		if (HT[i].parent == 0) {
			if (s1 == 0) {
				s1 = i;
			}
			else {
				s2 = i;
			}
		}
	}
	if (HT[s1].weight > HT[s2].weight) {
		s1 = s1 + s2;
		s2 = s1 - s2;
		s1 = s1 - s2;
	}
	for (; i <= n; i++) {
		if (HT[i].parent == 0) {
			if (HT[i].weight < HT[s2].weight) {
				if (HT[i].weight < HT[s1].weight) {
					s2 = s1;
					s1 = i;
				}
				else {
					s2 = i;
				}
			}
		}
	}
}// Select

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int * w, int n) {
	//w存放n个字符的权值（均>0),构造HT，并求出n个字符的huffman coding
	int m, i, c ,s1 ,s2 ,start ,f ;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0号单元未使用
	for (p = HT ,i = 1; i <= n; ++i, ++p, ++w)
		* p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		* p = { 0, 0, 0, 0 };
	for (i = n + 1; i < m; ++i) {		//建huffman tree
		//在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号分别为s1和s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//----- 从叶子到根逆向求每个字符的huffman coding -----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));		// 分配n个字符编码的头指针向量
	cd = (char *)malloc(n * sizeof(char));			// 分配求编码的工作空间
	cd[n - 1] = '\0';								// 编辑结束符
	for (i = 1; i <= n; ++i) {						// 这个字符求赫夫曼编码
		start = n - 1;								// 编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {	// 从叶子到根逆向求编码
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));	// 为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);				// 从cd复制编码（串）到HC
	}
	free(cd);//释放工作空间
}//HuffmanCoding

void main() {
	char select;

	printf("输入Q退出，按任意键继续：\n");
	scanf("%c", &select);
	while (select != 'Q'){
		int n;
		int *w;
		char *letter;
		char message[1000];
		HuffmanCode HC;
		HuffmanTree HT;

		printf("输入字符集大小n：");
		scanf("%d", &n);
		w = (int*)malloc(n * sizeof(int));
		letter = (char*)malloc(n * sizeof(char));
		
		
		printf("输入字符和其频度（A 64）：\n");
		for (int i = 0; i < n; i++) {	//输入字符集及权值
			getchar();
			scanf("%c", &letter[i]);
			scanf("%d", &w[i]);
		}
		HuffmanCoding(HT, HC, w, n);
		for (int i = 0, j = 0; i < n; i++) {	//输出输入的字符集及其权值
			if (j != 5) {
				printf(" %c:%-4d:%-6s ", letter[i], w[i],HC[i+1]);
				j++;
			}
			else {
				printf("\n %c:%-4d:%-6s ", letter[i], w[i], HC[i+1]);
				j = 1;
			}
		}

		printf("输入要编码的报文：");
		scanf("%s", message);
		for (int i = 0; i < strlen(message); i++) {
			for (int j = 0; j < n; j++)
				if (letter[j] == message[i])
					printf("%s", HC[j]);
		}

		printf("\n输入Q退出，按任意键继续：");
		scanf("%c", &select);
	}	
	exit(1);
}
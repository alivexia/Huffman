#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//--------huffman tree的编码存储表示---------
typedef struct {
	int weight;
	char ch;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;               //动态分配数组存储huffman tree

typedef char * *HuffmanCode;		//动态分配数组存储huffman 编码表

void Select(HuffmanTree &HT, int n, int &s1, int &s2) {
	// 在HT[1...n]选择parent为0且weight最小的两个结点，其序号分别为s1，和s2
		s1 = 99999;
		s2 = 99999;
		int temp = 99999;
		
		for (int i = 1; i <= n; i++)
		{
			if (temp > HT[i].weight && HT[i].parent == 0)
			{
				s1 = i;
				temp = HT[i].weight;
			}
		}
		temp = 99999;
		HT[s1].parent = 9999;
		for (int i = 1; i <= n; i++)
		{
			if (temp > HT[i].weight && HT[i].parent == 0)
			{
				s2 = i;
				temp = HT[i].weight;
			}
		}
		if (s1 > s2)
		{
			temp = s1;
			s1 = s2;
			s2 = temp;
		}
}// Select

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int * w, char *ch, int n) {
	//w存放n个字符的权值（均>0),构造HT，并求出n个字符的huffman coding
	int m, i, c ,s1 ,s2 ,start ,f ;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0号单元未使用
	for (p = HT + 1,i = 1; i <= n; ++i, ++p, ++w, ++ch)
		* p = { *w, *ch, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		* p = { 0,'0', 0, 0, 0 };
	for (i = n + 1; i <= m; ++i) {		//建huffman tree
		//在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号分别为s1和s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].ch = '0';
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

void decode(HuffmanTree HT,int n)//依次读入电文，根据哈夫曼树译码
{
	int i, j = 0;
	char ch[10240];
	char endflag = '\n';    //电文结束标志取2
	i = n * 2 - 1;             //从根结点开始往下搜索
	printf("输入发送的编码(按下回车结束)：");
	gets_s(ch);
	printf("译码后的字符为");
	while (ch[j] != '\0')
	{
		if (ch[j] == '0')
			i = HT[i].lchild;   //走向左孩子
		else
			i = HT[i].rchild;   //走向右孩子
		if (HT[i].lchild == 0)     //tree[i]是叶结点
		{
			printf("%c", HT[i].ch);
			i = n * 2 -1;      //回到根结点
		}
		j++;
	}
	printf("\n");
}//decode


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
		HuffmanCoding(HT, HC, w, letter, n);
		for (int i = 0, j = 0; i < n; i++) {	//输出输入的字符集及其权值
			if (j != 5) {
				printf(" %c:%-4d:%-4s ", letter[i], w[i],HC[i+1]);
				j++;
			}
			else {
				printf("\n %c:%-4d:%-4s ", letter[i], w[i], HC[i+1]);
				j = 1;
			}
		}
		
		printf("\n输入要编码的报文：");
		getchar();
		gets_s(message);
		for (int i = 0; i < strlen(message); i++) {
			for (int j = 0; j < n; j++)
				if (letter[j] == message[i])
					printf("%s", HC[j+1]);
		}
		printf("\n");

		decode(HT, n);


		printf("\n输入Q退出，按任意键继续：");
		scanf("%c", &select);
	}	
	exit(1);
}
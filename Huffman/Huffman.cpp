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

void Select(HuffmanTree &HT, int n, int &s1, int &s2) {
	// ��HT[1...n]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1����s2
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
	//w���n���ַ���Ȩֵ����>0),����HT�������n���ַ���huffman coding
	int m, i, c ,s1 ,s2 ,start ,f ;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0�ŵ�Ԫδʹ��
	for (p = HT ,i = 1; i <= n; ++i, ++p, ++w)
		* p = { *w, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		* p = { 0, 0, 0, 0 };
	for (i = n + 1; i < m; ++i) {		//��huffman tree
		//��HT[1..i-1]ѡ��parentΪ0��weight��С�������ڵ㣬����ŷֱ�Ϊs1��s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//----- ��Ҷ�ӵ���������ÿ���ַ���huffman coding -----
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));		// ����n���ַ������ͷָ������
	cd = (char *)malloc(n * sizeof(char));			// ���������Ĺ����ռ�
	cd[n - 1] = '\0';								// �༭������
	for (i = 1; i <= n; ++i) {						// ����ַ���շ�������
		start = n - 1;								// ���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {	// ��Ҷ�ӵ������������
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));	// Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);				// ��cd���Ʊ��루������HC
	}
	free(cd);//�ͷŹ����ռ�
}//HuffmanCoding

void main() {
	char select;

	printf("����Q�˳����������������\n");
	scanf("%c", &select);
	while (select != 'Q'){
		int n;
		int *w;
		char *letter;
		char message[1000];
		HuffmanCode HC;
		HuffmanTree HT;

		printf("�����ַ�����Сn��");
		scanf("%d", &n);
		w = (int*)malloc(n * sizeof(int));
		letter = (char*)malloc(n * sizeof(char));
		
		
		printf("�����ַ�����Ƶ�ȣ�A 64����\n");
		for (int i = 0; i < n; i++) {	//�����ַ�����Ȩֵ
			getchar();
			scanf("%c", &letter[i]);
			scanf("%d", &w[i]);
		}
		HuffmanCoding(HT, HC, w, n);
		for (int i = 0, j = 0; i < n; i++) {	//���������ַ�������Ȩֵ
			if (j != 5) {
				printf(" %c:%-4d:%-6s ", letter[i], w[i],HC[i+1]);
				j++;
			}
			else {
				printf("\n %c:%-4d:%-6s ", letter[i], w[i], HC[i+1]);
				j = 1;
			}
		}

		printf("����Ҫ����ı��ģ�");
		scanf("%s", message);
		for (int i = 0; i < strlen(message); i++) {
			for (int j = 0; j < n; j++)
				if (letter[j] == message[i])
					printf("%s", HC[j]);
		}

		printf("\n����Q�˳����������������");
		scanf("%c", &select);
	}	
	exit(1);
}
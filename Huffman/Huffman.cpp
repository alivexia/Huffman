#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//--------huffman tree�ı���洢��ʾ---------
typedef struct {
	int weight;
	char ch;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;               //��̬��������洢huffman tree

typedef char * *HuffmanCode;		//��̬��������洢huffman �����

void Select(HuffmanTree &HT, int n, int &s1, int &s2) {
	// ��HT[1...n]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1����s2
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
	//w���n���ַ���Ȩֵ����>0),����HT�������n���ַ���huffman coding
	int m, i, c ,s1 ,s2 ,start ,f ;
	HuffmanTree p;
	char *cd;
	if (n <= 1)
		return;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0�ŵ�Ԫδʹ��
	for (p = HT + 1,i = 1; i <= n; ++i, ++p, ++w, ++ch)
		* p = { *w, *ch, 0, 0, 0 };
	for (; i <= m; ++i, ++p)
		* p = { 0,'0', 0, 0, 0 };
	for (i = n + 1; i <= m; ++i) {		//��huffman tree
		//��HT[1..i-1]ѡ��parentΪ0��weight��С�������ڵ㣬����ŷֱ�Ϊs1��s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].ch = '0';
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

void decode(HuffmanTree HT,int n)//���ζ�����ģ����ݹ�����������
{
	int i, j = 0;
	char ch[10240];
	char endflag = '\n';    //���Ľ�����־ȡ2
	i = n * 2 - 1;             //�Ӹ���㿪ʼ��������
	printf("���뷢�͵ı���(���»س�����)��");
	gets_s(ch);
	printf("�������ַ�Ϊ");
	while (ch[j] != '\0')
	{
		if (ch[j] == '0')
			i = HT[i].lchild;   //��������
		else
			i = HT[i].rchild;   //�����Һ���
		if (HT[i].lchild == 0)     //tree[i]��Ҷ���
		{
			printf("%c", HT[i].ch);
			i = n * 2 -1;      //�ص������
		}
		j++;
	}
	printf("\n");
}//decode


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
		HuffmanCoding(HT, HC, w, letter, n);
		for (int i = 0, j = 0; i < n; i++) {	//���������ַ�������Ȩֵ
			if (j != 5) {
				printf(" %c:%-4d:%-4s ", letter[i], w[i],HC[i+1]);
				j++;
			}
			else {
				printf("\n %c:%-4d:%-4s ", letter[i], w[i], HC[i+1]);
				j = 1;
			}
		}
		
		printf("\n����Ҫ����ı��ģ�");
		getchar();
		gets_s(message);
		for (int i = 0; i < strlen(message); i++) {
			for (int j = 0; j < n; j++)
				if (letter[j] == message[i])
					printf("%s", HC[j+1]);
		}
		printf("\n");

		decode(HT, n);


		printf("\n����Q�˳����������������");
		scanf("%c", &select);
	}	
	exit(1);
}
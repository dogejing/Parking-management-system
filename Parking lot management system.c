#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <io.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

unsigned int n = 0; 

typedef struct Qnode  //�ڵ�ṹ 
{
	char plate_num[20];
	int stop_num;
	clock_t start;
	time_t now_time; 
	clock_t end;
	struct Qnode *next;
}qnode,* qnodeptr;

typedef struct       //��������ṹ 
{
	qnodeptr front,rear;
}linkq;

/* ����һ���ն���Q */
int creat_newq(linkq *q)
{ 
	q->front=q->rear=(qnodeptr)malloc(sizeof(qnode));
	if(!q->front)
		exit(OVERFLOW);
	q->front->next=NULL;
	return OK;
}


/*��Ӳ���*/
int  in_q(linkq *q,int ety_num)
{
	qnodeptr s = (qnodeptr)malloc(sizeof(qnode));
	
	if(n == 5)
	{
		printf("��λ���ˣ�\n");
		return 0;
	}
	if(!s)
	{
		exit(OVERFLOW);
	}
	printf("���복�ƺţ�");
//	getchar();
	gets(s->plate_num);
	s->now_time = time(NULL);
	s->stop_num = ety_num;
	s->start = clock();
	s->next =NULL;
	q->rear->next = s;
	q->rear = s;
	n++;
	
	return OK; 
} 

/*����*/
int out_q(linkq *q)
{
	qnodeptr p;
	int out_num;
	
	if(n == 0)
	{
		printf("��λ���ˣ�\n");
		return 0;
	}
	if(q->front == q->rear)
	{
		return ERROR;
	}
	p = q->front->next;
	printf("�ƺ�Ϊ%s\n",p->plate_num);
	printf("�ճ���λΪ%d\n",p->stop_num);
	p->end = clock();
	printf("ͣ��ʱ��Ϊ%ds\n",(p->end - p->start)/CLK_TCK);
	out_num = p->stop_num;
	q->front->next = p->next;
	if(q->rear == p)
	{
		q->rear = q->front;
	}
	free (p);
	n--;
	
	return out_num;
}

int print_info(linkq *q)
{
	qnode *p1,*p2;
	char c;
	
	printf("\n"); 
	printf("���ͣ����ȫ����Ϣ��\n");
	printf("ͣ������Ϊ��%d\n",n);
	printf("ʹ�õĳ�λΪ��");
	p1 = q->front->next;
	while(p1)
	{
		printf("%d  ",p1->stop_num);
		p1 = p1->next;
	}
	printf("\n"); 
	printf("�Ƿ�鿴��ϸ��Ϣ����y ��n��");
	scanf("%c",&c);
	getchar(); 
	if(c == 'n')
	{
		return 0;
	}
	else if(c == 'y')
	{
		p2 = q->front->next;
		while(p2)
		{
			printf("\n");
			printf("���ƣ�%s  \n",p2->plate_num);
			printf("��λ��%d  \n",p2->stop_num);
			printf("���ʱ��");
			printf(ctime(&(p2->now_time)));
			printf("\n");
			p2 = p2->next;
		}
	}
	else
	{
		printf("��������˳�");
		return 0; 
	}
}

 
int order()
{
	char s;
	int a[5];
	unsigned int i,j,k =0;
	linkq q;
//	qnode *p;
//	int ety_num;
	
	creat_newq(&q);
	for(i=0;i<5;i++)
	{
		a[i] = i+1;
	} 
	printf("ͣ��������p������������o,�鿴��Ϣ����s���˳�ϵͳ����q\n"); 
	while(1)
	{
		printf("����ָ�");
		scanf("%c",&s);
		getchar();
		switch (s)
		{
			case 'p': in_q(&q,a[k++]);
						break;
			case 'o':  k=out_q(&q);
						k--; 
						break;
			case 'q': exit(1);
			case 's': print_info(&q);
						break;
			default: printf("�������\n");
			         break; 
		}
	}
}

int main()
{	
	order();
}

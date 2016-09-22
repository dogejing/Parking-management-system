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

typedef struct Qnode  //节点结构 
{
	char plate_num[20];
	int stop_num;
	clock_t start;
	time_t now_time; 
	clock_t end;
	struct Qnode *next;
}qnode,* qnodeptr;

typedef struct       //队列链表结构 
{
	qnodeptr front,rear;
}linkq;

/* 构造一个空队列Q */
int creat_newq(linkq *q)
{ 
	q->front=q->rear=(qnodeptr)malloc(sizeof(qnode));
	if(!q->front)
		exit(OVERFLOW);
	q->front->next=NULL;
	return OK;
}


/*入队操作*/
int  in_q(linkq *q,int ety_num)
{
	qnodeptr s = (qnodeptr)malloc(sizeof(qnode));
	
	if(n == 5)
	{
		printf("车位满了！\n");
		return 0;
	}
	if(!s)
	{
		exit(OVERFLOW);
	}
	printf("输入车牌号：");
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

/*出队*/
int out_q(linkq *q)
{
	qnodeptr p;
	int out_num;
	
	if(n == 0)
	{
		printf("车位空了！\n");
		return 0;
	}
	if(q->front == q->rear)
	{
		return ERROR;
	}
	p = q->front->next;
	printf("牌号为%s\n",p->plate_num);
	printf("空出车位为%d\n",p->stop_num);
	p->end = clock();
	printf("停车时间为%ds\n",(p->end - p->start)/CLK_TCK);
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
	printf("输出停车场全部信息：\n");
	printf("停车数量为：%d\n",n);
	printf("使用的车位为：");
	p1 = q->front->next;
	while(p1)
	{
		printf("%d  ",p1->stop_num);
		p1 = p1->next;
	}
	printf("\n"); 
	printf("是否查看详细信息？是y 否n：");
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
			printf("车牌：%s  \n",p2->plate_num);
			printf("车位：%d  \n",p2->stop_num);
			printf("入库时间");
			printf(ctime(&(p2->now_time)));
			printf("\n");
			p2 = p2->next;
		}
	}
	else
	{
		printf("输入错误！退出");
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
	printf("停车请输入p，出车请输入o,查看信息输入s，退出系统输入q\n"); 
	while(1)
	{
		printf("输入指令：");
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
			default: printf("输入错误！\n");
			         break; 
		}
	}
}

int main()
{	
	order();
}

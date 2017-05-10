#include<iostream>
#include<stdio.h>
using namespace std;

typedef struct Node List;
struct Node
{
	char key;
	List * next;

};

List * myhead;

void InserNode(List * node)
{
	if(NULL == myhead)
		{
			myhead = node;
			myhead->key = node->key;

		}
	else
		{
			node->next = myhead;
			myhead = node;

		}
			
}

List *makeNode(char key)
{
	List *p = new List;
	p->key = key;
	p->next = NULL;

	return p;
}
List* reverse(List *n)
{
	if(!n || !n->next) //判断链表是否为空，为空即退出。
	{
		return n;
	}
	List *head= n->next;  //保存头结点
	List *cur = n;  //当前处理结点
	List *tmp;
	//printf("cur->key = %d\n",cur->key);
	cur->next = NULL; //头结点的指针指空，转换后变尾结点
	while ( NULL != head->next ) //循环直到 cur.next 为空
	{
		tmp = head->next;
		head->next = cur;
		cur = head;
		head = tmp;
		//printf("cur->key = %d\n",cur->key);
	}
	head->next = cur;
	return myhead = head;  //f 返回头指针m
}
void showAll()
{
	for(List*p = myhead;p != NULL;p = p->next)
		{
			printf("p->key = %d\n",p->key);
		}


}
int main(int argc, char *argv[])
{
	List * p;
	for(int i = 1; i<= 10; i++)
		{
			p = makeNode(i);
			
			if(!p)
				cout << p->key << endl;
			InserNode(p);
		}

	showAll();
	cout << endl;
	reverse(myhead);
	showAll();

	return 0;
}

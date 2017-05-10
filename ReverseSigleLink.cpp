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
	if(!n || !n->next) //�ж������Ƿ�Ϊ�գ�Ϊ�ռ��˳���
	{
		return n;
	}
	List *head= n->next;  //����ͷ���
	List *cur = n;  //��ǰ������
	List *tmp;
	//printf("cur->key = %d\n",cur->key);
	cur->next = NULL; //ͷ����ָ��ָ�գ�ת�����β���
	while ( NULL != head->next ) //ѭ��ֱ�� cur.next Ϊ��
	{
		tmp = head->next;
		head->next = cur;
		cur = head;
		head = tmp;
		//printf("cur->key = %d\n",cur->key);
	}
	head->next = cur;
	return myhead = head;  //f ����ͷָ��m
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

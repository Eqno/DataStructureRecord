#include <iostream>
using namespace std;

class Num
{
	public:
	int symbol = 1;
	struct Node
	{
		int val;
		Node *pre, *nxt;
	};
	Node *head = nullptr, *tail = nullptr;
	Num() {}
	Num(int num)
	{
		if (num == 0)
		{
			head = tail = new (Node) {0};
			return ;
		}
		if (num < 0)
		{
			symbol = -1;
			num = -num;
		}
		int s = 0;
		while (num)
		{
			Node *node = new (Node) {num%10};
			if (s == 0)
			{
				head = tail = node;
				s = 1;
			}
			else
			{
				head->pre = node;
				node->nxt = head;
				head = head->pre;
			}
			num /= 10;
		}
	}
	bool readNum()
	{
		int c = 0, s = 0, f = 0;
		while ((c=getchar()) != '\n')
		{
			
			if (c == '-')
			{
				symbol = -1;
				continue;
			}
			if (f==0 && c>='0' && c<='9')
			{
				Node *node = new (Node) {c-'0'};
				if (s == 0)
				{
					head = tail = node;
					s = 1;
				}
				else
				{
					tail->nxt = node;
					node->pre = tail;
					tail = tail->nxt;
				}
			}
			else f = 1;
		}
		return !f;
	}
	void printNum()
	{
		if (symbol == -1) putchar('-');
		for (Node *now=head; now; now=now->nxt)
			printf("%d", now->val);
		putchar('\n');
	}
	void printNum(bool rever)
	{
		if (rever)
		{
			if (symbol == -1) putchar('-');
			for (Node *now=tail; now; now=now->pre)
				printf("%d", now->val);
			putchar('\n');
		}
		else printNum();
	}
private:
	bool cmpNum(Num *num)
	{
		Node *a = head, *b = num->head;
		int la = 0, lb = 0;
		while (a || b)
		{
			if (a) a = a->nxt, la ++;
			if (b) b = b->nxt, lb ++;
		}
		if (la > lb) return false;
		if (la < lb) return true;
		while (a && b && a->val==b->val)
		{
			a = a->nxt;
			b = b->nxt;
		}
		if (a && b) return a->val < b->val;
		return true;
	}
public:
	bool ltNum(Num *num)
	{
		if (symbol==1 && num->symbol==1)
			return cmpNum(num);
		if (symbol==-1 && num->symbol==-1)
			return !cmpNum(num);
		if (symbol==1 && num->symbol==-1)
			return false;
		return true;
	}
	bool mtNum(Num *num) 
	{ 
		if (symbol==1 && num->symbol==1)
			return !cmpNum(num);
		if (symbol==-1 && num->symbol==-1)
			return cmpNum(num);
		if (symbol==-1 && num->symbol==1)
			return false;
		return true;
	}
private:
	void calNum(Num *num)
	{
		int f = 0, s = symbol*num->symbol;
		Node *a = tail, *b = num->tail;
		while (a || b)
		{
			if (a && b)
			{
				a->val += s*b->val + f;
				if (a->val > 9)
				{
					f = 1;
					a->val -= 10;
				}
				else if (a->val < 0)
				{
					f = -1;
					a->val += 10;
				}
				else f = 0;
				a = a->pre;
				b = b->pre;
			}
			else if (b)
			{
				int sum = s*b->val + f;
				if (sum > 9)
				{
					f = 1;
					sum -= 10;
				}
				else if (sum < 0)
				{
					f = -1;
					sum += 10;
				}
				else f = 0;
				Node *node = new (Node) {sum};
				head->pre = node;
				node->nxt = head;
				head = head->pre;
				b = b->pre;
			}
			else if (a)
			{
				a->val += f;
				if (a->val > 9)
				{
					f = 1;
					a->val -= 10;
				}
				else if (a->val < 0)
				{
					f = -1;
					a->val += 10;
				}
				else f = 0;
				a = a->pre;
			}
		}
		if (f != 0)
		{
			Node *node;
			if (f == 1) node = new (Node) {1};
			if (f == -1) node = new (Node) {-1};
			head->pre = node;
			node->nxt = head;
			head = head->pre;
		}
	}
public:
	void addNum(Num *num)
	{
		if (symbol*num->symbol == -1)
			if (cmpNum(num))

	}
};

Num *add(Num *a, Num *b)
{
	Num *c = new Num(0);
	c->addNum(a);
	c->addNum(b);
	return c;
}

int main()
{
	Num *a = new Num(), *b = new Num();
	if (a->readNum() && b->readNum())
	{
		 // a->printNum();
		 // b->printNum();
	}
	else
	{
		printf("请输入整数！");
		return 0;
	}
	a->addNum(b);
	a->printNum();
	return 0;
}

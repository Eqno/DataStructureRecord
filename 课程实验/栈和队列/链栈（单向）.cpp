#include <iostream>
#include <string>
#include <cstdlib> 
#include <cstring>
#include <algorithm>
using namespace std;

enum Status
{
	SUCCEED,
	EXISTED,
	NOT_FOUND,
	INIT_FAILD,
	EXPAND_FAILD,
	INVALID_ARGUMENTS
};
struct Node
{
	char *name;
	int val;
	Node *next;
	Node(char *name, int val)
	{
		this->name = name;
		this->val = val;
		this->next = nullptr;
	}
};
class Stack
{
public:
	Node *head;
private:
	int len;
public:
	Stack() { this->_init(); }
	int length() { return this->len; }
	void updateLength() { this->_updateLength(); }
	Node *get(int l) { return this->judgeGet(this->_get(l)); }
	int find(char *name) { return this->judgeFind(this->_find(name)); }
	int find(int val) { return this->judgeFind(this->_find(val)); }
	int find(char *name, int val) { return this->judgeFind(this->_find(name, val)); }
	void insert(int l, char *name, int val) { this->judgeInsert(this->_insert(l, name, val)); } 
	void remove(int l) { this->judgeRemove(this->_remove(l)); }
	void show() { this->judgeShow(this->_show()); }
	void show(int l) { this->judgeShow(this->_show(l)); }
	void sorted(bool (*cmp)(Node i, Node j)) { this->judgeSort(this->_sort(cmp)); }
	void reverse() { this->judgeReverse(this->_reverse()); }
	void clear() { this->judgeClear(this->_clear()); }
	void del() { this->judgeDel(this->_del()); }

	Node *top() { return this->get(this->len); }  // back
	char *getName(int l) { return this->get(l)->name; }
	int getVal(int l) { return this->get(l)->val; }
	int find(Node *e) { return this->find(e->name, e->val); }
	void insert(int l, Node *e) { this->insert(l, e->name, e->val); }
	void remove(Node *e) { this->remove(this->find(e)); }
	void remove(char *name) { this->remove(this->find(name)); }
	void removeVal(int val) { this->remove(this->find(val)); }
	void sortedVal() { this->sorted([](Node i, Node j) { return i.val < j.val; }); }

	void push(Node *e) { this->insert(1, e); }
	void push(char *name, int val) { this->insert(1, name, val); }
	void pop() { this->remove(1); }

private:
	void _init()
	{
		this->head = new Node("head", 0);
		this->len = 0;
		puts("链栈初始化成功！\n");
	}
	Node *_get(int l)
	{
		Node *p = this->head; 
		if (p==nullptr || l<1 || l>this->len) return nullptr;
		while (l --) p = p->next;
		return p;
	}
	Node *judgeGet(Node *e)
	{
		if (e == nullptr) puts("查询位置无效！\n");
		return e;
	}
	Status _insert(int l, char *name, int val)
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		if (l<1 || l>this->len+1) return INVALID_ARGUMENTS;
		while (l --> 1) p = p->next;
		Node *n = new Node(name, val);
		if (n == nullptr) return EXPAND_FAILD;
		n->next = p->next;
		p->next = n;	
		this->len ++;
		return SUCCEED;
	}
	void judgeInsert(Status st)
	{
		if (st == SUCCEED) puts("插入元素成功！\n");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("插入位置无效！\n");
		else if (st == EXPAND_FAILD) puts("空间拓展失败！\n");
		else puts("未知错误！\n");
	}
	Status _remove(int l)
	{
		Node *p = this->head; 
		if (p == nullptr) return NOT_FOUND;
		if (l<1 || l>this->len) return INVALID_ARGUMENTS;
		while (l --> 1) p = p->next;
		Node *q = p->next;
		p->next = p->next->next;
		delete q;
		this->len --;
		return SUCCEED;
	}
	void judgeRemove(Status st)
	{
		if (st == SUCCEED) puts("删除元素成功！\n");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("删除位置无效！\n");
		else puts("未知错误！\n");
	}
	int _find(char *name)
	{
		Node *p = this->head;
		if (p == nullptr) return 0;
		int cot = 1;
		while (p->next)
		{
			if (strcmp(p->next->name, name) == 0)
				return cot;
			p = p->next;
			cot ++;
		}
		return 0;
	}
	int _find(int val)
	{
		Node *p = this->head;
		if (p == nullptr) return 0;
		int cot = 1;
		while (p->next)
		{
			if (p->next->val == val)
				return cot;
			p = p->next;
			cot ++;
		}
		return 0;
	}
	int _find(char *name, int val)
	{
		Node *p = this->head;
		if (p == nullptr) return 0;
		int cot = 1;
		while (p->next)
		{
			if (strcmp(p->next->name, name)==0 && p->next->val==val)
				return cot;
			p = p->next;
			cot ++;
		}
		return 0;
	}
	int judgeFind(int st)
	{
		if (st == 0) puts("未找到该元素！\n");
		return st;
	}
	Status _show()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		while (p->next)
		{
			printf("(%s, %d)\n", p->next->name, p->next->val);
			p = p->next;
		}
		return SUCCEED;
	}
	Status _show(int l)
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		if (l<1 || l>this->len) return INVALID_ARGUMENTS;
		while (l --) p = p->next;
		printf("(%s, %d)\n", p->name, p->val);
		return SUCCEED;
	}
	void judgeShow(Status st)
	{
		if (st == SUCCEED) ;
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("查询位置无效！\n");
		else puts("未知错误！\n");
	}
	Status _sort(bool (*cmp)(Node i, Node j))
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		Node *q = p->next;
		p->next = nullptr;
		while (q)
		{
			while (p->next && cmp(*p->next, *q)) p = p->next;
			Node *t = q->next;
			q->next = p->next;
			p->next = q;
			q = t;
			p = this->head;
		}
		return SUCCEED;
	}
	void judgeSort(Status st)
	{
		if (st == SUCCEED) puts("链栈排序成功！");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _updateLength()
	{
		int cot = 0;
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		while (p->next) p = p->next, cot ++;
		this->len = cot;
		return SUCCEED;		
	}
	void judgeUpdateLength(Status st)
	{
		if (st == SUCCEED) puts("链栈长度更新成功！");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _reverse()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		p = p->next;
		this->head->next = nullptr;
		while (p)
		{
			Node *q = p->next;
			p->next  = this->head->next;
			this->head->next = p;
			if (q == nullptr) break;
			p = q;
			q = q->next;
		}
		return SUCCEED;
	}
	void judgeReverse(Status st)
	{
		if (st == SUCCEED) puts("链栈倒置成功！");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _clear()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		while (p->next)
		{
			p->next->name[0] = p->next->val = 0;
			p = p->next;
		}
		return SUCCEED;
	}
	void judgeClear(Status st)
	{
		if (st == SUCCEED) puts("链栈清空成功！");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _del()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		p = p->next;
		while (p)
		{
			Node *q = p;
			p = p->next;
			delete q;
		}
		this->len = 0;
		return SUCCEED;
	}
	void judgeDel(Status st)
	{
		if (st == SUCCEED) puts("链栈删除成功！");
		else if (st == NOT_FOUND) puts("链栈不存在！\n");
		else puts("未知错误！\n");
	}
};

void insertTest(Stack *Stack)
{
	puts("插入元素个数：");
	int len;
	cin >> len;
	puts("");
	for (int i=1; i<=len; i++)
	{
		printf("插入位置：");
		int l;
		cin >> l;
		printf("元素名称：");
		char *name = (char *)malloc(20*sizeof(char));
		cin >> name;
		printf("元素数值：");
		int val;
		cin >> val;
		if (len & 1) Stack->insert(l, name, val);  // insert(int l, char *name, int val);
		else Stack->insert(l, new Node(name, val));  // insert(int l, Node *e);
	}
}

void removeTest(Stack *Stack)
{
	puts("删除元素个数：");
	int len;
	cin >> len;
	puts("");
	for (int i=1; i<=len; i++)
	{
		if (i & 1)
		{
			printf("元素位置：");
			int l;
			cin >> l;
			Stack->remove(l);  // remove(int l);
		}
		else 
		{
			printf("元素名称：");
			char name[20];
			cin >> name;
			Stack->remove(name);  // remove(char *name);
		}
	}
}

void showTest(Stack *Stack)
{
	puts("链栈如下：");
	printf("元素个数：%d\n", Stack->length());  // length();
	printf("第一个元素：");
	Stack->show(1);  //show(int l);
	printf("第一个元素：");
	printf("(%s, %d)\n", Stack->get(1)->name, Stack->getVal(1));  // get(int l); getVal(int val);
	puts("元素列举："); 
	Stack->show();  // show();
	puts("");
}

void sortTest(Stack *Stack)
{
	puts("链栈按值排序。");
	Stack->sortedVal();  // sortedVal();
	puts("");
	showTest(Stack);
}

Stack *mergeSort(Stack *x, Stack *y, bool (*cmp)(Node i, Node j))
{
	x->sorted(cmp);
	y->sorted(cmp);
	Stack *nl = new Stack();
	Node *p = x->head, *q = y->head, *r = nl->head;
	if (p) p = p->next;
	if (q) q = q->next;
	while (p || q)
	{
		if (p && ((q&&cmp(*p, *q)) || q==nullptr))
			r = r->next = p, p = p->next;
		else r = r->next = q, q = q->next;
		nl->updateLength();
	}
	x->head = nullptr;
	y->head = nullptr;
	puts("归并完成！");
	return nl;
}

int main()
{ 
	Stack *stack = new Stack();
	puts("输入一组元素，以值为-1结束。");
	while (1)
	{
		printf("元素名称：");
		char *name = new char[20];
		cin >> name;
		printf("元素的值：");
		int val;
		cin >> val;
		if (val == -1) break;
		stack->push(name, val);
	}
	puts("\n元素出栈：");
	while (stack->length())
	{
		printf("(%s, %d)\n", stack->top()->name, stack->top()->val);
		stack->pop();
	}
	return 0;
}

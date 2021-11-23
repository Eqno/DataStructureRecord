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
	Node(char *name, int val)
	{
		this->name = name;
		this->val = val;
	}
};
class Stack
{ 
private:
	Node *head;
	int len, size;
	const static int EXPAND_SIZE = 10;	
public:
	Stack() { this->head = nullptr; this->len = this->size = 0; }
	int length() { return this->len; }
	void init(int size) { this->judgeInit(this->_init(true, size)); }
	void reInit(int size) { this->judgeInit(this->_init(false, size)); }
	Node *get(int l) { return this->judgeGet(this->_get(l), l); }
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
		
	Stack(int size) { this->head = nullptr; this->len = this->size = 0; this->init(size); }
	Node *front() { return this->get(1); }
	Node *back() { return this->get(this->len); }
	void pushBack(Node *e) { this->insert(this->len+1, e); }
	void pushBack(char *name, int val) { this->insert(this->len+1, name, val); }
	void popBack() { this->remove(this->len); }
	void pushFront(Node *e) { this->insert(1, e); }
	void pushFront(char *name, int val) { this->insert(1, name, val); }
	void popFront() { this->remove(1); }
	char *getName(int l) { return this->get(l)->name; }
	int getVal(int l) { return this->get(l)->val; }
	int find(Node *e) { return this->find(e->name, e->val); }
	void insert(int l, Node *e) { this->insert(l, e->name, e->val); }
	void remove(Node *e) { this->remove(this->find(e)); }
	void remove(char *name) { this->remove(this->find(name)); }
	void removeVal(int val) { this->remove(this->find(val)); }
	void sortedVal() { this->sorted([](Node i, Node j) { return i.val < j.val; }); }

	void push(Node *e) { this->pushBack(e); }
	void push(char *name, int val) { this->pushBack(name, val); }
	void pop() { this->popBack(); }

private:
	Status _init(bool f, int size)
	{
		if (f && this->head != nullptr)
			return EXISTED; 
		this->head = (Node *) malloc(size*sizeof(Node));
		if (this->head == nullptr)
			return INIT_FAILD;
		this->len = 0;
		this->size = size;
		return SUCCEED;
	}
	void judgeInit(Status st)
	{
		if (st == SUCCEED) puts("空间申请成功！\n");
		else if (st == EXISTED) puts("顺序栈已存在！若需重新申请，请使用 reInit() 方法。\n");
		else if (st == INIT_FAILD) puts("空间申请失败！\n");
		else puts("未知错误！\n");
	}
	Node *_get(int l)
	{
		if (this->head==nullptr || l<1 || l>this->len)
			return nullptr;
		return this->head + l - 1;
	}
	Node *judgeGet(Node *e, int l)
	{
		if (e == nullptr && l) puts("查询位置无效！\n");
		return e;
	}
	Status _insert(int l, char *name, int val)
	{
		if (l<1 || l>this->len+1)
			return INVALID_ARGUMENTS;
		if (this->len >= this->size)
		{
			this->head = (Node *) realloc(this->head, (this->size+EXPAND_SIZE)*sizeof(Node));
			if (this->head == nullptr)
				return EXPAND_FAILD;
			this->size += EXPAND_SIZE;
		}
		Node *loc = this->head+l-1;
		for (Node *p=this->back(); p && p>=loc; p--)
		{
			(p+1)->name = p->name;
			(p+1)->val = p->val;
		}
		loc->name = name;
		loc->val = val;
		this->len ++;
		return SUCCEED;
	}
	void judgeInsert(Status st)
	{
		if (st == SUCCEED) puts("插入元素成功！\n");
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("插入位置无效！\n");
		else if (st == EXPAND_FAILD) puts("空间拓展失败！\n");
		else puts("未知错误！\n");
	}
	Status _remove(int l)
	{
		if (this->head == nullptr)
			return NOT_FOUND;
		if (l<1 || l>this->len)
			return INVALID_ARGUMENTS;
		for (Node *p=this->get(l); p<=this->back(); p++)
		{
			p->name = (p+1)->name;
			p->val = (p+1)->val;
		}
		this->len --;
		return SUCCEED;
	}
	void judgeRemove(Status st)
	{
		// if (st == SUCCEED) puts("删除元素成功！\n");
		// else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		// else if (st == INVALID_ARGUMENTS) puts("删除位置无效！\n");
		// else puts("未知错误！\n");
	}
	int _find(char *name)
	{
		if (this->head == nullptr) return 0;
		for (Node *p=this->front(); p<=this->back(); p++)
			if (strcmp(p->name, name)==0)
				return p - this->front() + 1;
		return 0;
	}
	int _find(int val)
	{
		if (this->head == nullptr) return 0;
		for (Node *p=this->front(); p<=this->back(); p++)
			if (p->val==val)
				return p - this->front() + 1;
		return 0;
	}
	int _find(char *name, int val)
	{
		if (this->head == nullptr) return 0;
		for (Node *p=this->front(); p<=this->back(); p++)
			if (strcmp(p->name, name)==0 && p->val==val)
				return p - this->front() + 1;
		return 0;
	}
	int judgeFind(int st)
	{
		if (st == 0) puts("未找到该元素！\n");
		return st;
	}
	Status _show()
	{
		if (this->head == nullptr)
			return NOT_FOUND;
		for (Node *p=this->front(); p<=this->back(); p++)
			printf("(%s, %d)\n", p->name, p->val);
		return SUCCEED;
	}
	Status _show(int l)
	{
		if (this->head == nullptr)
			return NOT_FOUND;
		if (l<1 || l>this->len)
			return INVALID_ARGUMENTS;
		Node *p = this->get(l);
		printf("(%s, %d)\n", p->name, p->val);
		return SUCCEED;
	}
	void judgeShow(Status st)
	{
		if (st == SUCCEED) ;
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("查询位置无效！\n");
		else puts("未知错误！\n");
	}
	Status _sort(bool (*cmp)(Node i, Node j))
	{
		if (this->head == nullptr) return NOT_FOUND;
		sort(this->head, this->head+len, cmp);
		return SUCCEED;
	}
	void judgeSort(Status st)
	{
		if (st == SUCCEED) puts("顺序栈排序成功！");
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _clear()
	{
		if (this->head == nullptr) return NOT_FOUND;
		for (Node *p=this->front(); p<=this->back(); p++)
			p->name[0] = p->val = 0;
		this->len = 0;
		return SUCCEED;
	}
	void judgeClear(Status st)
	{
		if (st == SUCCEED) puts("顺序栈清空成功！");
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _del()
	{
		if (this->head == nullptr) return NOT_FOUND;
		delete this;
		return SUCCEED;
	}
	void judgeDel(Status st)
	{
		if (st == SUCCEED) puts("顺序栈删除成功！");
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else puts("未知错误！\n");
	}
	Status _reverse()
	{
		if (this->head == nullptr) return NOT_FOUND;
		Node *t = new Node("", 0);
		for (int i=0; i<=this->len/2; i++)
		{
			Node *p = this->head+i;
			Node *q = this->head+this->len-i-1;
			t->name = p->name;
			t->val = p->val;
			p->name = q->name;
			p->val = q->val;
			q->name = t->name;
			q->val = t->val;
		}
		return SUCCEED;
	}
		void judgeReverse(Status st)
	{
		if (st == SUCCEED) puts("顺序栈倒置成功！");
		else if (st == NOT_FOUND) puts("顺序栈不存在！\n");
		else puts("未知错误！\n");
	}
};

void insertTest(Stack *list)
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
		if (len & 1) list->insert(l, name, val);  // insert(int l, char *name, int val);
		else list->insert(l, new Node(name, val));  // insert(int l, Node *e);
	}
}

void removeTest(Stack *list)
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
			list->remove(l);  // remove(int l);
		}
		else 
		{
			printf("元素名称：");
			char name[20];
			cin >> name;
			list->remove(name);  // remove(char *name);
		}
	}
}

void showTest(Stack *list)
{
	puts("顺序栈如下：");
	printf("元素个数：%d\n", list->length());  // length();
	printf("第一个元素：");
	list->show(1);  //show(int l);
	printf("第一个元素：");
	printf("(%s, %d)\n", list->get(1)->name, list->getVal(1));  // get(int l); getVal(int val);
	puts("元素列举："); 
	list->show();  // show();
	puts("");
}

void sortTest(Stack *list)
{
	puts("顺序栈按值排序。");
	list->sortedVal();  // sortedVal();
	puts("");
	showTest(list);
}

Stack *mergeSort(Stack *x, Stack *y, bool (*cmp)(Node i, Node j))
{
	x->sorted(cmp);
	y->sorted(cmp);
	Stack *r = new Stack(x->length()+y->length());
	int cot = 1, i = 1, j = 1;
	Node *p, *q;
	while (i<=x->length() || j<=y->length())
	{
		if (i<=x->length()&&((j<=y->length()&&cmp(*(x->get(i)), *(y->get(j))))||(j>y->length())))
			p = x->get(i ++), r->insert(cot ++, p->name, p->val);
		else q = y->get(j ++), r->insert(cot ++, q->name, q->val);
	}
	puts("归并完成！");
	return r;
}

int main()
{
	Stack *stack = new Stack(10);
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
		Node *top = stack->back();
		printf("(%s, %d)\n", top->name, top->val);
		stack->pop();
	}
	return 0;
}

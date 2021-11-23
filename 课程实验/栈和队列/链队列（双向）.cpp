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
	Node *nxt, *pre;
	Node(char *name, int val)
	{
		this->name = name;
		this->val = val;
		this->nxt = nullptr;
		this->pre = nullptr;
	}
};
class Queue
{
public:
	Node *head, *tail;
private:
	int len;
public:
	Queue() { this->_init(); }
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
	
	Node *front() { return this->get(1); }
	Node *back() { return this->get(this->len); }
	void pushBack(Node *e) { this->insert(this->len+1, e); }
	void pushBack(char *name, int val) { this->insert(this->len+1, name, val); }
	void popBack() { this->remove(this->len); }
	void popFront(Node *e) { this->insert(1, e); }
	void popFront(char *name, int val) { this->insert(1, name, val); }
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
	void pop() { this->popFront(); }

private:
	void _init()
	{
		this->head = new Node("head", 0);
		this->tail = new Node("tail", 0);
		this->len = 0;
		puts("链队列初始化成功！\n");
	}
	Node *_get(int l)
	{
		if (!this->head || !this->tail || l<1 || l>this->len)
			return nullptr;
		Node *p = nullptr;
		if (l <= this->len/2)
		{
			p = this->head;
			while (l --) p = p->nxt;
		}
		else
		{
			p = this->tail;
			while (l ++<= this->len) p = p->pre;
		}
		return p;
	}
	Node *judgeGet(Node *e)
	{
		if (e == nullptr) puts("查询位置无效！\n");
		return e;
	}
	Status _insert(int l, char *name, int val)
	{
		if (!this->head || !this->tail) return NOT_FOUND;
		if (l<1 || l>this->len+1) return INVALID_ARGUMENTS;
		Node *n = new Node(name, val);
		if (! n) return EXPAND_FAILD;
		Node *p = nullptr;
		if (l <= this->len/2)
		{
			p = this->head;
			while (l --> 1) p = p->nxt;
			n->nxt = p->nxt;
			if (p->nxt) p->nxt->pre = n;
			else this->tail->pre = n;
			p->nxt = n;
			if (p != this->head) n->pre = p;
			else n->pre = nullptr;
		}
		else 
		{
			p = this->tail;
			while (l ++< this->len) p = p->pre;
			n->pre = p->pre;
			if (p->pre) p->pre->nxt = n;
			else this->head->nxt = n;
			p->pre = n;
			if (p != this->tail) n->nxt = p;
			else n->nxt = nullptr;
		}
		this->len ++;
 		return SUCCEED;
	}
	void judgeInsert(Status st)
	{
		if (st == SUCCEED) puts("插入元素成功！\n");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("插入位置无效！\n");
		else if (st == EXPAND_FAILD) puts("空间拓展失败！\n");
		else puts("未知错误！\n");
	}
	Status _remove(int l)
	{
		if (!this->head || !this->tail) return NOT_FOUND;
		if (l<1 || l>this->len) return INVALID_ARGUMENTS;
		Node *p = nullptr, *q = nullptr;
		if (l <= this->len/2)
		{
			p = this->head;
			while (l --> 1) p = p->nxt;
			q = p->nxt;
			if (p->nxt->nxt)
			{
				if (p != this->head) p->nxt->nxt->pre = p;
				else p->nxt->nxt->pre = nullptr;
			}
			p->nxt = p->nxt->nxt;
		}
		else 
		{
			p = this->tail;
			while (l ++< this->len) p = p->pre;
			q = p->pre;
			if (p->pre->pre)
			{
				if (p != this->tail) p->pre->pre->nxt = p;
				else p->pre->pre->nxt = nullptr;
			}
			p->pre = p->pre->pre;
		}
		delete q;
		this->len --;
		return SUCCEED;
	}
	void judgeRemove(Status st)
	{
		if (st == SUCCEED) puts("删除元素成功！\n");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("删除位置无效！\n");
		else puts("未知错误！\n");
	}
	int _find(char *name)
	{
		Node *p = this->head, *q = this->tail;
		if (!p || !q) return 0;
		int left = 1, right = this->len;
		while (p->nxt && q->pre)
		{
			if (!strcmp(p->nxt->name, name)) return left;
			if (!strcmp(q->pre->name, name)) return right;			
			p = p->nxt, q = q->pre;
			left ++, right --;
		}
		return 0;
	}
	int _find(int val)
	{
		Node *p = this->head, *q = this->tail;
		if (!p || !q) return 0;
		int left = 1, right = this->len;
		while (p->nxt && q->pre)
		{
			if (p->nxt->val, val) return left;
			if (q->pre->val, val) return right;			
			p = p->nxt, q = q->pre;
			left ++, right --;
		}
		return 0;
	}
	int _find(char *name, int val)
	{
		Node *p = this->head, *q = this->tail;
		if (!p || !q) return 0;
		int left = 1, right = this->len;
		while (p->nxt && q->pre)
		{
			if ((!strcmp(p->nxt->name, name)) && (p->nxt->val, val)) return left;
			if ((!strcmp(q->pre->name, name)) && (q->pre->val, val)) return right;			
			p = p->nxt, q = q->pre;
			left ++, right --;
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
		while (p->nxt)
		{
			printf("(%s, %d)\n", p->nxt->name, p->nxt->val);
			p = p->nxt;
		}
		return SUCCEED;
	}
	Status _show(int l)
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		if (l<1 || l>this->len) return INVALID_ARGUMENTS;
		while (l --) p = p->nxt;
		printf("(%s, %d)\n", p->name, p->val);
		return SUCCEED;
	}
	void judgeShow(Status st)
	{
		if (st == SUCCEED) ;
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else if (st == INVALID_ARGUMENTS) puts("查询位置无效！\n");
		else puts("未知错误！\n");
	}
	Status _sort(bool (*cmp)(Node i, Node j))
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		Node *q = p->nxt;
		p->nxt = nullptr;
		while (q)
		{
			while (p->nxt && cmp(*p->nxt, *q)) p = p->nxt;
			Node *t = q->nxt;
			q->nxt = p->nxt;
			p->nxt = q;
			q = t;
			p = this->head;
		}
		return SUCCEED;
	}
	void judgeSort(Status st)
	{
		if (st == SUCCEED) puts("链队列排序成功！");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else puts("未知错误！\n");
	}
	Status _updateLength()
	{
		int cot = 0;
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		while (p->nxt) p = p->nxt, cot ++;
		this->len = cot;
		return SUCCEED;;
	}
	void judgeUpdateLength(Status st)
	{
		if (st == SUCCEED) puts("链队列长度更新成功！");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else puts("未知错误！\n");
	}
	Status _reverse()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		p = p->nxt;
		this->head->nxt = nullptr;
		while (p)
		{
			Node *q = p->nxt;
			p->nxt  = this->head->nxt;
			this->head->nxt = p;
			if (q == nullptr) break;
			p = q;
			q = q->nxt;
		}
		return SUCCEED;
	}
	void judgeReverse(Status st)
	{
		if (st == SUCCEED) puts("链队列倒置成功！");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else puts("未知错误！\n");
	}
	Status _clear()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		while (p->nxt)
		{
			p->nxt->name[0] = p->nxt->val = 0;
			p = p->nxt;
		}
		return SUCCEED;
	}
	void judgeClear(Status st)
	{
		if (st == SUCCEED) puts("链队列清空成功！");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else puts("未知错误！\n");
	}
	Status _del()
	{
		Node *p = this->head;
		if (p == nullptr) return NOT_FOUND;
		p = p->nxt;
		while (p)
		{
			Node *q = p;
			p = p->nxt;
			delete q;
		}
		this->len = 0;
		return SUCCEED;
	}
	void judgeDel(Status st)
	{
		if (st == SUCCEED) puts("链队列删除成功！");
		else if (st == NOT_FOUND) puts("链队列不存在！\n");
		else puts("未知错误！\n");
	}
};

void insertTest(Queue *list)
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

void removeTest(Queue *list)
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

void showTest(Queue *list)
{
	puts("链队列如下：");
	printf("元素个数：%d\n", list->length());  // length();
	// printf("第一个元素：");
	// list->show(1);  //show(int l);
	// printf("第一个元素：");
	// printf("(%s, %d)\n", list->get(1)->name, list->getVal(1));  // get(int l); getVal(int val);
	puts("元素列举："); 
	list->show();  // show();
	puts("");
}

void sortTest(Queue *list)
{
	puts("链队列按值排序。");
	list->sortedVal();  // sortedVal();
	puts("");
	showTest(list);
}

Queue *mergeSort(Queue *x, Queue *y, bool (*cmp)(Node i, Node j))
{
	x->sorted(cmp), y->sorted(cmp);
	Queue *nl = new Queue();
	Node *p = x->head, *q = y->head, *r = nl->head;
	if (p) p = p->nxt; if (q) q = q->nxt;
	while (p || q)
	{
		if (p && ((q&&cmp(*p, *q)) || q==nullptr))
			r = r->nxt = p, p = p->nxt;
		else r = r->nxt = q, q = q->nxt;
		nl->updateLength();
	}
	x->head = nullptr, y->head = nullptr;
	puts("归并完成！");
	return nl;
}

int main()
{ 
	Queue *queue = new Queue();
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
		queue->push(name, val);
	}
	puts("\n元素出栈：");
	while (queue->length())
	{
		Node *tmp = queue->front();
		printf("(%s, %d)\n", tmp->name, tmp->val);
		queue->pop();
	}
	return 0;
}

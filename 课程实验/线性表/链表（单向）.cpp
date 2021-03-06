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
class List
{
public:
	Node *head;
private:
	int len;
public:
	List() { this->_init(); }
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
	
	// Node *front() { return this->get(1); }
	// Node *back() { return this->get(this->len); }
	// void pushBack(Node *e) { this->insert(this->len+1, e); }
	// void pushBack(char *name, int val) { this->insert(this->len+1, name, val); }
	// void popBack() { this->remove(this->len); }
	// void pushFront(Node *e) { this->insert(1, e); }
	// void pushFront(char *name, int val) { this->insert(1, name, val); }
	// void popFront() { this->remove(1); }
	char *getName(int l) { return this->get(l)->name; }
	int getVal(int l) { return this->get(l)->val; }
	int find(Node *e) { return this->find(e->name, e->val); }
	void insert(int l, Node *e) { this->insert(l, e->name, e->val); }
	void remove(Node *e) { this->remove(this->find(e)); }
	void remove(char *name) { this->remove(this->find(name)); }
	void removeVal(int val) { this->remove(this->find(val)); }
	void sortedVal() { this->sorted([](Node i, Node j) { return i.val < j.val; }); }
private:
	// init
	void _init()
	{
		this->head = new Node("head", 0);
		this->len = 0;
		puts("????????????????????????\n");
	}
	// get
	Node *_get(int l)
	{
		Node *p = this->head; 
		if (p==nullptr || l<1 || l>this->len) return nullptr;
		while (l --) p = p->next;
		return p;
	}
	Node *judgeGet(Node *e)
	{
		if (e == nullptr) puts("?????????????????????\n");
		return e;
	}
	// insert
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
		if (st == SUCCEED) puts("?????????????????????\n");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else if (st == INVALID_ARGUMENTS) puts("?????????????????????\n");
		else if (st == EXPAND_FAILD) puts("?????????????????????\n");
		else puts("???????????????\n");
	}
	// remove
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
		if (st == SUCCEED) puts("?????????????????????\n");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else if (st == INVALID_ARGUMENTS) puts("?????????????????????\n");
		else puts("???????????????\n");
	}
	// find
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
		if (st == 0) puts("?????????????????????\n");
		return st;
	}
	//show
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
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else if (st == INVALID_ARGUMENTS) puts("?????????????????????\n");
		else puts("???????????????\n");
	}
	// sort
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
		if (st == SUCCEED) puts("?????????????????????");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else puts("???????????????\n");
	}
	// updateLength
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
		if (st == SUCCEED) puts("???????????????????????????");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else puts("???????????????\n");
	}
	// reverse
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
		if (st == SUCCEED) puts("?????????????????????");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else puts("???????????????\n");
	}
	// clear
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
		if (st == SUCCEED) puts("?????????????????????");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else puts("???????????????\n");
	}
	// del
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
		if (st == SUCCEED) puts("?????????????????????");
		else if (st == NOT_FOUND) puts("??????????????????\n");
		else puts("???????????????\n");
	}
};

void insertTest(List *list)
{
	puts("?????????????????????");
	int len;
	cin >> len;
	puts("");
	for (int i=1; i<=len; i++)
	{
		printf("???????????????");
		int l;
		cin >> l;
		printf("???????????????");
		char *name = (char *)malloc(20*sizeof(char));
		cin >> name;
		printf("???????????????");
		int val;
		cin >> val;
		if (len & 1) list->insert(l, name, val);  // insert(int l, char *name, int val);
		else list->insert(l, new Node(name, val));  // insert(int l, Node *e);
	}
}

void removeTest(List *list)
{
	puts("?????????????????????");
	int len;
	cin >> len;
	puts("");
	for (int i=1; i<=len; i++)
	{
		if (i & 1)
		{
			printf("???????????????");
			int l;
			cin >> l;
			list->remove(l);  // remove(int l);
		}
		else 
		{
			printf("???????????????");
			char name[20];
			cin >> name;
			list->remove(name);  // remove(char *name);
		}
	}
}

void showTest(List *list)
{
	puts("???????????????");
	printf("???????????????%d\n", list->length());  // length();
	printf("??????????????????");
	list->show(1);  //show(int l);
	printf("??????????????????");
	printf("(%s, %d)\n", list->get(1)->name, list->getVal(1));  // get(int l); getVal(int val);
	puts("???????????????"); 
	list->show();  // show();
	puts("");
}

void sortTest(List *list)
{
	puts("?????????????????????");
	list->sortedVal();  // sortedVal();
	puts("");
	showTest(list);
}

List *mergeSort(List *x, List *y, bool (*cmp)(Node i, Node j))
{
	x->sorted(cmp);
	y->sorted(cmp);
	List *nl = new List();
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
	puts("???????????????");
	return nl;
}

int main()
{ 
	List *list = new List();  // List(); 
	
	insertTest(list);
	showTest(list);
	removeTest(list);
	showTest(list);
	
	// puts("????????????????????????");
	// cin >> size;
	// list->reInit(size);
	// showTest(list);
	
	puts("??????2?????????");
	List *list2 = new List();
	for (int i=1; i<=3; i++)
	{
		char *name = (char *)malloc(20*sizeof(char));
		name[0] = 'a'+i;
		name[1] = 0;
		list2->insert(i, name, (3-i+1)*2);
		// list2->insert(i, name, i*2);
	}
	showTest(list2);
	
	puts("?????????");
	List *list3 = mergeSort(list, list2, [](Node i, Node j) { return i.val < j.val; });
	puts("?????????");
	list3->reverse();
	showTest(list3);
	list3->clear();
	list3->del();
	return 0;
}

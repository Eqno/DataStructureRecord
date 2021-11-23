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
class Queue
{ 
private:
	Node *head, *start;
	int len, size;
	inline Node *mod(Node *p) 
	{
		if (p < this->head) return p + this->size - 1;
		if (p >= this->head+this->size) return p - this->size;
		return p;
	}
public:
	Queue() { this->head = nullptr; this->len = this->size = 0; }
	int length() { return this->len; }
	void init(int size) { this->judgeInit(this->_init(true, size)); }
	void reInit(int size) { this->judgeInit(this->_init(false, size)); }
	Node *front() { return this->start; }
	Node *back() { return (this->start+this->len-1); }
	void push(char *name, int val) { this->judgePush(this->_push(name, val)); } 
	Node *pop() { return this->_pop(); }
	void show() { this->judgeShow(this->_show()); }
	void clear() { this->judgeClear(this->_clear()); }
	void del() { this->judgeDel(this->_del()); }

	Queue(int size) { this->reInit(size); }
	void push(Node *e) { this->push(e->name, e->val); }
private:
	Status _init(bool f, int size)
	{
		if (f && this->head != nullptr) return EXISTED; 
		this->head = (Node *) malloc(size*sizeof(Node));
		if (this->head == nullptr) return INIT_FAILD;
		this->len = 0, this->size = size, this->start = head;
		return SUCCEED;
	}
	void judgeInit(Status st)
	{
		if (st == SUCCEED) puts("空间申请成功！\n");
		else if (st == EXISTED) puts("顺序队列已存在！若需重新申请，请使用 reInit() 方法。\n");
		else if (st == INIT_FAILD) puts("空间申请失败！\n");
		else puts("未知错误！\n");
	}
	Status _push(char *name, int val)
	{
		if (this->head == nullptr) return NOT_FOUND;
		if (this->len >= this->size) return EXPAND_FAILD;
		Node *p = mod(this->start+this->len);
		p->name = name;
		p->val = val;
		this->len ++;
		return SUCCEED;
	}
	void judgePush(Status st)
	{
		if (st == SUCCEED) puts("push成功！\n");
		else if (st == NOT_FOUND) puts("顺序队列不存在！\n");
		else if (st == EXPAND_FAILD) puts("顺序队列已满！\n");
		else puts("未知错误！\n");
	}
	Node *_pop()
	{
		if (this->len == 0) return nullptr;
		Node *res = this->start;
		this->start = mod(this->start+1);
		this->len --;
		return res;
	}
	Status _show()
	{
		if (this->head == nullptr) return NOT_FOUND;
		for (Node *p=this->start; p!=mod(this->start+this->len); p=mod(p+1))
			printf("(%s, %d)\n", p->name, p->val);
		return SUCCEED;
	}
	void judgeShow(Status st)
	{
		if (st == SUCCEED) ;
		else if (st == NOT_FOUND) puts("顺序队列不存在！\n");
		else puts("未知错误！\n");
	}
	Status _clear()
	{
		if (this->head == nullptr) return NOT_FOUND;
		this->start = this->head;
		this->len = 0;
		return SUCCEED;
	}
	void judgeClear(Status st)
	{
		if (st == SUCCEED) puts("顺序队列清空成功！");
		else if (st == NOT_FOUND) puts("顺序队列不存在！\n");
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
		if (st == SUCCEED) puts("顺序队列删除成功！");
		else if (st == NOT_FOUND) puts("顺序队列不存在！\n");
		else puts("未知错误！\n");
	}
};

int main()
{
	Queue *queue = new Queue(10);
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
		Node *tmp = queue->pop();
		printf("(%s, %d)\n", tmp->name, tmp->val);
	}
	return 0;
}

#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

vector <char> artical;
struct Node
{
	double freq;
	string code;
    Node *left, *right;
};
unordered_map <char, Node *> c;
struct Cmp
{
    bool operator ()(Node *&i, Node *&j)
    const { return i->freq > j->freq; }
};
priority_queue <Node *, vector<Node *>, Cmp> q;

Node *buildTree()
{
    while (q.size() > 1)
    {
        Node *l = q.top(); q.pop();
        Node *r = q.top(); q.pop();
        q.push(new (Node) {l->freq+r->freq, "", l, r});
    }
    if (q.size()) return q.top();
    return nullptr;
}

void encode(Node *root)
{
    if (root == nullptr) return ;
    if (root->left)
    {
        root->left->code = root->code+'0';
        encode(root->left);
    }
    if (root->right)
    {
        root->right->code = root->code+'1';
        encode(root->right);
    }
}

void readFile()
{
	freopen("README.md", "r", stdin);
	int t, n;
	for (t=0, n=0; (t=getchar())!=EOF; n++)
	{
		if (c.find(t) != c.end()) c[t]->freq ++;
		else c[t] = new (Node) {1, ""};
		artical.push_back(t);
	}
	for (auto i: c)
	{
		i.second->freq /= n/100.;
		q.push(i.second);
	}
}

void writeFile()
{
	freopen("huffman.txt", "w", stdout);
	putchar(0);
	for (auto i: c)
		printf("%c:%s,", i.first, i.second->code.c_str());
	putchar(0);
	for (auto i: artical)
		printf("%s", c[i]->code.c_str());
}

int main()
{
	readFile();
	encode(buildTree());
	writeFile();
	return 0;
}

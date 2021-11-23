#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

struct Node { int val; Node *left, *right; };
Node *buildTree(const vector <int> &tree)
{
	static int p = 0;
	if (p>=tree.size() || !tree[p]) { p ++; return nullptr; }
	return new (Node){ tree[p++], buildTree(tree), buildTree(tree) };
}

Node *buildTreeEx(const vector <int> &tree)
{
	int p = 0;
	stack <Node *> st;
	Node *root = nullptr;
	if (tree[p]) st.push(root=new (Node){tree[p++]});
	while (! st.empty())
	{
		Node *node = st.top();
		if (p>=tree.size() || !tree[p]) p ++;
		else if (! node->left)
		{
			st.push(node->left=new (Node){tree[p++]});
			continue;
		}
		if (p>=tree.size() || !tree[p]) p ++;
		else if (! node->right)
		{
			st.push(node->right=new (Node){tree[p++]});
			continue;
		}
		st.pop();
	}
	return root;
}

void preorderTravel(Node *root)
{
	if (! root) return;
	printf("%d\n", root->val);
	preorderTravel(root->left);
	preorderTravel(root->right);
}
void preorderTravelEx(Node *root)
{
	if (! root) return;
	stack <Node *> st({root});
	unordered_set <Node *> vis;
	while (! st.empty())
	{
		Node *node = st.top();
		if (vis.find(node)==vis.end())
		{
			printf("%d\n", node->val);
			vis.insert(node);
		}
		if (node->left && vis.find(node->left)==vis.end())
		{
			st.push(node->left);
			continue;
		}
		if (node->right && vis.find(node->right)==vis.end())
		{
			st.push(node->right);
			continue;
		}
		st.pop();
	}
}

void inorderTravel(Node *root)
{
	if (! root) return;
	inorderTravel(root->left);
	printf("%d\n", root->val);
	inorderTravel(root->right);
}
void inorderTravelEx(Node *root)
{
	if (! root) return;
	stack <Node *> st({root});
	unordered_set <Node *> vis;
	while (! st.empty())
	{
		Node *node = st.top();
		if (node->left && vis.find(node->left)==vis.end())
		{
			st.push(node->left);
			continue;
		}
		if (vis.find(node)==vis.end())
		{
			printf("%d\n", node->val);
			vis.insert(node);
		}
		if (node->right && vis.find(node->right)==vis.end())
		{
			st.push(node->right);
			continue;
		}
		st.pop();
	}
}

void postorderTravel(Node *root)
{
	if (! root) return;
	postorderTravel(root->left);
	postorderTravel(root->right);
	printf("%d\n", root->val);
}
void postorderTravelEx(Node *root)
{
	if (! root) return;
	stack <Node *> st({root});
	unordered_set <Node *> vis;
	while (! st.empty())
	{
		Node *node = st.top();
		if (node->left && vis.find(node->left)==vis.end())
		{
			st.push(node->left);
			continue;
		}
		if (node->right && vis.find(node->right)==vis.end())
		{
			st.push(node->right);
			continue;
		}
		if (vis.find(node)==vis.end())
		{
			printf("%d\n", node->val);
			vis.insert(node);
		}
		st.pop();
	}
}

int main()
{
	vector <int> tree({1, 2, 4, 0, 0, 5, 0, 0, 3, 0, 0});
	Node *root = buildTreeEx(tree);

	puts("先序遍历序列：\n---");
	preorderTravelEx(root);
	puts("---");
	preorderTravel(root);
	puts("---\n中序遍历序列：\n---");
	inorderTravelEx(root);
	puts("---");
	inorderTravel(root);
	puts("---\n后序遍历序列：\n---");
	postorderTravelEx(root);
	puts("---");
	postorderTravel(root);
	puts("---");
	return 0;
}

/*
				1
		2				3
	4		5		  0   0
  0   0	  0   0
*/
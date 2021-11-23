#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map <int, int> m;
struct Node { int val; Node *left, *right; };

Node *buildPreIn(int t, int l, int r, const vector <int> &preorder)
{
	if (l > r) return nullptr;
	int i = m[preorder[t]];
	Node *root = new (Node){ preorder[t] };
	root->left = buildPreIn(t+1, l, i-1, preorder);
	root->right = buildPreIn(t+1+i-l, i+1, r, preorder);
	return root;
}


Node *buildPostIn(int t, int l, int r, const vector <int> &postorder)
{
	if (l > r) return nullptr;
	int i = m[postorder[t]];
	Node *root = new (Node){ postorder[t] };
	root->left = buildPreIn(t-1-i+l, l, i-1, postorder);
	root->right = buildPreIn(t-1, i+1, r, postorder);
	return root;
}


void preorderTravel(Node *root)
{
	if (! root) return;
	printf("%c\n", root->val);
	preorderTravel(root->left);
	preorderTravel(root->right);
}

void inorderTravel(Node *root)
{
	if (! root) return;
	inorderTravel(root->left);
	printf("%c\n", root->val);
	inorderTravel(root->right);
}

void postorderTravel(Node *root)
{
	if (! root) return;
	postorderTravel(root->left);
	postorderTravel(root->right);
	printf("%c\n", root->val);
}

int main()
{
	vector <int> postorder({'E', 'B', 'A', 'D', 'C', 'F', 'H', 'G', 'I', 'K', 'J'});
	vector <int> inorder({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'});
	for (int i=0; i<inorder.size(); i++) m[inorder[i]] = i;
	preorderTravel(buildPostIn(postorder.size()-1, 0, inorder.size()-1, postorder));
	return 0;
}

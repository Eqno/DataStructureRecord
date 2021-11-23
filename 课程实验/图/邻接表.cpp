#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1e6+10;  // 点的最大个数。
const int INF = 0x3f3f3f3f;  // 无穷。

struct Edge  // 边的存储结构。
{
    int from, to, val;  // from到to边权为val。
    Edge *next;  // from连接的下一条边。 
} *edge[MAXN];  // 点索引到边表。
bool vis[MAXN];  // 是否访问过。

int bfs(int s)  // 宽度优先搜索。（求dfs经过的边权和）
{
    int sumLen = 0;  // 经过的边权和。
    queue <int> q;  // 用于搜索的队列。
    q.push(s);  // 将起点加入队列。
    vis[s] = true;  // 将起点标记为已访问。
    while (q.size())
    {
        int p = q.front();  // 取出队首。
        q.pop();  // 弹出队首。
        cout << p << " ";  // 输出经过点的编号。
        for (Edge *e=edge[p]; e; e=e->next)  // 遍历p连接的所有的边。
            if (e && !vis[e->to])  // 如果边表不为空，指向节点没有访问过。
            {
                q.push(e->to);  // 将新节点加入队列。
                vis[e->to] = true;  // 标记为已访问。
                sumLen += e->val;  // 经过的边权相加。
            }
    }
    return sumLen;  // 返回边权和。
}

int dfs(int s)  // 深度优先搜索。（求dfs经过的边权和）
{
    vis[s] = true;  // 标记为已访问。
    cout << s << " ";  // 输出经过点的编号。
    int sumLen = 0;  // 经过的边权和。
    for (Edge *e=edge[s]; e; e=e->next)  // 遍历s连接的所有的边。
        if (e && !vis[e->to])  // 如果边表不为空，指向节点没有访问过。
            sumLen += e->val+dfs(e->to);  // 前往下一个点。
    return sumLen;  // 返回边权和。
}

int dfsEx(int s)  // 深度优先搜索（模拟栈）。（求dfs经过的边权和）
{
    int sumLen = 0;  // 经过的边权和。
    stack <int> st;  // 用于搜索的栈。
    st.push(s);  // 将起点压入栈。
    vis[s] = true;  // 将起点标记为已访问。
    cout << s << " ";  // 输出起点的编号。
    while (st.size())
    {
        int p = st.top();  // 取出栈顶。
        bool flag = false;  // 有没有找到可行边。
        for (Edge *e=edge[p]; e; e=e->next)  // 遍历p连接的所有的边。
            if (e && !vis[e->to])  // 如果边表不为空，指向节点没有访问过。
            {
                st.push(e->to);  // 将新节点压入栈。
                vis[e->to] = true;  // 标记为已访问。
                cout << e->to << " ";  // 输出经过点的编号。
                sumLen += e->val;  // 经过的边权相加。
                flag = true;  // 找到了可行边。
                break;  // 找到可以前往的点就前往。
            }
        if (! flag) st.pop();  // 弹出栈顶。
    }
    return sumLen;  // 返回边权和。
}

void addEdge(int u, int v, int z)  // 加边。
{ edge[u] = new (Edge){u, v, z, edge[u]}; }  // 边表增加元素。

int main()
{
    int n, m;  // n个点m条边，点1~n编号。
    cin >> n >> m;  // 输入n、m。
    for (int i=1; i<=m; i++)
    {
        int u, v, z;  // u指向v边权为z。
        cin >> u >> v >> z;  // 输入u、v、z。
        addEdge(u, v, z);  // 有向图加边。
        // addEdge(v, u, z);  // 无向图加边。
    }
    int s;  // 搜索起点。
    cin >> s;  // 输入s。
    // int sumLen = bfs(s);  // 宽度优先搜索。
    // int sumLen = dfs(s);  // 深度优先搜索。
    int sumLen = dfsEx(s);  // 深度优先搜索（模拟栈）。
    cout << endl << sumLen;  // 输出经过的边权和。
    return 0;
}

/*
5 5
1 5 1
5 2 2
5 3 3
3 4 4
2 4 5
1
*/
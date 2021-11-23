#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1e3+10;  // 邻接矩阵的大小。
const int INF = 0x3f3f3f3f;  // 无穷。

int n, m;  // n个点m条边，点1~n编号。
bool vis[MAXN];  // 是否已经访问过。
int mat[MAXN][MAXN];  // 邻接矩阵。

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
        for (int i=1; i<=n; i++)  // 遍历所有的点。
            if (!vis[i] && mat[p][i]!=INF)  // 如果没有访问过且可以到达。
            {
                q.push(i);  // 将新节点加入队列。
                vis[i] = true;  // 标记为已访问。
                sumLen += mat[p][i];  // 经过的边权相加。
            }
    }
    return sumLen;  // 返回边权和。
}

int dfs(int s)  // 深度优先搜索。（求dfs经过的边权和）
{
    vis[s] = true;  // 标记为已访问。
    cout << s << " ";  // 输出经过点的编号。
    int sumLen = 0;  // 经过的边权和。
    for (int i=1; i<=n; i++)  // 遍历所有的点。
        if (!vis[i] && mat[s][i]!=INF)  // 如果没有访问过且可以到达。
            sumLen += mat[s][i]+dfs(i);  // 前往下一个点。
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
        for (int i=1; i<=n; i++)  // 遍历p连接的所有的边。
            if (!vis[i] && mat[p][i]!=INF)  // 如果没有访问过且可以到达。
            {
                st.push(i);  // 将新节点压入栈。
                vis[i] = true;  // 标记为已访问。
                cout << i << " ";  // 输出经过点的编号。
                sumLen += mat[p][i];  // 经过的边权相加。
                flag = true;  // 找到了可行边。
                break;  // 找到可以前往的点就前往。
            }
        if (! flag) st.pop();  // 弹出栈顶。
    }
    return sumLen;  // 返回边权和。
}

void init()  // 初始化矩阵。
{
    memset(mat, INF, sizeof mat);  // 矩阵初始化为INF。
    for (int i=1; i<=n; i++) mat[i][i] = 0;  // 自身到自身为0。
}

int main()
{
    cin >> n >> m;  // 输入n、m。
    init();  // 初始化矩阵。
    for (int i=1; i<=m; i++)
    {
        int u, v, z;  // u指向v边权为z。
        cin >> u >> v >> z;  // 输入u、v、z。
        mat[u][v] = z;  // 有向图加边。
        // mat[u][v] = mat[v][u] = z;  // 无向图加边。
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
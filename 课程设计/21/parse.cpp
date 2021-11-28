#include <string>
#include <vector>
#include <ctype.h>
#include <iostream>
#include <unordered_set>
using namespace std;

const int MAXN = 1e6+10;
string s;
int m[MAXN];
unordered_set <int> t;
unordered_set <string> r;
string parse(string e)
{
    int a = e.find('(');
    if (a != e.npos)
    {
        int b = e.find(')');
        string x = e.substr(0, a);
        string y = parse(e.substr(a+1, b-a-1));
        string z = e.substr(b+1, e.size()-b-1);
        return parse(x + y + z);
    }
    a = e.find('|');
    if (a != e.npos)
    {
        string x = parse(e.substr(0, a));
        string y = parse(e.substr(a+1, e.size()-a-1));
        return x=="1"||y=="1" ? "1" : "0";
    }
    a = e.find('&');
    if (a != e.npos)
    {
        string x = parse(e.substr(0, a));
        string y = parse(e.substr(a+1, e.size()-a-1));
        return x=="1"&&y=="1" ? "1" : "0";
    }
    if (e[0] == '~')
    {
        string x = parse(e.substr(1, e.size()-1));
        return x=="1" ? "0" : "1";
    }
    if (e.size() == 1)
    {
        if (e == "1") return "1";
        if (e == "0") return "0";
        return m[e[0]] ? "1" : "0";
    }
    return "0";
}
void dfs(vector <int> v)
{
    if (v.size() >= t.size())
    {
        int index = 0;
        for (auto i: t)
            m[i] = v[index++];
        string res = parse(s);
        // cout << res << endl;
        r.emplace(res);
        return;
    }
    v.push_back(0);
    dfs(v);
    v.back() = 1;
    dfs(v);
}
int main()
{
    char c;
    while ((c=getchar())!=EOF && c!='\n')
    {
        if (c == ' ') continue;
        if (isalpha(c)) t.emplace(c);
        s.push_back(c);
    }
    dfs({});
    if (r.size() < 1) puts("Error!");
    if (r.size() == 1)
    {
        if (*r.begin() == "1") puts("True forever!");
        if (*r.begin() == "0") puts("False forever!");
    }
    if (r.size() > 1)
    {
        puts("Satisfactible!\nPlz input value: (0 or 1)");
        vector <int> v;
        for (auto i: t)
        {
            printf("%c: ", i);
            cin >> m[i];
            getchar();
        }
        cout << parse(s) << endl;
    }
    return 0;
}
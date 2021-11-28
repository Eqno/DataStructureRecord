#include <cmath>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_set <string> k({
    "include", "main",
    
    "int", "char", "long", "double", "string",

    "set", "map", "stack", "queue", "multiset", "multimap",
    "unordered_set", "unordered_map", "priority_queue",
    
    "do", "for", "while",
    
    "if", "else", "switch", "break", "return", "continue",

    "gets", "puts", "cin", "cout", "scanf", "printf", "putchar", "getline",

    "new", "enum", "auto", "free", "delete", "malloc", "struct",

    "max", "min", "abs", "sort",

    "open", "close", "fopen", "freopen"
});
typedef unsigned long long ull;
unordered_map <string, int> fa, fb;
vector <int> va, vb;  // 特征向量。

bool read(string &s)
{
    char c = getchar();
    while (! isalpha(c))
    {
        if (c == EOF) return false;
        c = getchar();
    }
    while (isalpha(c))
    {
        s.push_back(c);
        c = getchar();
    }
    if (c == EOF) return false;
    return true;
}

int main()
{
    freopen("A.c", "r", stdin);
    while (1)
    {
        string s;
        if (! read(s)) break;
        if (k.find(s) != k.end()) fa[s] ++;
    }
    freopen("B.c", "r", stdin);
    while (1)
    {
        string s;
        if (! read(s)) break;
        if (k.find(s) != k.end()) fb[s] ++;
    }
    // if (fa.size() >= fb.size())
    //     for (auto i: fa)
    //         printf("%s: %d, %d\n", i.first.c_str(), i.second, fb[i.first]);
    // else
    //     for (auto i: fb)
    //         printf("%s: %d, %d\n", i.first.c_str(), i.second, fa[i.first]);
    if (fa.size() >= fb.size())
        for (auto i: fa)
        {
            va.push_back(i.second);
            vb.push_back(fb[i.first]);
        }
    else
        for (auto i: fb)
        {
            va.push_back(i.second);
            vb.push_back(fa[i.first]);
        }
    double n = 0, da = 0, db = 0;
    for (ull i=0; i<va.size(); i++) n += va[i]*vb[i];
    for (ull i=0; i<va.size(); i++) da += va[i]*va[i];
    for (ull i=0; i<vb.size(); i++) db += vb[i]*vb[i];
    double s = n / sqrt(da) / sqrt(db);
    cout << s << endl;
    return 0;
}
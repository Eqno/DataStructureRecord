#include <cmath>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <iostream>
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
template <class Key, class Val>  // Key -> getHash、==
class HashMap
{
    private:
    int siz = 0;
    static const int MAXN = 41;
    vector <pair <Key, Val>> hash[MAXN];
    public:
    Val &get(const Key &key)
    {
        auto &v = hash[key.getHash()];
        for (auto &i: v)
            if (key == i.first)
                return i.second;
        siz ++, v.push_back({key, NULL});
        return v.back().second;
    }
    int size() const { return siz; }
    const vector <pair <Key, Val>> &items()
    {
        auto *res = new vector <pair <Key, Val>> ();
        for (int i=0; i<MAXN; i++)
            for (auto j: hash[i])
                res->push_back(j);
        return *res;
    }
    Val & operator [](const Key &key) { return get(key); }
};
class String: public string
{
    public:
    String(): string() {};
    String(string s): string(s) {};
    int getHash() const { return (front()*100+back()) % 41; }
};
HashMap <String, int> fa, fb;  // 哈希频度。
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
    //     for (auto i: fa.items())
    //         printf("%s: %d, %d\n", i.first.c_str(), i.second, fb[i.first]);
    // else
    //     for (auto i: fb.items())
    //         printf("%s: %d, %d\n", i.first.c_str(), i.second, fa[i.first]);
    if (fa.size() >= fb.size())
        for (auto i: fa.items())
        {
            va.push_back(i.second);
            vb.push_back(fb[i.first]);
        }
    else
        for (auto i: fb.items())
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
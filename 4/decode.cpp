#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map <string, char> m;

void buildMap()
{
	char c = getchar();
	if (c != 0) return ;
	while ((c=getchar()) != 0)
	{
		char value = c;
		getchar();
		string key;
		while ((c=getchar()) != ',')
			key.push_back(c);
		m[key] = value;
	}
}

void readFile()
{
	freopen("huffman.txt", "r", stdin);
	buildMap();
}

void writeFile()
{
	freopen("README.md.backup", "w", stdout);
	string s;
	char c;
	while ((c=getchar()) != EOF)
	{
		s.push_back(c);
		if (m.find(s) != m.end())
		{
			putchar(m[s]);
			s.clear();
		}
	}
}

int main()
{
	readFile();
	writeFile();
	return 0;
}

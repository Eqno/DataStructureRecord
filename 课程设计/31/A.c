#include <stdio.h>
double average(int n, int s[])
{
    double res = 0;
    for (int i=0; i<n; i++)
        res += s[i];
    return res / n;
}
int main()
{
    int n, s[105];
    scanf("%d", &n);
    for (int i=0; i<n; i++)
        scanf("%d", s+i);
    printf("%.4f\n", average(n, s));
    return 0;
}
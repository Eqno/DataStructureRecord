#include <stdio.h>
int main()
{
    int n, sum = 0;
    scanf("%d", &n);
    for (int i=0; i<n; i++)
    {
        int num;
        scanf("%d", &num);
        sum += num;
    }
    printf("%.4f\n", (double)sum/n);
    return 0;
}

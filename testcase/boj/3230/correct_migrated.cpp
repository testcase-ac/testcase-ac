#include <stdio.h>

int f[110], s[110];
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int main()
{
    int n, m, v;

    scanf("%d %d", &n, &m);

    for (int i=1; i<=n; i++)
    {
        scanf("%d", &v);

        for (int j=n; j>=v+1; j--)
            f[j] = f[j-1];
        
        f[v] = i;
    }

    for (int i=m; i>=1; i--)
    {
        scanf("%d", &v);

        for (int j=3; j>=v+1; j--)
            s[j] = s[j-1];
        s[v] = f[i];
    }

    for (int i=1; i<=3; i++)
        printf("%d\n", s[i]);
}

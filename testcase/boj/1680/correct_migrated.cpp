#include <stdio.h>
int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++)
    {
        int W, N;
        int Xsum = 0, Wbound = 0;
        scanf("%d %d", &W, &N);
        for(int j = 0; j < N; j++)
        {
            int Xi, Wi;
            scanf("%d %d", &Xi, &Wi);
            if(Wi+Wbound > W)
            {
                Wbound = 0;
                Xsum += 2*Xi;
            }
            Wbound += Wi;
            if(Wbound == W)
            {
                Wbound = 0;
                Xsum += 2*Xi;
            }
            else if(j == N-1)
            {
                Xsum += 2*Xi;
            }
        }
        printf("%d\n", Xsum);
    }
}

#include <cstdio>

int N, M, K;

int main(){

    scanf("%d%d%d", &N, &M, &K);

    int n;

    for (n = 1; n <= N; n++){        //이 안에 답이 나옴

        int nM = M % (N - n + 1) == 0 ? N - n + 1 : M % (N - n + 1);

        if (K == nM || n == N)

            break;

        else

            K = K > nM ? K - nM : N - n + K - nM + 1;

    }

    printf("%d\n", n);

    return 0;

}

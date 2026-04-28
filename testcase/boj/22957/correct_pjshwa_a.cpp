#include <stdio.h>

long long comb[32][32], b3[32];
int poss[32][256][3], possc[32], cnt[3];

int main(void) {
    for (int i = 0; i <= 30; i++) {
        comb[i][0] = 1;
        b3[i] = i ? b3[i - 1] * 3 : 1;
        for (int j = 1; j <= i; j++) {
            if (i == 0) comb[i][j] = 1;
            else comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
    for (int i = 0; i <= 30; i += 2) {
        for (int j = 0; i + j <= 30; j += 2) {
            for (int k = 0; i + j + k <= 30; k += 2) {
                poss[i + j + k][possc[i + j + k]][0] = i;
                poss[i + j + k][possc[i + j + k]][1] = j;
                poss[i + j + k][possc[i + j + k]][2] = k;
                possc[i + j + k]++;
            }
        }
    }
    int n, d;
    long long k, t, t2;
    scanf("%d %lld", &n, &k);
    for (d = n; d > 0; d--) {
        t = b3[d];
        for (int j = 0; j < possc[d]; j++) {
            t -= comb[d][poss[d][j][0]] * comb[d - poss[d][j][0]][poss[d][j][1]];
        }
        if (k > t) k -= t;
        else break;
    }
    for (int i = 0; i < d; i++) {
        t = b3[d - i - 1];
        for (int j = 0; j < possc[d]; j++) {
            if (poss[d][j][0] < cnt[0] + 1 || poss[d][j][1] < cnt[1] || poss[d][j][2] < cnt[2]) continue;
            t -= comb[d - i - 1][poss[d][j][0] - cnt[0] - 1] * comb[d - i - poss[d][j][0] + cnt[0]][poss[d][j][1] - cnt[1]];
        }
        t2 = t;
        if (t >= k) {
            printf("7");
            cnt[0]++;
            continue;
        }
        t += b3[d - i - 1];
        for (int j = 0; j < possc[d]; j++) {
            if (poss[d][j][0] < cnt[0] || poss[d][j][1] < cnt[1] + 1 || poss[d][j][2] < cnt[2]) continue;
            t -= comb[d - i - 1][poss[d][j][0] - cnt[0]] * comb[d - i - poss[d][j][0] + cnt[0] - 1][poss[d][j][1] - cnt[1] - 1];
        }
        if (t >= k) {
            printf("5");
            cnt[1]++;
            k -= t2;
        }
        else {
            printf("3");
            cnt[2]++;
            k -= t;
        }
    }
    return 0;
}

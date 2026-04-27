#include <cstdio>
#include <algorithm>

using std::max;

int n, m;
int L[4010][4010], R[4010][4010], C[4010][4010], M[4010][4010];
int DR[4010][4010], DL[4010][4010];
int AR[10100], AL[10100];
int BR[10100],  BL[10100];
char p[4010][4010];

void Solve() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", p[i] + 1);
    }
    
    int EM = 0, OM = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i][j] == '1') {
                L[i][j] = L[i - 1][j - 1] + 1;
                R[i][j] = R[i - 1][j + 1] + 1;
                C[i][j] = L[i][j] + R[i][j] - 1;
                if ((i + j) % 2 == 0) {
                    EM = max(EM, C[i][j]);
                } else {
                    OM = max(OM, C[i][j]);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            M[i][j] = max({ M[i - 1][j], M[i - 1][j - 1], M[i - 1][j + 1], C[i][j] });
        }
    }

    int res = EM + OM;
    for (int i = n; i >= 1; --i) {
        for (int j = 1; j <= m; ++j) {
            if (p[i][j] == '1') {
                DL[i][j] = max(L[i][j], DL[i + 1][j - 1] + 1);
                DR[i][j] = max(R[i][j], DR[i + 1][j + 1] + 1);

                AL[j - i + n] = max(AL[j - i + n], DL[i][j]);
                AR[i + j] = max(AR[i + j], DR[i][j]);

                BL[j - i + n] = max(BL[j - i + n], C[i][j]);
                BR[i + j] = max(BR[i + j], C[i][j]);
            }
        }
    }

    for (int i = 2; i <= n + m; ++i) {
        AL[i] = max(AL[i], AL[i - 1]);
        BR[i] = max(BR[i], BR[i - 1]);
    }

    for (int i = n + m - 1; i >= 1; --i) {
        AR[i] = max(AR[i], AR[i + 1]);
        BL[i] = max(BL[i], BL[i + 1]);
    }

    for (int i = 1; i <= n + m; ++i) {
        res = max(res, AL[i] + BL[i + 1]);
        res = max(res, AR[i] + BR[i - 1]);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            res = max(res, C[i][j] + M[i - 1][j]);
        }
    }

    printf("%d\n", res);
}

int main() {
    Solve();
}

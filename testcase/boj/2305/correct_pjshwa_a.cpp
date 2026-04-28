#include <bits/stdc++.h>

using namespace std;

int N, K;

int F[41];
int E[41][41];
int DP[41][41];

int func_E(int n, int k) {
    if (k > n / 2) {
        k = n - k + 1;
    }

    int &ret = E[n][k];
    if (ret != -1) return ret;
    int l = k - 1;
    int r = n - l - 1;

    return ret = F[l] * F[r] + F[r] * func_E(l, 1) + F[l] * func_E(r, 1);
}

int func_DP(int n, int k) {
    if (k > n / 2) {
        k = n - k + 1;
    }

    int &ret = DP[n][k];
    if (ret != -1) return ret;
    int l = k - 1;
    int r = n - l - 1;
    return ret = -F[l] * F[r] + func_DP(l + 1, 1) * F[r] + func_DP(r + 1, 1) * F[l];
}

int main() {
    memset(F, -1, sizeof F);
    memset(E, -1, sizeof E);
    memset(DP, -1, sizeof DP);

    cin >> N >> K;
    F[1] = 1;
    F[2] = 2;
    for (int n = 3; n <= 40; n++)
        F[n] = F[n - 2] + F[n - 1];
    E[1][1] = 1;
    E[2][1] = 2;
    for (int n = 3; n <= 40; n++) {
        E[n][1] = F[n - 1] + E[n - 1][1];
    }
    DP[1][1] = 1;
    DP[2][1] = 2;
    DP[2][2] = 2;

    for (int n = 3; n <= 40; n++) {
        DP[n][1] = F[n - 1];
        for (int j = 1; j <= n - 1; j++) {
            DP[n][1] += func_E(n - 1, j);
        }
    }

    cout << func_DP(N, K);


    return 0;
}

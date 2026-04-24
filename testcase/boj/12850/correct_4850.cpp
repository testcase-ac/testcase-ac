#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<vector<int>> init = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 1},
    {0, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 0, 0, 1, 1, 0, 1},
    {0, 0, 0, 0, 1, 0, 1, 0},
};
int dp[8];
const int MOD = 1e9 + 7;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int D;
    cin >> D;
    vector<vector<int>> cur = vector<vector<int>>(8, vector<int>(8)), mul = init;
    for(int i = 0; i < 8; i++) {
        cur[i][i] = 1;
    }
    while(D) {
        if(D & 1) {
            vector<vector<int>> tmp(8, vector<int>(8));
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    for(int k = 0; k < 8; k++) {
                        tmp[i][j] += cur[i][k] * mul[k][j];
                        tmp[i][j] %= MOD;
                    }
                }
            }
            cur = tmp;
        }
        vector<vector<int>> tmp(8, vector<int>(8));
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                for(int k = 0; k < 8; k++) {
                    tmp[i][j] += mul[i][k] * mul[k][j];
                    tmp[i][j] %= MOD;
                }
            }
        }
        mul = tmp;
        D >>= 1;
    }
    int ans = 0;
    cout << cur[7][7] << '\n';
}

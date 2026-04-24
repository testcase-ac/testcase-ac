#include <iostream>

using namespace std;
#define int long long
int arr[101][101], dp[101][101];
bool block[101][101][2]; // 0:horizontal 1:vertical
int32_t main() {
    int R, C, K;
    cin >> R >> C >> K;
    for(int i=0; i<K; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        if(r1 == r2) {
            block[r1][min(c1, c2)][0] = true;
        } else if(c1 == c2) {
            block[min(r1, r2)][c1][1] = true;
        }
    }
    dp[0][0] = 1;
    for(int i=0; i<=R; i++) {
        for(int j=0; j<=C; j++) {
            if(dp[i][j] > 0) {
                if(j+1 <= C && !block[i][j][0]) dp[i][j+1] += dp[i][j];
                if(i+1 <= R && !block[i][j][1]) dp[i+1][j] += dp[i][j];
            }
        }
    }
    cout << dp[R][C];

}

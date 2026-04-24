#include <cstring>
#include <string>
#include <climits>
#include <cstdio>
using namespace std;
const int MX = 4002;
char A[MX], B[MX];
int N, M;
int nxtA[MX][2], nxtB[MX][2], _dp[MX][MX];
int dp(int i, int j) {
    if(i >= N+1 && j >= M+1 ) return 0;
    auto &val = _dp[i][j];
    if(val) return val;
    val = INT_MAX;
    // try choose 0
    int ni = nxtA[i][0], nj = nxtB[j][0];
    val = min(val, dp(ni, nj) + 1);

    // try choose 1
    ni = nxtA[i][1], nj = nxtB[j][1];
    val = min(val, dp(ni, nj) + 1);

    return val;
}
int32_t main() {
    scanf("%s %s", A+1, B+1);
    N = strlen(A+1), M = strlen(B+1);
    nxtA[N+1][0] = nxtA[N+1][1] = N+1;
    for(int i=N; i>=0; i--) {
        nxtA[i][0] = nxtA[i+1][0];
        if(A[i+1] == '0') nxtA[i][0] = i+1;
        nxtA[i][1] = nxtA[i+1][1];
        if(A[i+1] == '1') nxtA[i][1] = i+1;
    }

    nxtB[M+1][0] = nxtB[M+1][1] = M+1;
    for(int i=M; i>=0; i--) {
        nxtB[i][0] = nxtB[i+1][0];
        if(B[i+1] == '0') nxtB[i][0] = i+1;
        nxtB[i][1] = nxtB[i+1][1];
        if(B[i+1] == '1') nxtB[i][1] = i+1;
    }
    string ans = "";
    int i = 0, j = 0;
    while(i <= N || j <= M) {
        // try choose 0
        int best = dp(i, j);
        int ni = nxtA[i][0], nj = nxtB[j][0];
        int tmp = dp(ni, nj) + 1;
        // printf("at ans = %s, best = %d, tmp = %d\n", ans.c_str(), best, tmp);
        if(tmp > best) {
            ans += '1';
            i = nxtA[i][1];
            j = nxtB[j][1];
        } else {
            ans += '0';
            i = nxtA[i][0];
            j = nxtB[j][0];
        }
    }
    printf("%s", ans.c_str());
}

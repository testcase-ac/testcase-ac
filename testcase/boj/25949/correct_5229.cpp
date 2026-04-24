#include <bits/stdc++.h>
using namespace std;

int dp[101][101][101][29];

void update(int& a, int b) {
    a = max(a, b);
}

int32_t main() {
    cin.tie(0);
    cin.sync_with_stdio(0);

    int a,b,c;
    cin >> a >> b >> c; 
    for(int i=0; i<=a; i++) {
        for(int j=0; j<=b; j++) {
            for(int k=0; k<=c; k++) {
                for(int l=1; l<=28; l++) {
                    dp[i][j][k][l] = -1e6;
                    if(i==0 && j==0 && k==0) {
                        dp[i][j][k][l] = 0;
                    } 
                    else if(l!=28) {
                        if(i!=0)
                            update(dp[i][j][k][l], min(l, i) - dp[max(i-l, 0)][j][k][l+1]);
                        if(j!=0)
                            update(dp[i][j][k][l], min(l, j) - dp[i][max(j-l, 0)][k][l+1]);
                        if(k!=0)
                            update(dp[i][j][k][l], min(l, k) - dp[i][j][max(k-l, 0)][l+1]);
                    }
                }

            }
        }
    }
    if(dp[a][b][c][1] > 0)
        cout << "F";
    else if(dp[a][b][c][1] < 0)
        cout << "S";
    else
        cout << "D";
}

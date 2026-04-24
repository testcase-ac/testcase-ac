#include <bits/stdc++.h>
using namespace std;
int n,p,q;
vector<string> X,p1,p2;
int dp[502][502][502];
void update(int& a, int b) {
    a = max(a, b);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>n>>p>>q;
    X.resize(n);
    p1.resize(p);
    p2.resize(q);
    int idx=1;
    for(auto &e:X){
        cin>>e;
    }
    for(auto &e:p1){
        cin>>e;
    }
    for(auto &e:p2){
        cin>>e;
    }
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=p; j++) {
            for(int k=0; k<=q; k++) {
                if(i>=1 && j>=1 && X[i-1]==p1[j-1]) {
                    update(dp[i][j][k], dp[i-1][j-1][k] + 1);
                }
                if(i>=1 && k>=1 && X[i-1]==p2[k-1]) {
                    update(dp[i][j][k], dp[i-1][j][k-1] + 1);
                }
                if(i>=1) {
                    update(dp[i][j][k], dp[i-1][j][k]);
                }
                if(j>=1)
                    update(dp[i][j][k], dp[i][j-1][k]);
                if(k>=1)
                    update(dp[i][j][k], dp[i][j][k-1]);
            }
        }
    }
    cout << dp[n][p][q];
}

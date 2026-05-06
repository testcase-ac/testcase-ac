//N^3 dp (어차피 N^3이 시간초과나는 테스트케이스는 testcase.ac에서 짤림)
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin>>n;
    int dp[501][501];
    pair<int,int> a[501],dpt[501][501];
    for(int i=1;i<=n;i++) {
        cin>>a[i].first>>a[i].second;
        dpt[i][i]=a[i];
    } for(int i=1;i<n;i++) {
        for(int j=1;i+j<=n;j++) {
            dp[j][i+j]=2100000000;
            for(int k=j;k<i+j;k++) {
                int s=dpt[j][k].first*dpt[j][k].second*dpt[k+1][i+j].second;
                dp[j][i+j]=min(dp[j][i+j],dp[j][k]+dp[k+1][i+j]+s);
            } dpt[j][i+j].first=a[j].first;
			dpt[j][i+j].second=a[i+j].second;
        }
    } cout<<dp[1][n];
}

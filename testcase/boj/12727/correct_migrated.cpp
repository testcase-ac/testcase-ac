#include <bits/stdc++.h>
using namespace std;
int main() {
    int k,n,a;
    int dp[31];
    dp[0]=2;
    dp[1]=6;
    for(int i=2;i<=30;i++) {
        dp[i]=(6*dp[i-1]-4*dp[i-2])%1000;
    } cin>>k;
    for(int i=0;i<k;i++) {
        cin>>n;
        a=dp[n];
        while(a<0) {
            a+=1000;
        } if(a-1<10) {
            cout << "Case #" << i+1 << ": 00" << a-1 << "\n";
        } else if(a-1<100) {
            cout << "Case #" << i+1 << ": 0" << a-1 << "\n";
        } else {
            cout << "Case #" << i+1 << ": " << a-1 << "\n";
        }
    }
}

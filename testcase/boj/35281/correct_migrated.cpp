#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,m;
    cin>>n>>m;
    bool swp=0;
    if(n>m) {swap(n,m);swp=1;}
    if((m-n)%2||n==2) {cout<<-1;return 0;}
    int a[n][m];
    memset(a,0,sizeof(a));
    cout<<max(n,m)<<'\n';
    if(abs(n-m)%4==0) {
        for(int i=0;i<n-2;i++) {
            a[i][i+1]=1;
            a[i+1][i+1]=2;
        } for(int i=0;i<m-n;i+=2) {
            a[n-2][n-1+i]=1;
            a[n-1][n-1+i]=2;
            a[n-3][n+i]=1;
            a[n-2][n+i]=2;
        } a[n-1][0]=1;
        a[n-1][1]=2;
        a[n-2][m-1]=1;
        a[n-1][m-1]=2;
    } else {
        for(int i=0;i<n-2;i++) {
            a[i][i]=1;
            a[i+1][i]=2;
        } for(int i=0;i<m-n;i+=2) {
            a[n-2][n-2+i]=1;
            a[n-1][n-2+i]=2;
            a[n-3][n-1+i]=1;
            a[n-2][n-1+i]=2;
        } a[n-3][m-1]=1;
        a[n-2][m-1]=2;
        a[n-1][m-2]=1;
        a[n-1][m-1]=2;
    } if(swp) {
        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                if(a[j][i]==1) cout<<'G';
                else if(a[j][i]==2) cout<<'g';
                else cout<<'.';
            } cout<<'\n';
        }
    } else {
        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                if(a[i][j]==1) cout<<'G';
                else if(a[i][j]==2) cout<<'g';
                else cout<<'.';
            } cout<<'\n';
        }
    }
}

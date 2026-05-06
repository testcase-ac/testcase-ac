#include <bits/stdc++.h>
using namespace std;
long len[90];
char f(long n,long k) {
    if(k==1) return '(';
    if(n>100) {
        if(k-(n-88)/2<1) return '(';
        return f(n-(n-88)/2*2,k-(n-88)/2);
    } if(n>88) return f(n-2,k-1);
    if(k==len[n]) return ')';
    if(k<=len[n-2]+1) return f(n-2,k-1);
    return f(n-1,k-1-len[n-2]);
}
int main() {
    len[1]=len[2]=2;
    for(int i=3;i<90;i++) len[i]=len[i-1]+len[i-2]+2;
    int t;
    long n,k;
    cin>>t;
    while(t--) {
        cin>>n>>k;
        if(n<86) if(k>len[n]) {cout<<"0\n";continue;}
        cout<<f(n,k)<<'\n';
    }
}

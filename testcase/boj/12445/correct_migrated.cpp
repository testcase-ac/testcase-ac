#include <bits/stdc++.h>
using namespace std;
int f(int x,int m) {return x<m?x:x%m+m;}
int pw(int a,int n,int m) {
    int r=1;
    while(n) {
        if(n%2) r=f(r*a,m);
        a=f(a*a,m);
        n/=2;
    } return r;
}
int phi(int n) {
    int a=n;
    for(int p=2;p*p<=n;p++) {
        if(n%p==0) a=a/p*(p-1);
        while(n%p==0) n=n/p;
    } return n==1?a:a/n*(n-1);
}
int main() {
    int t,a,b,c;
    cin>>t;
    for(int i=1;i<=t;i++) {
        cin>>a>>b>>c;
        cout<<"Case #"<<i<<": ";
        if(b==1) cout<<pw(a,a,c)%c<<'\n';
        else cout<<pw(pw(a,a,c),pw(a,a,phi(c)),c)%c<<'\n';
    }
}

#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
ull pw(__int128 x,__int128 y,__int128 m) {
    x%=m;
    __int128 r=1;
    while(y) {
        if(y%2) r=(r*x)%m;
        x=(x*x)%m;
        y/=2;
    } return (ull)r;
}
bool chk(ull n,ull a) {
    if(a%n==0) return 1;
    ull k=n-1;
    while(1) {
        ull t=pw(a,k,n);
        if(t==n-1) return 1;
        if(k%2) return (t==1||t==n-1);
        k/=2;
    }
}
bool isprime(ull n) {
    if(n==2||n==3) return 1;
    if(n%2==0) return 0;
    ull a[]={2,3,5,7,11,13,17,19,23};
    for(int i=0;i<9;i++) if(!chk(n,a[i])) return 0;
    return 1;
}
ull gcd(ull a,ull b) {return b?gcd(b,a%b):a;}
ull dv(__int128 n) {
    if(n%2==0) return 2;
    if(isprime(n)) return n;
    __int128 x=rand()%(n-2)+2,y=x,c=rand()%10+1,g=1;
    while(g==1) {
        x=(x*x%n+c)%n;
        y=(y*y%n+c)%n;
        y=(y*y%n+c)%n;
        g=gcd(abs(x-y),n);
        if(g==n) return dv(n);
    } return isprime(g)?g:dv(g);
}
int main() {
    ull a,x,n;
    cin>>a>>n;
    if(a==1) {cout<<-1;return 0;}
    x=a;
    vector<ull> p;
    while(x>1) {
        auto d=dv(x);
        while(x%d==0) x/=d;
        p.push_back(d);
    } sort(p.rbegin(),p.rend());
    for(auto k:p) {
        if((__int128)a*k<=n) {cout<<a*k;return 0;}
        while(a%k==0) a/=k;
        a*=k;
    } cout<<-1;
}

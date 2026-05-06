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
    if(a%n==0)return 1;
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
    ull a[]={2,3,5,7,11,13,17,19,23,29,31,37};
    for(int i=0;i<12;i++) if(!chk(n,a[i])) return 0;
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
    ull n,ans=1,k=2;
    cin>>n;
    if(n==1) {
        cout<<1;
        return 0;
    } vector<ull> v;
    while(n>1) {
        ull d=dv(n);
        v.push_back(d);
        n/=d;
    } sort(v.begin(),v.end());
    for(int i=1;i<v.size();i++) {
        if(v[i]==v[i-1]) k++;
        else {
            ans*=k;
            k=2;
        }
    } cout<<ans*k;
}

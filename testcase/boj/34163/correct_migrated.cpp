#include <bits/stdc++.h>
#define ll long long
using namespace std;
const long double PI=acosl(-1);
long double f(long long m,long long n) {
    if(n==1) return 0;
    if(m==1) return -logl(cosl(PI/n));
    long long g=gcd(m,n);
    if(g>1) return logl(cosl(PI*g/(m*n)))-logl(cosl(PI/n));
    if(m==3) {
        if(n%3==1) return logl(cosl(PI/(n*3))+cosl(PI/(n*3)-PI/3))-logl(cosl(PI/n)+cosl(PI/(n*3)-PI/3));
        return logl(cosl(PI/(n*3))+cosl(PI/(n*3)+PI/3))-logl(cosl(PI/n)+cosl(PI/(n*3)+PI/3));
    } if(n==3) return logl(2)-logl(3)+logl(cosl(PI/m)-2.0L*cosl(PI/m+PI*2*floor(m/3)/m+PI/3));
    if(m==4) {
        if(n==5||n==9) return logl(cosl(PI/(n*2))+sinl(PI/(n*2)))-logl(cosl(PI/n)+sinl(PI/(n*2)));
        if(n%4==1) return -logl(sinl(-PI/(n*2))+1)-logl(cosl(PI/(n*2))+sinl(PI/(n*2)))+logl(cosl(PI/(n*4)));
        return -logl(sinl(PI/(n*2))+1)-logl(cosl(PI/(n*2))-sinl(PI/(n*2)))+logl(cosl(PI/(n*4)));
    } return logl(2)*0.5L+logl(cosl(PI/(m*2)))+logl(cosl(PI/(m*4)));
}
int main() {
    long long n,k,a,b;
    long double r=0;
    cin>>n>>k>>a;
    while(--n) {
        cin>>b;
        r+=f(a,b);
        a=b;
    } cout<<fixed<<setprecision(15)<<r;
}

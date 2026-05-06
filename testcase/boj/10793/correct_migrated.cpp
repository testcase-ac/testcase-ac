#include <bits/stdc++.h>
#define ll long long
using namespace std;
using cd=complex<double>;
const double pi=acos(-1);
void fft(vector<cd> &a,bool inv) {
    int n=a.size();
    for(int i=1,j=0;i<n;i++) {
        int bit=n>>1;
        while(j>=bit) {
            j-=bit;
            bit>>=1;
        } j+=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int i=1;i<n;i<<=1) {
        double ang=(inv?-1:1)*pi/i;
        cd w={cos(ang),sin(ang)};
        for(int j=0;j<n;j+=i<<1) {
            cd th={1,0};
            for(int k=0;k<i;k++) {
                cd tmp=a[i+j+k]*th;
                a[i+j+k]=a[j+k]-tmp;
                a[j+k]+=tmp;
                th*=w;
            }
        }
    } if(inv) for(int i=0;i<n;i++) a[i]/=n;
}
vector<ll> mult(vector<ll> &a,vector<ll> &b) {
    vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1;
    while(n<a.size()+b.size()) n<<=1;
    fa.resize(n);
    fb.resize(n);
    fft(fa,0);
    fft(fb,0);
    for(int i=0;i<n;i++) fa[i]*=fb[i];
    fft(fa,1);
    vector<ll> r(n);
    for(int i=0;i<n;i++) r[i]=(ll)round(fa[i].real());
    return r;
}
int main() {
    vector<ll> a(1<<19,0),x;
    for(int i=1;i<(1<<19);i++) for(int j=i;j<(1<<19);j+=i) a[j]++;
    x=mult(a,a);
    x[1]=1;
    int t,l,r,m,id;
    cin>>t;
    while(t--) {
        cin>>l>>r;
        m=0;
        for(int i=l;i<=r;i++) {
            if(x[i]>m) {m=x[i];id=i;}
        } cout<<id<<' '<<m<<'\n';
    }
}

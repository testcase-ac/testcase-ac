#include <bits/stdc++.h>
using namespace std;
using cd=complex<double>;
const double pi=acos(-1);
void fft(vector<cd> &a,bool inv) {
    int n=a.size();
    for(int i=1,j=0;i<n;i++) {
        int bit=n>>1;
        for(;j>=bit;bit>>=1) j-=bit;
        j+=bit;
        if(i<j) swap(a[i],a[j]);
    } for(int l=2;l<=n;l<<=1) {
        double ang=(inv?-1:1)*pi/(l/2);
        cd wl(cos(ang),sin(ang));
        for(int i=0;i<n;i+=l) {
            cd w(1);
            for (int j=0;j<l/2;j++) {
                cd u=a[i+j],v=a[i+j+l/2]*w;
                a[i+j] = u+v;
                a[i+j+l/2]=u-v;
                w*=wl;
            }
        }
    } if(inv) for(cd &x:a) x/=n;
}
vector<int> multiply(vector<int> &a,vector<int> &b) {
    vector<cd> fa(a.begin(),a.end()),fb(b.begin(),b.end());
    int n=1<<21;
    fa.resize(n);
    fb.resize(n);
    fft(fa,0);
    fft(fb,0);
    for(int i=0;i<n;i++) fa[i]*=fb[i];
    fft(fa,1);
    vector<int> r(n);
    for(int i=0;i<n;i++) r[i]=(int)round(fa[i].real());
    return r;
}
vector<int> third(vector<int> &a) {
    vector<cd> fa(a.begin(), a.end());
    int n=1<<21;
    fa.resize(n);
    fft(fa,0);
    for(int i=0;i<n;i++) fa[i]*=fa[i]*fa[i];
    fft(fa,1);
    vector<int> r(n);
    for (int i=0;i<n;i++) r[i]=(int)round(fa[i].real());
    return r;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    vector<int> prime;
    char notp[1000001]={};
    for(int i=2;i*i<=1000000;i++) {
        if(!notp[i]) for(int j=i*i;j<=1000000;j+=i) notp[j]=1;
    } for(int i=3;i<=1000000;i+=2) {
        if(!notp[i]) prime.push_back(i);
    } vector<int> a(1<<21),b(1<<21),x,y;
    for(int p:prime) {
        a[(p-1)/2]=1;
        b[(p-1)]=1;
    } x=third(a);
    y=multiply(a, b);
    int q,n;
    cin>>q;
    while(q--) {
        cin>>n;
        int asdf=(!notp[n-4]),fasd=x[(n-3)/2]-3*y[(n-3)/2];
        if(n%3==0&&!notp[n/3]) cout<<asdf+(fasd+2)/6+y[(n-3)/2]<<'\n';
        else cout<<asdf+fasd/6+y[(n-3)/2]<<'\n';
    }
}

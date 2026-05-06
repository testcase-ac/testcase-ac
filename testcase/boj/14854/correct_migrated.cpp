#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll c[38][38],f27[27],i27[27];
vector<int> luca(ll n,int m) {
    vector<int> v;
    while(n) {
        v.push_back(n%m);
        n/=m;
    } return v;
}
ll com(int n,int k,int m) {
    if(n<k) return 0;
    if(n/2<k) k=n-k;
    ll &r=c[n][k];
    if(r!=-1) return r;
    if(k==0) return r=1;
    if(k==1) return r=n;
    return r=(com(n-1,k-1,m)+com(n-1,k,m))%m;
}
ll mdcm(ll n,ll k,int m) {
    memset(c,-1,sizeof(c));
    ll r=1;
    vector<int> a,b;
    a=luca(n,m);b=luca(k,m);
    int j=min(a.size(),b.size());
    for(int i=0;i<j;i++) {
        int n=a[i],x=b[i];
        r*=com(n,x,m);
        r%=m;
    } return r;
}
ll mdcm27(ll n,ll m) {
    ll r=n-m,d=0,a=1,n1[30],m1[30],r1[30],n2[30],m2[30],r2[30],c[30],k=0;
    while(n||m||r||d <=2) {
        n1[d]=n%3;m1[d]=m%3;r1[d]=r%3;
        n2[d]=n%27;m2[d]=m%27;r2[d]=r%27;
        a=a*f27[n2[d]]%27*i27[m2[d]]%27*i27[r2[d]]%27;
        n/=3;m/=3;r/=3;d++;
    } for(int i=0;i<d;i++) {
        if(m1[i]+r1[i]+k>=3) {c[i]=1;k=1;}
        else {c[i]=0;k=0;}
    } int p=0,q=0;
    for(int i=0;i<d;i++) {
        if(i>=2) p+=c[i];
        q+=c[i];
    } if(p%2) a=-a;
    for(int i=0;i<q;i++) a*=3;
    return (a%27+27)%27;
}
ll pw(ll a,ll b,ll m) {
	ll r=1;
	while(b) {
		if(b&1) r=r*a%m;
		a=a*a%m;
		b>>=1;
	} return r;
}
ll inv(ll a,ll m) {
	ll m0=m,x0=0,x1=1;
	if(m==1) return 1;
	while(a>1) {
		ll q=a/m;
		tie(a,m)=make_pair(m,a%m);
		tie(x0,x1)=make_pair(x1-q*x0,x0);
	} if(x1<0) x1+=m0;
	return x1;
}
ll crt(const vector<ll>& v,const vector<ll>& p) {
	ll m=1,r=0;
	for(auto i:p) m*=i;
	for(int i=0;i<v.size();i++) {
		ll mi=m/p[i];
		ll iv=inv(mi%p[i],p[i]);
		r=(r+v[i]*mi%m*iv%m)%m;
	} return r;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for(int i=0;i<27;i++) {
		if(!i) f27[i]=1;
		else if(i%3) f27[i]=f27[i-1]*i%27;
		else f27[i]=f27[i-1];
		i27[i]=inv(f27[i],27);
	} int t;
    ll n,k,a,b,c,d,m;
    cin>>t;
    while(t--) {
        cin>>n>>k;
        a=mdcm(n,k,11);b=mdcm(n,k,13);c=mdcm(n,k,37);d=mdcm27(n,k);
        cout<<crt({a,b,c,d},{11,13,37,27})<<'\n';
    }
}

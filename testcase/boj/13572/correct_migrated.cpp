#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll M,M1=29,M2=34483;
const ll MM=1000007;
ll pw(ll a,ll n) {
    ll r=1;
    while(n) {
        if(n&1) r=r*a%M;
        a=a*a%M;
        n>>=1;
    } return r;
}
vector<int> berlekamp_massey(vector<int> x) {
    vector<int> s,v;
    int f,d;
    for(int i=0;i<x.size();i++) {
        ll t=0;
        for(int j=0;j<v.size();j++) t=(t+(ll)x[i-j-1]*v[j])%M;
        if((t-x[i])%M==0) continue;
        if(v.empty()) {
            v.resize(i+1);
            f=i;
            d=(t-x[i])%M;
            continue;
        } ll k=-(x[i]-t)*pw(d,M-2)%M;
        vector<int> c(i-f-1);
        c.push_back(k);
        for(auto &j:s) c.push_back(-j*k%M);
        if(c.size()<v.size()) c.resize(v.size());
        for(int j=0;j<v.size();j++) c[j]=(c[j]+v[j])%M;
        if(i-f+(int)s.size()>=(int)v.size()) tie(s,f,d)=make_tuple(v,i,(t-x[i])%M);
        v=c;
    } for(auto &i:v) i=(i%M+M)%M;
    return v;
}
int get_nth(vector<int> rec,vector<int> dp,ll n) {
	int m=rec.size();
	static ll a[310],b[310],c[620];
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	a[0]=1;
	if(m==1)b[0]=rec[0];
	else b[1]=1;
	auto mul=[&](ll *x,ll *y) {
		memset(c,0,sizeof(c));
		for(int i=0;i<m;i++) {
			for(int j=0;j<m;j++) {
				c[i+j]+=x[i]*y[j];
				if(c[i+j]>=(1LL<<62)) c[i+j]%=M;
			}
		} for(int i=2*m-2;i>=m;i--) {
			ll v=c[i]%M;
			if(!v) continue;
			for(int j=1;j<=m;j++) {
				c[i-j]+=v*rec[j-1];
				if(c[i-j]>=(1LL<<62)) c[i-j]%=M;
			}
		} for(int i=0;i<m;i++) x[i]=c[i]%M;
	}; while(n) {
		if(n&1) mul(a,b);
		mul(b,b);
		n>>=1;
	} ll r=0;
	for(int i=0;i<m;i++) r=(r+a[i]*dp[i])%M;
	return r;
}
int nth(vector<int> x,ll n) {
    if(n<x.size()) return x[n];
    vector<int> v=berlekamp_massey(x);
    if(v.empty()) return 0;
    return get_nth(v,x,n);
}
int dx[8]={1,1,-1,-1,2,2,-2,-2},dy[8]={2,-2,2,-2,1,-1,1,-1};
int main() {
    vector<vector<int>> a(23);
    int d[23]={4,6,11,15,22,28,37,45,56,66,78,89,104,120,137,153,172,190,210,231,254,276,301};
	for(int n=2;n<=24;n++) {
		int m=n*2;
		static int f[700][50][50];
		memset(f,0,sizeof(f));
		for(int x=0;x<m;x++) for(int y=0;y<m;y++) if((x==0||x==m-1)&&(y==0||y==m-1)) f[0][x][y]=1;
		for(int l=1;l<d[n-2]*2+5;l++) {
			for(int x=0;x<m;x++) for(int y=0;y<m;y++) {
				int r=((x==0||x==m-1)&&(y==0||y==m-1));
				for(int z=0;z<8;z++) {
					int nx=x+dx[z],ny=y+dy[z];
					if(nx<0||ny<0||nx>=m||ny>=m) continue;
					r+=f[l-1][nx][ny];
					if(r>=MM) r-=MM;
				} f[l][x][y]=r;
			}
		} for(int k=1;k<d[n-2]*2+5;k++) a[n-2].push_back(f[k][0][0]);
	} int t,n,k;
    cin>>t;
    while(t--) {
        cin>>n>>k;
        M=M1;
        ll p=nth(a[n-2],k-1);
        M=M2;
        ll q=nth(a[n-2],k-1);
        ll iv=pw(M1,M2-2);
        p=(q-p+M2)%M2*iv%M2*M1+p;
        cout<<p<<'\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
struct mint {
	using u32=uint32_t;
	using u64=uint64_t;
	struct Barrett {
		u32 m;
		u64 im;
		Barrett():m(1),im(0){}
		Barrett(u32 m):m(m),im((~0ULL)/m){}
		u32 umod() const {return m;}
		u32 mul(u32 a,u32 b) const {
			u64 z=(u64)a*b;
			u32 x=(u32)(z-(u64)((u64)((__uint128_t)z*im>>64))*m);
			if(x>=m) x-=m;
			return x;
		}
	}; u32 _v;
	static Barrett bt;
	mint():_v(0){}
	mint(long long v){long long x=v%bt.umod();if(x<0) x+=bt.umod();_v=x;}
	int val() const{return _v;}
	static void set_mod(u32 m){bt=Barrett(m);}
	mint& operator++(){_v++;if(_v==bt.umod())_v=0;return *this;}
	mint& operator--(){if(_v==0)_v=bt.umod(); _v--;return *this;}
	mint operator++(int){mint r=*this;++*this;return r;}
	mint operator--(int){mint r=*this;--*this;return r;}
	mint& operator+=(const mint &r){_v+=r._v; if(_v>=bt.umod())_v-=bt.umod(); return *this;}
	mint& operator-=(const mint &r){_v+=bt.umod()-r._v; if(_v>=bt.umod())_v-=bt.umod(); return *this;}
	mint& operator*=(const mint &r){_v=bt.mul(_v,r._v); return *this;}
	mint& operator/=(const mint &r){return *this *= r.inv();}
	mint operator+() const{return *this;}
	mint operator-() const{return mint::raw(0)-*this;}
	mint pw(long long n) const {
		assert(n>=0);
		mint x=*this,r=1;
		while(n) {if(n&1) r*=x;x*=x;n>>=1;}
		return r;
	} mint inv() const{return pw(bt.umod()-2);}
	static mint raw(u32 v){mint r;r._v=v;return r;}
	friend mint operator+(mint a,const mint &b){return a+=b;}
	friend mint operator-(mint a,const mint &b){return a-=b;}
	friend mint operator*(mint a,const mint &b){return a*=b;}
	friend mint operator/(mint a,const mint &b){return a/=b;}
	friend bool operator==(const mint &a,const mint &b){return a._v==b._v;}
	friend bool operator!=(const mint &a,const mint &b){return a._v!=b._v;}
}; mint::Barrett mint::bt;
using mat=vector<vector<mint>>;
using matpol=vector<vector<vector<mint>>>;
void hessenberg(mat&A) {
    int n=A.size();
    for(int i=1;i<n;i++) {
        for(int j=i;j<n;j++) { 
            if(A[j][i-1]!=0){
                swap(A[i],A[j]);
                for(int k=0;k<n;k++) {swap(A[k][i],A[k][j]);}
                break;
            }
        } if(A[i][i-1]==0) {continue;}
        mint x=A[i][i-1],y=x.inv();
        for(int j=0;j<n;j++) {A[j][i]*=x;}
        for(int j=i-1;j<n;j++) {A[i][j]*=y;}
        for(int j=i+1;j<n;j++) {
			mint z=A[j][i-1],w=-z;
			for(int k=0;k<n;k++) {A[k][i]=A[k][j]*z+A[k][i];}
			for(int k=i-1;k<n;k++) {A[j][k]=A[i][k]*w+A[j][k];}
		}
    }
}
vector<mint> charpoly(mat A) {
    if(A.empty()) {return {1};}
    hessenberg(A);
    int n=A.size();
    vector<vector<mint>> dp(n+1,vector<mint>(n+1));
    dp[0][0]=1;
    for(int i=0;i<n;i++) {
        mint x=1;
        for(int j=i;~j;j--) {
            mint y=-x*A[j][i];
            for(int k=0;k<=j;k++) dp[i+1][k]=y*dp[j][k]+dp[i+1][k];
			if(j) x*=A[j][j-1];
        } for(int k=0;k<=i;k++) dp[i+1][k+1]=dp[i][k]+dp[i+1][k+1];
    } return dp[n];
}
vector<mint> polymod(vector<mint> a,const vector<mint>& mod) {
    int n=mod.size();
    if(n==0) return a;
    while(!a.empty()&&!a.back().val()) a.pop_back();
    if(a.size()<n) return a;
    vector<mint> r=a;
    mint t=mod.back().inv();
    for(int i=r.size()-1;i>=n-1;i--) {
        if(!r[i].val()) continue;
        mint c=r[i]*t;
        for(int j=0;j<n;j++) r[i-n+1+j]-=c*mod[j];
    } while(!r.empty()&&!r.back().val()) r.pop_back();
    return r;
}
vector<mint> polymul(const vector<mint>&a,const vector<mint>&b,const vector<mint>&mod) {
	if(a.empty()||b.empty()) return {};
	vector<mint> r(a.size()+b.size()-1);
	for(int i=0;i<a.size();i++) for(int j=0;j<b.size();j++) r[i+j]+=a[i]*b[j];
	return polymod(r,mod);
}
matpol matmul(const matpol&X,const matpol&Y,const vector<mint>&mod) {
	matpol Z(2,vector<vector<mint>>(2));
	int n=mod.size();
	for(int i=0;i<2;i++) for(int j=0;j<2;j++) {
		vector<mint> t(n*2);
		for(int k=0;k<2;k++) {
			if(X[i][k].empty()||Y[k][j].empty()) continue;
			for(int a=0;a<X[i][k].size();a++) {
				if(!X[i][k][a].val()) continue;
				for(int b=0;b<Y[k][j].size();b++) t[a+b]+=X[i][k][a]*Y[k][j][b];
			}
		} Z[i][j]=polymod(t,mod);
	} return Z;
}
vector<mint> xx[2];
vector<mint> f(long long k,const vector<mint>&mod) {
	int n=mod.size();
	if(n==0) return {0};
	vector<vector<vector<mint>>> A(2,vector<vector<mint>>(2));
	A[0][0]={2,1};A[0][1]={-1};A[1][0]={1};A[1][1]={0};
	matpol R(2,vector<vector<mint>>(2));
	R[0][0]={1};R[1][1]={1};
	long long t=k-1;
	while(t) {
		if(t&1) R=matmul(R,A,mod);
		A=matmul(A,A,mod);
		t>>=1;
	} vector<mint> r(n);
	auto v=polymul(R[0][0],xx[1],mod);
	for(int d=0;d<v.size();d++) r[d]+=v[d];
	v=polymul(R[0][1],xx[0],mod);
	for(int d=0;d<v.size();d++) r[d]+=v[d];
	while(!r.empty()&&!r.back().val()) r.pop_back();
	return r;
}
mint resultant(vector<mint> A,vector<mint> B) {
	while(!A.empty()&&!A.back().val()) A.pop_back();
	while(!B.empty()&&!B.back().val()) B.pop_back();
	if(A.empty()||B.empty()) return 0;
	mint r=1;
	while(B.size()>1) {
		int a=A.size()-1,b=B.size()-1;
		vector<mint>C=polymod(A,B);
		if(C.empty()) return 0;
		int c=C.size()-1;
		if((a*b)%2) r=-r;
		if(a>c) r*=B.back().pw(a-c);
		A=B;B=C;
	} return r*B[0].pw(A.size()-1);
}
int main() {
    mint::set_mod(1e9+7);
    xx[0]={0};
    xx[1]={1};
    long long n,m,k;
    cin>>n>>m>>k;
    if(n==1) {cout<<1;return 0;}
    mat L(n,vector<mint>(n,0));
    for(int i=0;i<m;i++) {
        int a,b;
        cin>>a>>b;
        a--;b--;
        L[a][b]--;
        L[b][a]--;
        L[a][a]++;
        L[b][b]++;
    } auto p=charpoly(L);
    for(int i=0;i<p.size()-1;i++) p[i]=p[i+1];
    p.pop_back();
    auto q=f(k,p);
    mint r=resultant(p,q);
    r*=p[0];
    r/=n;
    if(p.size()%2==0) r=-r;
    cout<<r.val();
}

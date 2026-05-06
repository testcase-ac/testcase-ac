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
using mat=vector<vector<vector<mint>>>;
vector<int> tt[36];
vector<mint> t(int n) {
    vector<mint> r;
    for(int i:tt[n]) r.push_back(i);
	return r;
}
vector<mint> polymod(vector<mint>a,const vector<mint>&mod) {
	int n=mod.size();
	if(n==0) return a;
	while(!a.empty()&&!a.back().val()) a.pop_back();
	if(a.empty()||a.size()<n) return a;
	mint t=mod.back().inv();
	while(a.size()>=n) {
		mint k=a.back()*t;
		if(k.val()) {
			int p=a.size()-n;
			for(int i=0;i<n;i++) a[p+i]-=mod[i]*k;
		} while(!a.empty()&&!a.back().val()) a.pop_back();
	} return a;
}
vector<mint> polymul(const vector<mint>&a,const vector<mint>&b,const vector<mint>&mod) {
	if(a.empty()||b.empty()) return {};
	vector<mint> r(a.size()+b.size()-1);
	for(int i=0;i<a.size();i++) for(int j=0;j<b.size();j++) r[i+j]+=a[i]*b[j];
	return polymod(r,mod);
}
mat matmul(const mat&X,const mat&Y,const vector<mint>&mod) {
	mat Z(4,vector<vector<mint>>(4));
	int n=mod.size();
	for(int i=0;i<4;i++) for(int j=0;j<4;j++) {
		vector<mint> t(n*2);
		for(int k=0;k<4;k++) {
			if(X[i][k].empty()||Y[k][j].empty()) continue;
			for(int a=0;a<X[i][k].size();a++) {
				if(!X[i][k][a].val()) continue;
				for(int b=0;b<Y[k][j].size();b++) t[a+b]+=X[i][k][a]*Y[k][j][b];
			}
		} Z[i][j]=polymod(t,mod);
	} return Z;
}
vector<mint> tmod(long long m,const vector<mint>&mod) {
	int n=mod.size();
	if(n==0) return {0};
	if(m<4) return polymod(t(m),mod);
	vector<vector<mint>> f(4);
	f[0]={0,-2,1};
	f[1]={-1,1};
	f[2]={0,1};
	f[3]={1};
	vector<vector<vector<mint>>> A(4,vector<vector<mint>>(4));
	for(int i=0;i<4;i++) for(int j=0;j<4;j++) A[i][j]={};
	A[0][1]={-2,1};
	A[0][3]={-1};
	A[1][0]={1};
	A[2][1]={1};
	A[3][2]={1};
	mat R(4,vector<vector<mint>>(4));
	for(int i=0;i<4;i++) R[i][i]={1};
	long long t=m-3;
	while(t) {
		if(t&1) R=matmul(R,A,mod);
		A=matmul(A,A,mod);
		t>>=1;
	} vector<mint> r(n);
	for(int j=0;j<4;j++) {
		auto v=polymul(R[0][j],f[j],mod);
		for(int d=0;d<v.size();d++) r[d]+=v[d];
	} while(!r.empty()&&!r.back().val()) r.pop_back();
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
    cin.tie(0);
    tt[0]={1};
    tt[1]={0,1};
    tt[2]={-1,1};
    tt[3]={0,-2,1};
    for(int i=4;i<36;i++) {
        auto x=tt[i-2],y=tt[i-4];
	    int p=x.size(),q=y.size();
	    x.push_back(0);
	    for(int i=p-1;i>=0;i--) {
		    x[i+1]+=x[i];
		    x[i]*=-2;
	    } for(int i=0;i<q;i++) x[i]-=y[i];
	    tt[i]=x;
    } int T,p;
	long long n,m;
	cin>>T;
	while(T--) {
		cin>>n>>m>>p;
		mint::set_mod(p);
		if(n>m) swap(n,m);
		if(n==1) {
			cout<<1-m%2<<'\n';
			continue;
		} auto x=t(n);
		for(int i=1;i<x.size();i+=2) x[i]=-x[i];
		auto y=tmod(m,x);
		auto r=resultant(x,y);
		if((m+1)/2%2&&x.size()%2==0) r=-r;
		r*=x.back().pw(y.size()+1);
		cout<<r.val()<<'\n';
	}
}

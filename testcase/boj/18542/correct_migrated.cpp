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
vector<int> cycle(vector<int> p) {
    int n=p.size();
    vector<bool> b(n,0);
    vector<int> r;
    for(int i=0;i<n;i++) {
        if(b[i]) continue;
        int t=i,k=0;
        while(1) {
            b[t]=1;
            t=p[t];
            k++;
            if(t==i) break;
        } r.push_back(k);
    } return r;
}
int main() {
    mint::set_mod(1e9+7);
    int n;
    cin>>n;
    vector<int> a(n),pi(n);
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) {cin>>pi[i];pi[i]--;}
    auto d=cycle(pi);
    if(d.size()>1) {cout<<0;return 0;}
    vector<int> inv(n),a0(n);
    for(int i=0;i<n;i++) inv[pi[i]]=i;
    a0[0]=0;
    for(int i=1;i<n;i++) a0[i]=inv[a0[i-1]];
    auto c=cycle(a0);
    mint f=1;
    for(int i:c) if(i%2==0) f=-f;
    vector<mint> p(n+1,0),q(n);
    q[0]=a[a0[0]];
    for(int i=1;i<n;i++) q[i]=a[a0[n-i]];
    p[0]=-1;p[n]=1;
    mint r=resultant(p,q);
    r*=f;
    cout<<r.val();
}

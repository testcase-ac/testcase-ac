#define private public
#include <bitset>
#undef private
#include <bits/stdc++.h>
#include <x86intrin.h>
using namespace std;
string a,b,s;
template<size_t _Nw> void _M_do_sub(_Base_bitset<_Nw>& A,const _Base_bitset<_Nw>& B) {
	for(int i=0,c=0;i<_Nw;i++) c=_subborrow_u64(c,A._M_w[i],B._M_w[i],(unsigned long long*)&A._M_w[i]);
}
template<> void _M_do_sub(_Base_bitset<1>& A,const _Base_bitset<1>& B) {A._M_w-=B._M_w;}
template<size_t _Nb> bitset<_Nb>& operator-=(bitset<_Nb>& A,const bitset<_Nb>& B) {return _M_do_sub(A,B), A;}
template<size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb>& A,const bitset<_Nb>& B) {bitset<_Nb> C(A);return C-=B;}
template<size_t sz>
vector<int> lcsl(int l,int r,int L,int R,bool inv) {
	bitset<sz> x,y[26],t,k;
	if(!inv) for(int i=L;i<=R;i++) y[b[i]-'a'][i-L]=1;
	else for(int i=R;i>=L;i--) y[b[i]-'a'][R-i]=1;
	for(int i=l;i<=r;i++) {
		char c=inv?a[r-i+l]:a[i];
		x=y[c-'a']|t;
		t<<=1;t[0]=1;
		t=x&(x^(x-t));
	} vector<int> ret(R-L+3);
	if(inv) for(int i=R;i>=L;i--) ret[i-L+1]=ret[i-L+2]+t[R-i];
	else for(int i=L;i<=R;i++) ret[i-L+1]=ret[i-L]+t[i-L];
	return ret;
}
vector<int> lcslen(int l,int r,int L,int R,bool inv) {
	int len=R-L+1;
	if(len<=64) return lcsl<64>(l,r,L,R,inv);
	else if(len<=128) return lcsl<128>(l,r,L,R,inv);
	else if(len<=256) return lcsl<256>(l,r,L,R,inv);
	else if(len<=512) return lcsl<512>(l,r,L,R,inv);
	else if(len<=1024) return lcsl<1024>(l,r,L,R,inv);
	else if(len<=2048) return lcsl<2048>(l,r,L,R,inv);
	else if(len<=4096) return lcsl<4096>(l,r,L,R,inv);
	else if(len<=8192) return lcsl<8192>(l,r,L,R,inv);
	return lcsl<16384>(l,r,L,R,inv);
}
void lcs(int l,int r,int L,int R) {
	if(l>r||L>R) return;
	if(l==r) {
		for(int i=L;i<=R;i++) if(a[l]==b[i]) {s+=a[l];return;}
		return;
	} int m=(l+r)/2,mx=L;
	auto v1=lcslen(l,m,L,R,0),v2=lcslen(m+1,r,L,R,1);
	for(int i=L+1;i<=R+1;i++) if(v1[mx-L]+v2[mx-L+1]<v1[i-L]+v2[i-L+1]) mx=i;
	lcs(l,m,L,mx-1);
	lcs(m+1,r,mx,R);
}
int main() {
    int n,m;
	cin>>n>>m>>a>>b;
	lcs(0,n-1,0,m-1);
	cout<<s.length()<<'\n'<<s;
}

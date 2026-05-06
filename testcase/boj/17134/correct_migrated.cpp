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
	}
	if(inv) for(int i=0;i<n;i++) a[i]/=n;
}
vector<ll> multiply(vector<ll> &a,vector<ll> &b) {
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
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<int> prime;
    vector<bool> notp(1000001,0);
    for(int i=2;i*i<=1000000;i++){
        if(!notp[i]){
            prime.push_back(i);
            for(int j=i+i;j<=1000000;j+=i){
                notp[j]=1;
            }
        }
    } for(int i=2;i<=1000000;i++){
        if(!notp[i]) prime.push_back(i);
    } vector<ll> a(1<<21),b(1<<21);
    for(int i=0;i<prime.size();i++){
        a[prime[i]]=1;
        if(prime[i]*2<=1000000){
            b[2*prime[i]]=1;
        }
    } vector<ll> m=multiply(a,b);
	int t,n;
	cin>>t;
	while(t--) {
	    cin>>n;
	    cout<<m[n]<<'\n';
	}
}

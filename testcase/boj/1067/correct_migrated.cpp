#include <bits/stdc++.h>

using namespace std;
using cd=complex<double>;
const double pi=acos(-1);

void fft(vector<cd>&a,bool inv){
	int n=a.size();
	for(int i=1,j=0;i<n;i++){
		int bit=n>>1;
		while(j>=bit){
			j-=bit;
			bit>>=1;
		}
		j+=bit;
		if(i<j) swap(a[i],a[j]);
	}
	for(int i=1;i<n;i<<=1){
		double ang=(inv?-1:1)*pi/i;
		cd w={cos(ang),sin(ang)};
		for(int j=0;j<n;j+=i<<1){
			cd th={1,0};
			for(int k=0;k<i;k++){
				cd tmp=a[i+j+k]*th;
				a[i+j+k]=a[j+k]-tmp;
				a[j+k]+=tmp;
				th*=w;
			}
		}
	}
	if(inv) for(int i=0;i<n;i++) a[i]/=n;
}

vector<long long> multiply(vector<long long>&a,vector<long long>&b){
	vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());
	int n=1;
	while(n<a.size()+b.size())n<<=1;
	fa.resize(n);
	fb.resize(n);
	fft(fa,0);
	fft(fb,0);
	for(int i=0;i<n;i++)fa[i]*=fb[i];
	fft(fa,1);
	vector<long long>r(n);
	for(int i=0;i<n;i++)r[i]=(long long)round(fa[i].real());
	return r;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	vector<long long>a(n*2),b(n);
	for(int i=0;i<n;i++){
		cin>>a[i];
		a[i+n]=a[i];
	}
	for(int i=1;i<=n;i++)cin>>b[n-i];
	vector<long long>m=multiply(a,b);
	long long move=0;
	for(long long x:m)move=max(move,x);
	cout<<move;
}

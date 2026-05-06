//GPT 코드
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	random_device rd;
	mt19937_64 r(rd());

	int n=r()%51+2;
	int k=r()%(n/2+1);

	ll g=r()%((ll)1e12-1)+2;

	vector<ll>a(n);

	for(int i=0;i<n-k;i++){
		ll x=r()%1000000+1;
		if(g*x>1e18)x=1;
		a[i]=g*x;
	}

	for(int i=n-k;i<n;i++){
		ll x=r()%((ll)1e18-1)+1;
		if(x%g==0)x++;
		a[i]=x;
	}

	shuffle(a.begin(),a.end(),r);

	cout<<n<<' '<<k<<'\n';
	for(int i=0;i<n;i++){
		cout<<a[i];
		if(i+1<n)cout<<' ';
	}
	cout<<'\n';
}

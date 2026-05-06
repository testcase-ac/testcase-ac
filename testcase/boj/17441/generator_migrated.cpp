//GPT 코드
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
	mt19937_64 r(chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> dn(3,100);
	uniform_int_distribution<int> dr(100,10000);
	uniform_real_distribution<long double> da(0,2*acos(-1));
	
	int n=dn(r);
	cout<<n<<'\n';
	
	vector<pair<long double,long double>> v;
	for(int i=0;i<n;i++){
		long double ang=da(r);
		long double rad=dr(r);
		v.push_back({ang,rad});
	}
	sort(v.begin(),v.end());
	
	for(int i=0;i<n;i++){
		long double x=v[i].second*cos(v[i].first);
		long double y=v[i].second*sin(v[i].first);
		cout<<(ll)x<<" "<<(ll)y<<'\n';
	}
}

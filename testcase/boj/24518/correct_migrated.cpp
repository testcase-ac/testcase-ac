#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll M=1e9+7;
ll f(ll a,ll m) {return ((a+1)/m)*m*(m-1)/2+(a-((a+1)/m)*m+1)*(a-((a+1)/m)*m)/2;}
int main() {
	ll n,m,r=0;
	cin>>n>>m;
	for(int i=1;i*i<=n;i++) r=(r+(n/i)*(i%m))%M;
	for(int i=1;i<n/(int)sqrt(n);i++) r=(r+i*(f(n/i,m)-f(n/(i+1),m)))%M;
	cout<<r;
}

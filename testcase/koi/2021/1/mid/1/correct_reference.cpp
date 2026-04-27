#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<db,db> pdb;
typedef tuple<int,int,int> tii;
typedef tuple<db,db,db> tdb;
typedef tuple<ll,ll,ll> tll;
typedef tuple<int,int,int,int> ti4;
typedef tuple<ll,ll,ll,ll> tl4;
typedef tuple<db,db,db,db> td4;
const ll mod=1e9+7;
const int N=1e5+5;
int n,a[N],s[N],ans;
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	for(int i=2;i<=n-1;i++) ans=max(ans,s[n-1]-a[1]+a[i]);
	for(int i=2;i<=n-1;i++) ans=max(ans,s[i-1]-a[1]+2*(s[n]-s[i]));
	for(int i=2;i<=n-1;i++) ans=max(ans,2*s[i-1]+s[n-1]-s[i]);
	cout<<ans;
	return 0;
}
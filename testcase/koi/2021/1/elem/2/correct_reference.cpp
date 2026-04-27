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
int n,a[N],s[N];
ll ans,pfx[N],sfx[N];
int main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		s[i]=s[i-1]+a[i];
	}
	if(s[n]%4!=0){
		cout<<0; return 0;
	}
	for(int i=1;i<=n;i++) pfx[i]=pfx[i-1]+(s[i]==s[n]/4);
	for(int i=n-1;i>=1;i--) sfx[i]=sfx[i+1]+(s[i]==3*s[n]/4);
	for(int i=2;i<n;i++) ans+=(s[i]==2*s[n]/4)*pfx[i-1]*sfx[i+1];
	cout<<ans;
	return 0;
}
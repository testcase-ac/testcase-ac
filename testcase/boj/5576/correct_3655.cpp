#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int a[10], b[10];
	rep(i,10) cin >> a[i];
	sort(a, a+10);
	rep(i,10) cin >> b[i];
	sort(b, b+10);
	printf("%d %d", a[7]+a[8]+a[9], b[7]+b[8]+b[9]);
}

#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		int a[n];
		rep(i,n) cin >> a[i];
		sort(a, a+n);
		int m;
		cin >> m;
		while(m--) {
			int t;
			cin >> t;
			if(binary_search(a,a+n,t)) {
				cout << "1\n";
			} else {
				cout << "0\n";
			}
		}
	}
}

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
	int a[5];
	rep(i,5) cin >> a[i];
	while(1) {
		bool flag = false;
		rep(i,4) {
			if(a[i] > a[i+1]) {
				flag = true;
				swap(a[i], a[i+1]);
				rep(i,5) cout << a[i] << ' ';
				cout << '\n';
			}
		}
		if(!flag) break;
	}
}

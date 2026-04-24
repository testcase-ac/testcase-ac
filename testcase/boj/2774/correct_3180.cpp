#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int arr[10] = {}, ans = 0;
		for(char c: s) {
			int n = c - '0';
			if(!arr[n]) {
				ans++;
				arr[n] = true;
			}
		}
		cout << ans << '\n';
	}
}

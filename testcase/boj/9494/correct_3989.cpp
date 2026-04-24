#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	while(1) {
		int n;
		cin >> n;
		if(!n) return 0;
		vector<vector<int>> arr(n);
		vector<int> len(n);
		string s;
		getchar();
		rep(i,n) {
			getline(cin, s);
			len[i] = sz(s);
			rep(j, len[i]) {
				if(s[j] == ' ') arr[i].push_back(j+1);
			}
		}
		int pos = 0;
		rep(i,n) {
			if(pos > len[i]) continue;
			auto it = lower_bound(arr[i].begin(), arr[i].end(),pos);
			if(it == arr[i].end()) pos = len[i]+1;
			else pos = *it;
		}
		cout << pos << '\n';
	}
}

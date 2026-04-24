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
	int n;
	cin >> n;
	bool has1 = false;
	while(n) {
		if(n&1) {
			if(!has1)
				has1 = true;
			else
				return !(cout << 0);
		}
		n >>= 1;
	}
	cout << 1;
}

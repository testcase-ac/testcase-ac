#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int y = 0, m = 0;
	rep(i,n) {
		int t;
		cin >> t;
		y += ((t/30)+1)*10;
		m += ((t/60)+1)*15;
	}
	if(y < m) printf("Y %d", y);
	else if(y > m) printf("M %d", m);
	else printf("Y M %d", y);
}

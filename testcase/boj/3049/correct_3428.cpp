#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define fastio() ios::sync_with_stdio(false);cin.tie(NULL)

using namespace std;

int main() {
	fastio();
	int n;
	cin >> n;
	int cnt = 0;
	for(int i=2; i<=n-2; i++)
		cnt += (i-1)*(n-1-i);
	cout << cnt * n / 4;
}

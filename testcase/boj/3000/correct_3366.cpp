#include <bits/stdc++.h>
using namespace std;
const int MX = 100001;
int cntx[MX], cnty[MX];
pair<int, int> pts[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> pts[i].first >> pts[i].second;
		cntx[pts[i].first]++;
		cnty[pts[i].second]++;
	}
	long long ans = 0;
	for(int i=0; i<n; i++) {
		int x, y;
		tie(x, y) = pts[i];
		ans += (long long)(cntx[x]-1)*(cnty[y]-1);
	}
	cout << ans;
}

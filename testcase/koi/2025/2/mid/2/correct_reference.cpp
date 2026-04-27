#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
using namespace std;
using lint = long long;
using pi = array<lint, 2>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k, c;
	cin >> n >> k >> c;
	vector<lint> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(all(a));
	a.insert(a.begin(), 0);
	for (int i = 1; i <= n; i++)
		a[i] += a[i - 1];
	int j = 0;
	for (int x = 1; x <= c; x++) {
		while (j < n - k && a[j + 1] <= x)
			j++;
		cout << a[j + k] - a[j] << "\n";
	}
}
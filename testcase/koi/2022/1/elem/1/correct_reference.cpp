#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 1e9;

int N;
vector<int> a, b;

int main() {
	cin >> N;

	a.resize(N);
	b.resize(N);

	for (int i=0; i<N; i++) cin >> a[i] >> b[i];

	int ans = inf;
	for (int i=0; i<N; i++) if (a[i] <= b[i]) {
		ans = min(ans, b[i]);
	}

	if (ans == inf) cout << -1 << '\n';
	else cout << ans << '\n';
}
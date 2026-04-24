#include <bits/stdc++.h>
using namespace std;
#define int long long
struct st { int b, j; };
int init[50][50], arr[50][50], init_a[50], b[50], a[50], n, m;
st v[50];
bool chk() {
	memcpy(a, init_a, sizeof a);
	for(int j=0; j<m; j++)
		v[j] = {b[j], j};
	for(int i=0; i<n; i++) {
		sort(v, v+m, [](st x, st y){return x.b > y.b;});
		for(st& t: v) {
			if(a[i] <= 0)
				break;
			if(t.b <= 0)
				break;
			if(init[i][t.j] != -1)
				continue;
			a[i]--;
			t.b--;
		}
		if(a[i] > 0)
			return 0;
	}
	return 1;
}
int32_t main() {
	cin >> n >> m;
	memset(init, -1, sizeof init);
	memset(arr, -1, sizeof arr);
	for(int i=0; i<n; i++)
		cin >> init_a[i];
	for(int i=0; i<m; i++)
		cin >> b[i];
	if(accumulate(init_a, init_a+n, 0ll) != accumulate(b, b+m, 0ll))
		return !(cout << -1);
	if(!chk())
		return !(cout << -1);
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++) {
			init[i][j] = 0;
			if(!chk()) {
				init[i][j] = 1;
				init_a[i]--;
				b[j]--;
			}
		}
	}
	for(int i=0; i<n; i++) {
		for(int j=0; j<m; j++)
			cout << init[i][j];
		cout << '\n';
	}
}

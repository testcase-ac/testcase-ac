#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

using lint = long long;
using pint = pair<int, int>;
#define x first
#define y second

int N, M;
lint A[100001], B[100001], P[100001];
vector<pint> g[100001];

bool possible = true;
vector<lint> fixedX;

void dfs(int x, int a, lint b) {
	if (A[x] != 0) {
		if (A[x] == a) {
			if (B[x] != b) possible = false;
		} else {
			if ((B[x] + b) % 2 == 1) possible = false;
			else {
				lint v = (A[x] == 1) ? (b - B[x]) / 2 : (B[x] - b) / 2;
				fixedX.push_back(v);
			}
		}

		return;
	}
	A[x] = a;
	B[x] = b;
	P[x] = -a*b;

	for (pint p : g[x]) {
		int y = p.x, w = p.y;

		dfs(y, -a, w-b);
	}
}

int main() {
	cin >> N >> M;
	
	for (int i=0; i<M; i++) {
		int x, y, w;

		cin >> x >> y >> w;

		g[x].emplace_back(y, w);
		g[y].emplace_back(x, w);
	}

	dfs(1, 1, 0);

	sort(fixedX.begin(), fixedX.end());
	fixedX.resize(unique(fixedX.begin(), fixedX.end()) - fixedX.begin());

	if (fixedX.size() > 1 or !possible) {
		cout << "No" << '\n';
		return 0;
	}

	sort(P+1, P+N+1);

	lint x;

	if (fixedX.empty()) x = P[(N+1)/2];
	else x = fixedX[0];

	cout << "Yes" << '\n';
	for (int i=1; i<=N; i++) {
		if (i != 1) cout << ' ';
		cout << A[i] * x + B[i];
	}

	cout << '\n';
}
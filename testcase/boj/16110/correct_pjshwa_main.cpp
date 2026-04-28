#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
int Av[MAXN][MAXN], Bv[MAXN][MAXN];

void solve() {
  int N, m, k; cin >> N >> m >> k;

  vector<pii> A, B;
  for (int i = 1; i <= m; ++i) {
    int x; cin >> x;
    A.emplace_back(x, i);
  }
  for (int i = 1; i <= k; ++i) {
    int x; cin >> x;
    B.emplace_back(x, i);
  }
  sort(A.begin(), A.end(), greater<pii>());
  sort(B.begin(), B.end(), greater<pii>());

  queue<int> qA, qB;
  for (auto& [cnt, i] : A) for (int j = 0; j < cnt; ++j) qA.push(i);
  for (auto& [cnt, i] : B) for (int j = 0; j < cnt; ++j) qB.push(i);

  for (int j = 0; j < N; ++j) for (int i = 0; i < N; ++i) {
    Av[i][(i + j) % N] = qA.front(); qA.pop();
    Bv[i][(i + j) % N] = qB.front(); qB.pop();
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) cout << Av[i][j] << 'v' << Bv[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

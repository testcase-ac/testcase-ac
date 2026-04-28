#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
vector<int> graph[MAX + 1];
ll N, A, B, L;
int ac[MAX + 1], bc[MAX + 1];
double P[MAX + 1];

void dfs(int v, int p, int l) {
  ac[l % A]++, bc[l % B]++;
  ll cac = ac[l % A], cbc = bc[l % B];

  for (int u : graph[v]) {
    if (u == p) continue;
    dfs(u, v, l + 1);
  }

  ll suba = ac[l % A] - cac + 1, subb = bc[l % B] - cbc + 1;
  double ap = suba * 1.0 / N, bp = subb * 1.0 / N;
  P[v] = ap + bp - ap * bp;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> N >> A >> B;
  L = A / __gcd(A, B) * B;

  for (int i = 1; i <= N; i++) graph[i].clear();

  for (int i = 2; i <= N; i++) {
    int x;
    cin >> x;
    graph[x].push_back(i);
  }

  dfs(1, 0, 1);

  double ans = 0;
  for (int i = 1; i <= N; i++) ans += P[i];
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}

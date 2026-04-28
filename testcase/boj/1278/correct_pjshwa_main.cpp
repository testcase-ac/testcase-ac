#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 17;
bool vis[1 << MAXN];
int N;
vector<int> cur;

// void dfs(int s, int l) {
//   if (l == (1 << N) - 1) {
//     cout << "cur = ";
//     for (int i : cur) cout << i << " ";
//     cout << "\n";
//   }

//   for (int i = 0; i < N; ++i) {
//     int ns = s ^ (1 << i);
//     if (ns == 0 || vis[ns]) continue;

//     vis[s ^ (1 << i)] = true;
//     cur.push_back(i);
//     dfs(s ^ (1 << i), l + 1);
//     cur.pop_back();
//     vis[s ^ (1 << i)] = false;
//   }
// }

void dfs(int n) {
  if (n == 1) return cout << "1\n", void();

  dfs(n - 1);
  cout << n << '\n';
  dfs(n - 1);
}

void solve() {
  cin >> N;

  cout << (1 << N) - 1 << '\n';
  dfs(N);
  cout << N << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

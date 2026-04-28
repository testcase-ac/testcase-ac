#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int E[MAX + 1];
 
void solve() {
  int N;
  cin >> N;
  for (int i = 2; i <= N; i++) cin >> E[i];

  int ans = N - 1;
  for (int i = N; i >= 3; i--) {
    if (E[i] == 0) continue;
    ans = min(ans, max(N - i + 1, 2));
    break;
  }

  bool comp = true;
  for (int i = 3; i <= N; i++) comp &= E[i];
  if (comp) ans = 1;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

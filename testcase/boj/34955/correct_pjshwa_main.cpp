#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int B[MAXN], F[MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 0; i < M; ++i) cin >> F[i];
  sort(B, B + N); sort(F, F + M);

  vector<pair<string, int>> ops;
  priority_queue<int, vector<int>, greater<int>> fish;
  int j = 0;
  for (int i = 0; i < N; ++i) {
    while (j < M && F[j] <= B[i]) ++j;
    if (j < M) {
      ops.emplace_back("fish", B[i]);
      fish.push(F[j]); F[j] = -1;
      ++j;
    }
  }
  if (fish.empty()) return cout << "0\n0\n", void();

  for (int j = 0; j < M; ++j) {
    if (F[j] != -1 && fish.top() < F[j]) {
      ops.emplace_back("bait", fish.top());
      ops.emplace_back("fish", fish.top());
      fish.pop();
      fish.push(F[j]);
      F[j] = -1;
    }
  }

  cout << ops.size() << '\n';
  for (auto &p : ops) cout << p.first << ' ' << p.second << '\n';

  ll ans = 0;
  while (!fish.empty()) {
    ans += fish.top();
    fish.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

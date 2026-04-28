#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
queue<tii> P[MAX + 10];
int A[MAX + 10];

void solve() {
  int N, Q; cin >> N >> Q;
  
  vector<tuple<int, int, int, int>> queries;
  for (int i = 0; i < Q; ++i) {
    int a, b, x; cin >> a >> b >> x;
    queries.emplace_back(a, b, x, i);
  }
  reverse(queries.begin(), queries.end());
  for (auto& [a, b, x, i] : queries) P[a].emplace(b, x, i);
  
  priority_queue<tii, vector<tii>, greater<tii>> wait;
  for (int i = 1; i <= N; ++i) {
    while (!P[i].empty()) {
      auto [b, x, qi] = P[i].front(); P[i].pop();
      wait.emplace(qi, b, x);
    }
    while (!wait.empty()) {
      auto [qi, b, x] = wait.top();
      if (b < i) wait.pop();
      else break;
    }

    if (!wait.empty()) A[i] = get<2>(wait.top());
  }

  for (int i = 1; i <= N; ++i) cout << A[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

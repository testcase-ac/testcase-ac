#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int uc[MAX + 1];

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) cin >> A[i].first >> A[i].second;
  sort(A.begin(), A.end());

  int X = 0;
  priority_queue<pii, vector<pii>, greater<pii>> use;
  priority_queue<int, vector<int>, greater<int>> avail;

  for (int i = 0; i < N; i++) {
    auto [x, y] = A[i];
    while (use.size() && use.top().first < x) {
      avail.push(use.top().second);
      use.pop();
    }

    int cur;
    if (avail.empty()) {
      cur = ++X;
    }
    else {
      cur = avail.top();
      avail.pop();
    }

    uc[cur]++;
    use.push({y, cur});
  }

  cout << X << '\n';
  for (int i = 1; i <= X; i++) cout << uc[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

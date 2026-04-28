#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  priority_queue<pii> L, R;
  int red = 0, blue = 0;
  for (int i = 0; i < N; i++) R.push({A[i], i});

  for (int i = 0; i < N - 1; i++) {
    L.push({A[i], i});
    while (R.top().second <= i) R.pop();

    int ltop = L.top().first, rtop = R.top().first;
    if (ltop > rtop) red++;
    if (ltop < rtop) blue++;
  }

  if (red > blue) cout << "R\n";
  else if (red < blue) cout << "B\n";
  else cout << "X\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

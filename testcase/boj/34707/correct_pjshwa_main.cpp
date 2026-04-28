#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN], K;

void print_ans(int si) {
  cout << "YES\n";
  for (int i = si; i < si + K; ++i) cout << A[i] << ' ';
}

void solve() {
  int N; cin >> N >> K;
  for (int i = 0; i < N; ++i) cin >> A[i];

  set<int> W;
  for (int i = 0; i < K; ++i) W.insert(A[i]);
  auto check = [&]() {
    int vmax = *W.rbegin(), vmin = *W.begin();
    return (vmax - vmin + 1) == (int)W.size();
  };
  if (check()) return print_ans(0);

  for (int i = K; i < N; ++i) {
    W.insert(A[i]);
    W.erase(A[i - K]);
    if (check()) return print_ans(i - K + 1);
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

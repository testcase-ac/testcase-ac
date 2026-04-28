#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50;
int d[MAX + 1];
pii A[MAX + 1];

int N;
void solve() {
  for (int i = 1; i <= N; i++) cin >> A[i].second >> A[i].first;
  sort(A + 1, A + N + 1);

  for (int i = 1; i <= N; i++) d[i] = 1;

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j < i; j++) {
      if (A[i].second >= A[j].first) d[i] = max(d[i], d[j] + 1);
    }
    ans = max(ans, d[i]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}

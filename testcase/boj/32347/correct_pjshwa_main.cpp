#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN + 1], Nxt[MAXN + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  int j = N;
  for (int i = N - 1; i >= 1; --i) {
    Nxt[i] = j;
    if (A[i] == 1) j = i;
  }

  int l = 1, r = N;
  while (l < r) {
    int m = (l + r) / 2;

    int i = N, cnt = 0;
    while (i > 1 && cnt <= K) {
      if (A[i] == 1) i = max(1, i - m), ++cnt;
      else i = Nxt[i];
    }
    
    if (cnt <= K) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

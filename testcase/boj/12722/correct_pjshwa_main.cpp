#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class FenwickTree {
public:
  int n;
  vector<int> bit;

  void init(int N) {
    n = N;
    bit.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) bit[i] = 1;
    for (int i = 1; i <= n; ++i) {
      int j = i + (i & -i);
      if (j <= n) bit[j] += bit[i];
    }
  }

  void dec(int p) {
    for (int i = p + 1; i <= n; i += i & -i) bit[i] -= 1;
  }

  int query(int L, int R) {
    if (R < 0 || L >= n || L > R) return 0;
    L = max(L, 0);
    R = min(R, n - 1);
    return sum(R + 1) - sum(L);
  }

  int kth(int k) {
    int idx = 0;
    int pw = 1;
    while (pw < n) pw <<= 1;
    for (int step = pw; step > 0; step >>= 1) {
      int next = idx + step;
      if (next <= n && bit[next] < k) {
        idx = next;
        k -= bit[next];
      }
    }
    return idx;
  }

private:
  int sum(int p) {
    int ret = 0;
    for (int i = p; i > 0; i -= i & -i) ret += bit[i];
    return ret;
  }
};

FenwickTree ft;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int K, N; cin >> K >> N;
  ft.init(K);
  vector<int> P(K);

  int idx = 0;
  for (int i = 1; i <= K; ++i) {
    ft.dec(idx); P[idx] = i;
    if (i == K) break;

    int rem = K - i;
    int l = (i + 1) % rem;
    if (l == 0) l = rem;

    // Find l-th filled spot after idx
    int q = ft.query(idx + 1, K - 1);
    if (q < l) idx = ft.kth(l - q);
    else idx = ft.kth(l + rem - q);
  }

  int x;
  for (int i = 0; i < N; ++i) {
    cin >> x;
    cout << P[x - 1] << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}

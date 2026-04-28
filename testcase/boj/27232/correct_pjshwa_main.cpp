#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAX = 5e5, INF = 1e18;
int A[MAX + 1], inv[MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  if (K == 1) return cout << "0\n", void();

  set<int> current; ll cur = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    inv[A[i]] = i;
    if (i < K) current.insert(A[i]);
  }

  int l = -1;
  for (int e : current) {
    if (l != -1) cur += abs(inv[e] - inv[l]);
    l = e;
  }

  ll ans = cur;
  for (int i = K; i < N; i++) {
    int rem = A[i - K], add = A[i];

    {
      auto it = current.find(rem);
      auto itn = it; ++itn;

      if (it == current.begin()) {
        cur -= abs(inv[rem] - inv[*itn]);
      }
      else if (itn == current.end()) {
        auto itp = it; --itp;
        cur -= abs(inv[rem] - inv[*itp]);
      }
      else {
        auto itp = it; --itp;
        cur -= abs(inv[rem] - inv[*itp]);
        cur -= abs(inv[rem] - inv[*itn]);
        cur += abs(inv[*itp] - inv[*itn]);
      }
      current.erase(it);
    }

    {
      current.insert(add);
      auto it = current.find(add);
      auto itn = it; ++itn;

      if (it == current.begin()) {
        cur += abs(inv[add] - inv[*itn]);
      }
      else if (itn == current.end()) {
        auto itp = it; --itp;
        cur += abs(inv[add] - inv[*itp]);
      }
      else {
        auto itp = it; --itp;
        cur += abs(inv[add] - inv[*itp]);
        cur += abs(inv[add] - inv[*itn]);
        cur -= abs(inv[*itp] - inv[*itn]);
      }
    }

    ans = min(ans, cur);
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

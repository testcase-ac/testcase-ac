#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool overlaps(string a, string b) {
  int az = a.size(), bz = b.size();
  int z = min(az, bz);
  for (int k = 1; k <= z; k++) {
    bool ok = true;
    for (int i = 0; i < k; i++) {
      if (a[az - k + i] != b[i]) {
        ok = false;
        break;
      }
    }
    if (ok) return true;
  }
  return false;
}

void solve() {
  int N; cin >> N;
  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    if (overlaps(A[i], A[j]) || overlaps(A[j], A[i])) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

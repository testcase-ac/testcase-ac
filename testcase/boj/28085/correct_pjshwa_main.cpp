#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX], N;

int cross(int r) {
  if (r == 0) return A[0];
  if (r == 1) return A[1];
  if (r == 2) return A[0] + A[1] + A[2];

  if (A[0] + A[r - 1] > 2 * A[1]) return A[0] + 2 * A[1] + A[r] + cross(r - 2);
  else return 2 * A[0] + A[r - 1] + A[r] + cross(r - 2);
}

void solve() {
  cin >> N;

  map<int, int> T;
  for (int i = 0; i < N; i++) cin >> A[i], T[A[i]]++;

  if (N == 1) return cout << A[0] << '\n', void();
  if (T.size() == 1) return cout << "-1\n", void();

  vector<int> V; int ans = 0;
  for (auto [k, v] : T) V.push_back(k);

  for (int i = 0; i < T[V[0]] - 1; i++) ans += 2 * V[1];
  T[V[0]] = 1;

  int Z = V.size(), i = Z - 1, j = Z - 2;
  while (i > 0) {
    // Remove two boats at a time, if possible
    if (j == 0) {
      ans += V[i] + V[j];
      if (--T[V[i]] == 0) i--;
    }
    else {
      int cost = V[i] + V[j] + 2 * V[0];
      if (j > 1 || T[V[1]] > 1) cost = min(cost, V[0] + 2 * V[1] + V[i]);

      ans += cost;
      if (--T[V[j]] == 0) j--;
      if (--T[V[i]] == 0) i--;
      while (T[V[i]] == 0) i--;
      while (i <= j) j--;
    }
  }
  ans -= V[0];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

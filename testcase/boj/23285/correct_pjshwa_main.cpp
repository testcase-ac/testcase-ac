#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int A[MAX + 1], C[MAX + 1];

void solve() {
  int N;
  cin >> N;
  for (int i = 1; i <= N - 2; i++) cin >> A[i], C[A[i]]++;

  vector<pii> ans;
  for (int i = 1; i <= N - 2; i++) {
    int u;
    for (u = 1; u <= N; u++) {
      if (C[u] == 0) {
        if (u < A[i]) ans.push_back({u, A[i]});
        else ans.push_back({A[i], u});

        C[u] = INF;
        break;
      }
    }
    C[A[i]]--;
  }

  if (A[N - 2] == N) ans.push_back({N - 1, N});
  else ans.push_back({A[N - 2], N});

  sort(ans.begin(), ans.end());
  for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

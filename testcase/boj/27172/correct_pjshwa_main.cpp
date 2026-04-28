#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX + 1], T[MAX + 1], S[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    T[A[i]]++;
  }

  for (int i = 0; i < N; i++) {
    for (int u = 2 * A[i]; u <= MAX; u += A[i]) {
      if (T[u] == 0) continue;

      S[A[i]]++;
      S[u]--;
    }
  }

  for (int i = 0; i < N; i++) cout << S[A[i]] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

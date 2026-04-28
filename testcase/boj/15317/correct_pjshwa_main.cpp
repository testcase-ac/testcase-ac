#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
int C[MAX + 1], S[MAX + 1];
int N, M, X;

bool check(int p) {
  ll need = 0;
  for (int i = p - 1; i >= 0; i--) {
    need += max(0, C[i] - S[p - 1 - i]);
  }
  return need <= X;
}

void solve() {
  cin >> N >> M >> X;
  for (int i = 0; i < N; i++) cin >> C[i];
  for (int i = 0; i < M; i++) cin >> S[i];
  sort(C, C + N);
  sort(S, S + M);
  reverse(S, S + M);

  int left = 0, right = min(N, M) + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (check(mid)) left = mid + 1;
    else right = mid;
  }
  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

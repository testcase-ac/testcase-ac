#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int S[MAX], N;

void toggle(int s) {
  if (s & 1) {
    for (int i = 0; i < N; i++) S[i] ^= 1;
  }
  if (s & 2) {
    for (int i = 0; i < N; i += 2) S[i] ^= 1;
  }
  if (s & 4) {
    for (int i = 1; i < N; i += 2) S[i] ^= 1;
  }
  if (s & 8) {
    for (int i = 0; i < N; i += 3) S[i] ^= 1;
  }
}

void print() {
  for (int i = 0; i < N; i++) cout << S[i];
  cout << '\n';
}

void solve() {
  int C, x; cin >> N >> C;
  fill(S, S + N, 1);

  vector<int> A, B;
  while (cin >> x, x != -1) A.push_back(x);
  while (cin >> x, x != -1) B.push_back(x);

  // All 4 buttons cancel themselves out, i.e. no button needs to be pressed more than once.
  for (int s = 0; s < (1 << 4); s++) {
    int cnt = __builtin_popcount(s);
    if (cnt > C || cnt % 2 != C % 2) continue;

    toggle(s); int f = 1;
    for (int e : A) f &= S[e - 1] == 1;
    for (int e : B) f &= S[e - 1] == 0;
    if (f) print();
    toggle(s);
  }
}

int main() {
  int t = 1;
  // cin >> t;
  while (t--) solve();
}

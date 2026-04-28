#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool next_repetition(int C[], int N, int K) {
  int i = K - 1;
  while (i >= 0 && C[i] == N - 1) i--;
  if (i < 0) return false;

  C[i]++;
  for (int j = i + 1; j < K; j++) C[j] = 0;
  return true;
}

void solve() {
  int A, B; cin >> A >> B;

  int C[4]{};
  do {
    for (int i = 0; i < 4; i++) cout << (char)(C[i] + 'a');
    cout << ' ';
    B--;
  } while (B && next_repetition(C, 26, 4));
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

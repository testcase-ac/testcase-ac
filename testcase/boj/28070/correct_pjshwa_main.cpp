#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int d[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    // Always in YYYY-MM form
    string S, T; cin >> S >> T;
    int Y1 = stoi(S.substr(0, 4)), M1 = stoi(S.substr(5, 2));
    int Y2 = stoi(T.substr(0, 4)), M2 = stoi(T.substr(5, 2));
    Y1 -= 2000; Y2 -= 2000; M1--; M2--;

    int V1 = Y1 * 12 + M1, V2 = Y2 * 12 + M2;
    d[V1]++; d[V2 + 1]--;
  }

  for (int i = 1; i < MAX; i++) d[i] += d[i - 1];

  int mmax = 0;
  for (int i = 0; i < MAX; i++) mmax = max(mmax, d[i]);
  for (int i = 0; i < MAX; i++) {
    if (d[i] == mmax) {
      int Y = i / 12 + 2000, M = i % 12 + 1;
      cout << Y << '-' << setw(2) << setfill('0') << M << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

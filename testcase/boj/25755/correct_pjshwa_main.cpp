#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 20;
int P[MAX][MAX];

char rev(int o) {
  if (o == 1 || o == 8) return o + '0';
  if (o == 2) return '5';
  if (o == 5) return '2';
  return '?';
}

void solve() {
  string W; int N;
  cin >> W >> N;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> P[i][j];

  if (W == "U" || W == "D") {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) cout << rev(P[N - 1 - i][j]) << ' ';
      cout << '\n';
    }
  }
  else {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) cout << rev(P[i][N - 1 - j]) << ' ';
      cout << '\n';
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

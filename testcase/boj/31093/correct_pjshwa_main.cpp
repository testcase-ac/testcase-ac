#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;

void solve() {
  int N, K; string S; cin >> N >> K >> S;

  int C[6] = {0};
  for (int i = 0; i < N / 2; ++i) {
    char c1 = S[i], c2 = S[N - i - 1];
    if (c1 > c2) swap(c1, c2);

    if (c1 == '2' && c2 == '2') ++C[0];
    if (c1 == '2' && c2 == '3') ++C[1];
    if (c1 == '3' && c2 == '3') ++C[2];
    if (c1 == '2' && c2 == 'E') ++C[3];
    if (c1 == '3' && c2 == 'E') ++C[4];
    if (c1 == 'E' && c2 == 'E') ++C[5];
  }

  for (int i = 0; i < 6; ++i) {
    // cout << "C[" << i << "] = " << C[i] << '\n';
  }

  cout << 2 * (C[0] + C[4]) << '\n';
  for (int i = 1; i <= K; ++i) {
    if (C[2] > 0 && C[5] > 0) {
      --C[2]; --C[5];
      C[4] += 2;
    }
    else if (C[1] > 0 && C[3] > 0) {
      --C[1]; --C[3];
      C[0] += 1; C[4] += 1;
    }
    else if (C[1] >= 2) {
      C[1] -= 2;
      C[0] += 1; C[2] += 1;
    }
    else if (C[3] >= 2) {
      C[3] -= 2;
      C[0] += 1; C[5] += 1;
    }
    else if (C[1] > 0 && C[5] > 0) {
      --C[1]; --C[5];
      C[3] += 1; C[4] += 1;
    }
    else if (C[2] > 0 && C[3] > 0) {
      --C[2]; --C[3];
      C[1] += 1; C[4] += 1;
    }
    cout << 2 * (C[0] + C[4]) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

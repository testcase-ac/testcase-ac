#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000, INF = 0x3f3f3f3f;
int X[MAX], Y[MAX];
int U[MAX + 1][MAX + 1];
int N, A, L;

void solve() {
  cin >> N >> A >> L;
  for (int i = 1; i <= N; i++) cin >> X[i] >> Y[i];

  memset(U, -1, sizeof(U));
  U[0][L] = A;
  for (int i = 1; i <= N; i++) {
    if (X[i] == -1) {
      for (int v = Y[i]; v <= L; v++) {
        U[i][v - Y[i]] = max(U[i][v - Y[i]], U[i - 1][v]);
      }
    }
    else if (Y[i] == -1) {
      for (int v = 0; v <= L; v++) {
        if (U[i - 1][v] == -1) continue;
        U[i][v] = max({U[i][v], U[i - 1][v] - X[i], 0});
      }
    }
    else {
      for (int v = Y[i]; v <= L; v++) {
        U[i][v - Y[i]] = max(U[i][v - Y[i]], U[i - 1][v]);
      }

      for (int v = 0; v <= L; v++) {
        if (U[i - 1][v] < X[i]) continue;
        U[i][v] = max(U[i][v], U[i - 1][v] - X[i]);
      }
    }
  }

  for (int v = 1; v <= L; v++) {
    if (U[N][v] == -1) continue;

    cout << "YES\n";
    string seq = "";

    // backtrack answer
    for (int i = N; i >= 1; i--) {
      if (X[i] == -1) {
        seq += 'L';
        v += Y[i];
      }
      else if (Y[i] == -1) {
        seq += 'A';
      }
      else {
        if (v + Y[i] <= L && U[i - 1][v + Y[i]] == U[i][v]) {
          seq += 'L';
          v += Y[i];
        }
        else {
          seq += 'A';
        }
      }
    }

    assert(v == L);
    reverse(seq.begin(), seq.end());
    cout << seq << '\n';

    return;
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

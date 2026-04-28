#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
const char C[5] = {'B', 'S', 'G', 'P', 'D'};
string A[MAX];

bool comp(string& a, string& b) {
  if (a[0] == b[0]) {
    int av = stoi(a.substr(1));
    int bv = stoi(b.substr(1));
    return av > bv;
  }
  else {
    int ai, bi;
    for (int i = 0; i < 5; ++i) {
      if (a[0] == C[i]) ai = i;
      if (b[0] == C[i]) bi = i;
    }
    return ai < bi;
  }
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 0; i < N; i++) for (int j = N - 1; j > i; j--) {
    if (!comp(A[i], A[j])) {
      cout << "KO\n";
      cout << A[j] << ' ' << A[i] << '\n';
      return;
    }
  }
  cout << "OK\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A; int zc = 0, oc = 0;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    if (x == 0) zc++;
    else if (x == 1) oc++;
    else A.push_back(x);
  }

  sort(A.begin(), A.end());
  int z = A.size();
  if (zc & 1) {
    zc--;
    if (oc) {
      oc--;
      if (z >= 2 && A[z - 2] == 2 && A[z - 1] == 3) swap(A[z - 2], A[z - 1]);
      for (int e : A) cout << e << '\n';
      while (zc--) cout << "0\n";
      cout << "1\n0\n";
      while (oc--) cout << "1\n";
    }
    else if (z) {
      if (z >= 3 && A[z - 2] == 2 && A[z - 1] == 3) swap(A[z - 2], A[z - 1]);
      for (int i = 1; i < z; i++) cout << A[i] << '\n';
      while (zc--) cout << "0\n";
      cout << A[0] << '\n';
      cout << "0\n";
    }
    else {
      while (zc--) cout << "0\n";
      cout << "0\n";
    }
  }
  else {
    if (z >= 2 && A[z - 2] == 2 && A[z - 1] == 3) swap(A[z - 2], A[z - 1]);
    for (int e : A) cout << e << '\n';
    while (zc--) cout << "0\n";
    while (oc--) cout << "1\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

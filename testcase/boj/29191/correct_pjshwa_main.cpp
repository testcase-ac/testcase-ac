#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN];

void print_vec(vector<int>& v) {
  cout << v.size() << '\n';
  for (int i : v) cout << i + 1 << ' ';
  cout << '\n';
}

void solve() {
  int N; cin >> N;

  int sgn = 1;
  vector<int> zi, pi;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    if (A[i] == 0) zi.push_back(i);
    else {
      pi.push_back(i);
      if (A[i] < 0) sgn *= -1;
    }
  }

  if (!zi.empty()) {
    if (zi.size() == N) return cout << "Impossible\n", void();
    else if (sgn == 1) print_vec(pi);
    else print_vec(zi);
    return;
  }

  for (int i = 0; i < N; ++i) {
    ll rval = 1, ok = 0, val = A[i], csgn = sgn * (A[i] < 0 ? -1 : 1);
    vector<int> pi, oi{i};
    for (int j = 0; j < N; ++j) if (i != j) pi.push_back(j);
    for (int j = 0; j < N; ++j) {
      if (i == j) continue;
      rval *= A[j];
      if (abs(rval) > abs(val)) {
        ok = 1;
        break;
      }
    }

    if (ok) {
      if (csgn == 1) return print_vec(pi);
      else return print_vec(oi);
    } else {
      if (rval > val) return print_vec(pi);
      if (rval < val) return print_vec(oi);
    }
  }

  cout << "Impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

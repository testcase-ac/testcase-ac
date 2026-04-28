#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_sorted(const vector<int>& v) {
  for (int i = 1; i < v.size(); ++i) {
    if (v[i] < v[i - 1]) return false;
  }
  return true;
}

string f(bool ok) {
  return ok ? "So Lucky" : "Unlucky";
}

void solve() {
  int N; cin >> N;

  vector<int> O, E, A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    if (A[i] & 1) O.push_back(A[i]);
    else E.push_back(A[i]);
  }
  cout << f(is_sorted(O) && is_sorted(E)) << '\n';

  vector<int> R;
  auto flush = [&](vector<int>& v) {
    if (v.empty()) return;
    sort(v.begin(), v.end());
    for (int x : v) R.push_back(x);
    v.clear();
  };

  O.clear(); E.clear();
  for (int i = 0; i < N; ++i) {
    if (A[i] & 1) {
      O.push_back(A[i]);
      flush(E);
    } else {
      E.push_back(A[i]);
      flush(O);
    }
  }
  flush(O); flush(E);
  cout << f(is_sorted(R)) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

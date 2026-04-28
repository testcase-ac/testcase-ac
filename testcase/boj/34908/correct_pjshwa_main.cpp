#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
ll A[MAXN + 1];

ll ask(int i, int j) {
  cout << "? " << i << ' ' << j << endl;
  ll res; cin >> res;
  return res;
}

void solve() {
  int N; cin >> N;

  ll a1 = ask(1, 2), a2 = ask(2, 3);
  A[2] = __gcd(a1, a2);
  A[1] = a1 / A[2], A[3] = a2 / A[2];

  int i = 4;
  while (i <= N) {
    int d = N - i + 1;
    if (d == 1) {
      ll a = ask(1, i);
      A[i] = a / A[1];
      i += 1;
    } else if (d == 2) {
      ll a1 = ask(1, i), a2 = ask(1, i + 1);
      A[i] = a1 / A[1], A[i + 1] = a2 / A[1];
      i += 2;
    } else {
      ll a1 = ask(i, i + 1), a2 = ask(i + 1, i + 2);
      A[i + 1] = __gcd(a1, a2);
      A[i] = a1 / A[i + 1], A[i + 2] = a2 / A[i + 1];
      i += 3;
    }
  }

  cout << "! ";
  for (int i = 1; i <= N; i++) cout << A[i] << ' ';
  cout << endl;
}

int main() {
  // fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    A[i] %= 2;
  }

  ll zc = 0, oc = 0, cur1 = 0, cur2 = 0;
  for (int i = 0; i < N; i++) {
    if (A[i]) oc++;
    else cur1 += oc;
  }
  for (int i = 0; i < N; i++) {
    if (A[i]) cur2 += zc;
    else zc++;
  }

  cout << min(cur1, cur2) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

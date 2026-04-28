#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  int A, B, C, D;
  cin >> A >> B >> C >> D;

  int p1c = 0, p2c = 0, pzc = 0;
  for (int p : pr) {
    if (A <= p && p <= B) {
      if (C <= p && p <= D) pzc++;
      else p1c++;
    }
    else if (C <= p && p <= D) p2c++;
  }

  if (pzc & 1) {
    if (p2c <= p1c) cout << "yt\n";
    else cout << "yj\n";
  }
  else {
    if (p1c > p2c) cout << "yt\n";
    else cout << "yj\n";
  }
}

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

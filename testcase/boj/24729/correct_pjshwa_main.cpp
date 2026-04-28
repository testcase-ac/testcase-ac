#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX], t[MAX + 1];

void solve() {
  int n;
  cin >> n;

  vector<int> vs;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    t[a[i]]++;
    vs.push_back(a[i]);
  }

  compress(vs);
  for (int i = 0; i < vs.size() - 1; i++) {
    if (vs[i + 1] - vs[i] > 1) return cout << "-1\n", void();
  }

  for (int i = vs.size() - 1; i >= 0; i--) {
    int v = vs[i];
    // cout << "v: " << v << ", t[v]: " << t[v] << '\n';
    if (t[v] <= 0) {
      if (t[v] == 0 && i == 0) return cout << "1\n", void();
      else return cout << "-1\n", void();
    }
    else if (i == 0) return cout << "-1\n", void();
    else t[vs[i - 1]] -= t[v];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

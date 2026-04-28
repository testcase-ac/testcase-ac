#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<pii> ss(N), es(N);
  for (int i = 0; i < N; i++) {
    int li, ri;
    cin >> li >> ri;
    ss[i] = {li, ri};
    es[i] = {ri, -li};
  }
  sort(ss.begin(), ss.end());
  sort(es.begin(), es.end());

  int Q;
  cin >> Q;
  while (Q--) {
    int li, ri;
    cin >> li >> ri;

    if (binary_search(ss.begin(), ss.end(), pii(li, ri))) cout << 1;
    else {
      if (
        lower_bound(ss.begin(), ss.end(), pii(li, ri))->first == li &&
        lower_bound(es.begin(), es.end(), pii(ri, -li))->first == ri
      ) cout << 2;
      else cout << -1;
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

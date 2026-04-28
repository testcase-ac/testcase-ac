#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N;

void solve() {
  map<string, pii> products;
  for (int i = 0; i < N; ++i) {
    string name; int price, wait; cin >> name >> price >> wait;
    products[name] = {price, wait};
  }

  int C, cnt = 0; cin >> C;
  while (C--) {
    int Ci, P, M, err = 0; cin >> Ci >> P >> M;
    cout << Ci << ' ';

    int total = 0;
    while (P--) {
      string item; cin >> item;
      auto [price, wait] = products[item];
      if (wait <= M) total += price;
      else err = 1;
    }

    cout << total;
    if (err) cout << " *";
    cout << '\n';
    cnt += err;
  }

  cout << "Number of discontented customers is: " << cnt << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}

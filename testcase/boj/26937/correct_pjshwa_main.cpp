#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> books[M]; int postage[M];
  for (int i = 0; i < M; ++i) {
    int K; cin >> K >> postage[i];
    for (int j = 0; j < K; ++j) {
      int a, b; cin >> a >> b;
      books[i].emplace_back(a, b);
    }
  }

  int ans = INF;
  for (int state = 0; state < (1 << M); ++state) {
    map<int, int> by_book;

    int cost = 0;
    for (int i = 0; i < M; ++i) {
      if (!(state & (1 << i))) continue;

      cost += postage[i];
      for (auto [book, price] : books[i]) {
        if (by_book.count(book)) by_book[book] = min(by_book[book], price);
        else by_book[book] = price;
      }
    }

    if (by_book.size() != N) continue;
    for (auto [_, price] : by_book) cost += price;
    ans = min(ans, cost);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, ans = 0; string S; cin >> N >> S;

  string T = "";
  for (char& c : S) {
    T.push_back(c);
    if (c != 'p') continue;
    while (T.size() >= 5 && T.substr(T.size() - 5) == "skeep") {
      T.resize(T.size() - 5);
      if (T.empty() || T.back() == 's') T.push_back('k');
      else if (T.back() == 'k') T.push_back('e');
      else if (T.back() == 'e' && T.size() >= 2 && T[T.size() - 2] != 'e') {
        T.push_back('e');
      }
      else T.push_back('p');
      ++ans;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

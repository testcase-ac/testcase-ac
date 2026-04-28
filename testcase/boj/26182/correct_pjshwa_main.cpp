#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int c, d; cin >> c >> d;
  vector<int> fizzes, buzzes;
  for (int i = c; i <= d; i++) {
    string s; cin >> s;
    if (s == "Fizz") fizzes.push_back(i);
    else if (s == "Buzz") buzzes.push_back(i);
    else if (s == "FizzBuzz") {
      fizzes.push_back(i);
      buzzes.push_back(i);
    }
  }

  if (fizzes.size() == 0) cout << d + 1;
  else if (fizzes.size() == 1) cout << fizzes[0];
  else cout << fizzes[1] - fizzes[0];

  cout << ' ';

  if (buzzes.size() == 0) cout << d + 1;
  else if (buzzes.size() == 1) cout << buzzes[0];
  else cout << buzzes[1] - buzzes[0];

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

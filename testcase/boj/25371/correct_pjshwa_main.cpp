#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

void solve() {
  int n, k;
  cin >> n >> k;
  
  stack<ll> s;
  while (n) {
    s.push(n % k);
    n /= k;
  }

  string bs = "";
  while (!s.empty()) {
    bs += '0' + s.top();
    s.pop();
  }

  ll ans = 0;
  for (auto token : split(bs, "0")) {
    if (!token.empty()) ans += stoll(token);
  }

  while (ans) {
    s.push(ans % k);
    ans /= k;
  }
  while (!s.empty()) {
    cout << s.top();
    s.pop();
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

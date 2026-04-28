#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

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
  int N; string td;
  cin >> N >> td;
  auto tokens = split(td, ".");
  if (tokens.size() == 1) tokens.push_back("0");
  while (tokens[1].size() < 4) tokens[1] += '0';
  __int128_t T = stoll(tokens[0]) * 1e4 + stoll(tokens[1]);

  vector<pll> v(N);
  for (int i = 0; i < N; i++) cin >> v[i].first, v[i].first *= 1e4;
  for (int i = 0; i < N; i++) cin >> v[i].second;
  sort(v.begin(), v.end());

  __int128_t s = v[0].first - T * v[0].second, e = v[0].first + T * v[0].second;
  for (int i = 1; i < N; i++) {
    auto [xi, vi] = v[i];
    __int128_t ns = xi - T * vi, ne = xi + T * vi;
    s = max(s, ns), e = min(e, ne);
  }

  if (s <= e) cout << "1\n";
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

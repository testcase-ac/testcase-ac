#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
map<string, int> fi;
int fcount;
int par[MAX + 1];

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
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
  int N;
  cin >> N;

  memset(par, -1, sizeof(par));
  for (int i = 0; i < N - 1; i++) {
    string S, T;
    cin >> S >> T;
    int si = fidx(S), ti = fidx(T);
    par[si] = ti;
  }

  string S, T;
  cin >> S >> T;
  int si = fidx(S), ti = fidx(T), s, t;

  s = si, t = ti;
  while (1) {
    if (s == t) return cout << "1\n", void();
    s = par[s];
    if (s == -1) break;
  }

  s = si, t = ti;
  while (1) {
    if (s == t) return cout << "1\n", void();
    t = par[t];
    if (t == -1) break;
  }

  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

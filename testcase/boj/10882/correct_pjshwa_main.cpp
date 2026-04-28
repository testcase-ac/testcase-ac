#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1440;

struct Time {
  int m;
  Time(int m) : m(m) {}
  Time add_time(int t) {
    return Time((m + t + MOD) % MOD);
  }
  string to_str() {
    string hs = to_string(m / 60);
    string ms = to_string(m % 60);
    if (hs.size() == 1) hs = "0" + hs;
    if (ms.size() == 1) ms = "0" + ms;
    return hs + ":" + ms;
  }
};

Time parse_time(string s) {
  int h = stoi(s.substr(0, 2));
  int m = stoi(s.substr(3, 2));
  return Time(h * 60 + m);
}

int parse_utc(string s) {
  int sign = s[3] == '-' ? -1 : 1;
  double num = stod(s.substr(4));
  return sign * (int)(num * 60);
}

void solve() {
  int N; cin >> N;
  string ts, zs; cin >> ts >> zs;
  Time t = parse_time(ts); int base = parse_utc(zs);

  for (int i = 0; i < N; ++i) {
    string s; cin >> s;
    int tz = parse_utc(s);
    int diff = tz - base;
    cout << t.add_time(diff).to_str() << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

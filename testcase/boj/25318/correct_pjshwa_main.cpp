#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

const int MAX = 1000;
const int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int L[MAX + 1], T[MAX + 1];
double P[MAX + 1];

int ts2ep(string dstr, string tstr) {
  vector<string> ds = split(dstr, "/");
  vector<string> ts = split(tstr, ":");
  int y = stoi(ds[0]), m = stoi(ds[1]), d = stoi(ds[2]);
  int hh = stoi(ts[0]), mm = stoi(ts[1]), ss = stoi(ts[2]);

  int dd = 0, cy = 2019, cm = 1;
  while (!(cy == y && cm == m)) {
    dd += months[cm];
    if (cm == 2 && (cy % 4 == 0 && (cy % 100 != 0 || cy % 400 == 0))) dd++;
    cm++;
    if (cm > 12) {
      cm = 1;
      cy++;
    }
  }
  dd += (d - 1);

  return dd * 86400 + hh * 3600 + mm * 60 + ss;
}

void solve() {
  int N;
  cin >> N;
  if (N == 0) return cout << "0\n", void();

  for (int i = 1; i <= N; i++) {
    string dstr, tstr; int li;
    cin >> dstr >> tstr >> li;
    L[i] = li;
    T[i] = ts2ep(dstr, tstr);
  }

  for (int i = 1; i <= N; i++) {
    double pp = pow(0.9, N - i);
    double py = pow(0.5, (T[N] - T[i]) / (365.0 * 86400));
    P[i] = max(pp, py);
  }

  double ans = 0, div = 0;
  for (int i = 1; i <= N; i++) ans += P[i] * L[i], div += P[i];
  cout << round(ans / div) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

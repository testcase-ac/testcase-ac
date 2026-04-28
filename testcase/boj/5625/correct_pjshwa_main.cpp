#include <bits/stdc++.h>
using namespace std;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, INF = 1e9 + 7;
int dtx[MAX + 10], dty[MAX + 10];

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

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    int minx = min({x1, x2, x3}), maxx = max({x1, x2, x3});
    int miny = min({y1, y2, y3}), maxy = max({y1, y2, y3});
    dtx[minx + 1]++; dtx[maxx]--;
    dty[miny + 1]++; dty[maxy]--;
  }
  for (int i = 1; i <= MAX; i++) dtx[i] += dtx[i - 1], dty[i] += dty[i - 1];

  int q;
  cin >> q;
  cin.ignore();
  while (q--) {
    string u;
    getline(cin, u);

    auto uq = split(u, " = ");
    int c = stoi(uq[1]);
    if (uq[0] == "x") cout << dtx[c] << '\n';
    else cout << dty[c] << '\n';
  }
}

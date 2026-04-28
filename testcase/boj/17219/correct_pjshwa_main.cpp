#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;
  string url, pw;
  map<string, string> p;
  while (n--) {
    cin >> url >> pw;
    p[url] = pw;
  }
  while (q--) {
    cin >> url;
    cout << p[url] << '\n';
  }
}

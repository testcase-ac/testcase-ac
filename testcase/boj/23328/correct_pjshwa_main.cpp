#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  string d, l;
  cin >> n >> d >> l;

  char tbig = d[0], tsmall = d[0] + 32;

  vector<char> rest;
  int bc = 0, sc = 0;
  bool precede = false;
  for (char c : l) {
    if (c == tbig) bc++;
    else if (c == tsmall) sc++;
    else rest.push_back(c);

    if (c < tbig) precede = true;
  }

  if (precede) {
    if (sc >= 2) {
      for (int i = 0; i < sc; i++) rest.push_back(tsmall);
      sort(rest.begin(), rest.end());

      int ss;
      for (int i = rest.size() - 1; i >= 0; i--) {
        if (rest[i] == tsmall) ss = i;
      }

      bool done = false;
      for (char c : rest) {
        cout << c;
        if (!done && c == tsmall) {
          for (int i = 0; i < bc; i++) cout << tbig;
          done = true;
        }
      }
    }
    else {
      sort(rest.begin(), rest.end());
      for (char c : rest) cout << c;
      for (int i = 0; i < sc; i++) cout << tsmall;
      for (int i = 0; i < bc; i++) cout << tbig;
    }
  }
  else {
    for (int i = 0; i < max(0, sc - 1); i++) rest.push_back(tsmall);
    sort(rest.begin(), rest.end());

    for (int i = 0; i < bc; i++) cout << tbig;
    for (int i = 0; i < min(1, sc); i++) cout << tsmall;
    for (char c : rest) cout << c;
  }
  cout << '\n';
}

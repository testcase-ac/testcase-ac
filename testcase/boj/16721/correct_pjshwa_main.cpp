#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool rels[5000];
int main() {
  fast_io();

  int n, m, b, c;
  string op;
  cin >> n;

  cin >> op;
  for (int i = 1; i < n; i++) {
    cin >> op;
    rels[i] = (op == "-" ? false : true);
  }
  for (int i = 0; i < n * n - n; i++) cin >> op;

  cin >> m;
  bool friends;
  while (m--) {
    cin >> b >> c;
    if (b == 0) friends = rels[c];
    else if (c == 0) friends = rels[b];
    else friends = rels[b] == rels[c];
    cout << (friends ? '+' : '-') << '\n';
  }
}

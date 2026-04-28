#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;

const int MAX = 2e5, INF = 1e9 + 7;
int d[MAX + 5];

int rec(int i) {
  if (i == 0) return s[0] == '+' ? 10 : 1;
  if (i == 1) return s[0] == '+' && s[1] == '-' ? 11 : -INF;
  if (i == 2) {
    if (s[0] == '+') {
      if (s[1] == '+' && s[2] == '+') return 20;
      if (s[1] == '+' && s[2] == '-') return 11;
      if (s[1] == '-' && s[2] == '+') return 0;
      if (s[1] == '-' && s[2] == '-') return 9;
    }
    else {
      if (s[1] == '+' && s[2] == '+') return 11;
      if (s[1] == '+' && s[2] == '-') return 2;
      if (s[1] == '-' && s[2] == '+') return -9;
      if (s[1] == '-' && s[2] == '-') return 0;
    }
  }
  if (d[i] != -1) return d[i];
  
  int ret;
  if (s[i - 1] == '+') {
    if (s[i] == '+') ret = rec(i - 2) + 10;
    else {
      if (s[i - 2] == '-') ret = rec(i - 3) - 11;
      else ret = rec(i - 3) + 11;
      ret = max(ret, rec(i - 2) + 1);
    }
  }
  else {
    if (s[i] == '+') ret = rec(i - 2) - 10;
    else ret = rec(i - 2) - 1;
  }
  return d[i] = ret;
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  cin >> s;
  cout << rec(s.size() - 1) << '\n';
}

#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int pi[MAX + 1];
int main() {
  fast_io();

  int n, j = 0;
  string s;
  cin >> n >> s;

  for (int i = 1; i < n; i++) {
    while (s[i] != s[j] && j > 0) j = pi[j - 1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  cout << n - pi[n - 1];
}

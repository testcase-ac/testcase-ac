#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int pi[MAX + 1];
int main() {
  fast_io();

  while (1) {
    int j = 0;
    string s;
    cin >> s;
    if (s == ".") break;

    int n = s.size();
    memset(pi, 0, sizeof(pi));

    for (int i = 1; i < n; i++) {
      while (s[i] != s[j] && j > 0) j = pi[j - 1];
      if (s[i] == s[j]) pi[i] = ++j;
    }
    int a = n - pi[n - 1];
    cout << (n % a ? 1 : n / a) << '\n';
  }
}

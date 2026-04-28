#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool isPrime(int n) {
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

int LL, LR;
vector<int> ans;

void dfs(string s) {
  if (s.size() > 9) return;
  if (s.size() && s[0] != '0') {
    int i = stoi(s);
    if (isPrime(i) && LL <= i && i <= LR) ans.push_back(i);
  }

  for (int c = '0'; c <= '9'; c++) {
    string m(1, c);
    dfs(m + s + m);
  }
}

int main() {
  fast_io();

  cin >> LL >> LR;
  dfs("");
  for (int i = 0; i < 10; i++) dfs(to_string(i));
  sort(ans.begin(), ans.end());
  for (int e : ans) cout << e << '\n';
  cout << -1;
}

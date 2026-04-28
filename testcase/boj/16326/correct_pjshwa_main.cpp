#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_palindrome(string s) {
  for (int i = 0; i < s.size() / 2; i++) {
    if (s[i] != s[s.size() - 1 - i]) return false;
  }
  return true;
}

vector<char> current;
int zcnt, cnt;
ll n;

void dfs() {
  if (to_string(n).size() < current.size() * 2) return;

  string ca;
  int sz = current.size();
  for (int i = 0; i < sz; i++) ca += current[i];
  for (int i = sz - 1; i >= 0; i--) ca += current[i];
  if (ca.size()) {
    ll nca = stoll(ca);
    ll sd = n - nca;
    if (is_palindrome(to_string(sd))) sd == nca ? zcnt++ : cnt++;
  }
  for (int i = 0; i < sz; i++) ca.pop_back();
  for (int k = 0; k < 10; k++) {
    if (k == 0 && sz == 0) continue;
    ca += (k + '0');
    for (int i = sz - 1; i >= 0; i--) ca += current[i];
    ll nca = stoll(ca);
    ll sd = n - nca;
    if (is_palindrome(to_string(sd))) sd == nca ? zcnt++ : cnt++;
    for (int i = 0; i <= sz; i++) ca.pop_back();
  }

  for (int c = '0'; c <= '9'; c++) {
    if (c == '0' && sz == 0) continue;
    current.push_back(c);
    dfs();
    current.pop_back();
  }
}

int main() {
  fast_io();

  cin >> n;
  dfs();
  cout << cnt + (zcnt / 2) << '\n';
}

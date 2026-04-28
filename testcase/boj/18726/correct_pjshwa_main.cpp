#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_palindrome(string s) {
  int n = s.size();
  for (int i = 0; i < n / 2; i++) {
    if (s[i] != s[n - i - 1]) return false;
  }
  return true;
}

// Requires t.size() >= o.size();
string sub(string t, string o) {
  int sz = t.size(), diff = sz - o.size();
  
  string res = "";
  bool carry = false;
  for (int i = sz - 1; i >= 0; i--) {
    int scur = t[i] - '0';
    int ocur = i >= diff ? o[i - diff] - '0' : 0;
    if (carry) ocur++;
    carry = false;

    if (scur >= ocur) res.push_back(scur - ocur + '0');
    else {
      res.push_back(scur - ocur + 10 + '0');
      carry = true;
    }
  }
  while (res.back() == '0') res.pop_back();
  reverse(res.begin(), res.end());

  return res;
}

vector<string> ans;
string s;

void r(string s) {
  if (is_palindrome(s)) {
    ans.push_back(s);
    return;
  }

  int sz = s.size(), a = 0;
  for (int i = 0; i < sz; i++) a += s[i] - '0';
  if (s[0] == '1' && a == 1) {
    string t = "";
    for (int i = 0; i < sz - 1; i++) t += '9';
    ans.push_back(t);
    ans.push_back("1");
    return;
  }

  string f = s.substr(0, sz / 2);
  string fr = f;
  reverse(fr.begin(), fr.end());
  
  string c;
  if (sz & 1) c = f + "0" + fr;
  else c = f + fr;

  for (int i = 0; i < sz; i++) {
    if (s[i] == c[i]) continue;
    if (s[i] > c[i]) break;

    f = sub(f, "1");
    fr = f;
    reverse(fr.begin(), fr.end());

    if (sz & 1) c = f + "0" + fr;
    else c = f + fr;

    break;
  }

  ans.push_back(c);
  r(sub(s, c));
}

void solve() {
  ans.clear();
  string s;
  cin >> s;
  r(s);

  cout << ans.size() << '\n';
  for (auto a : ans) cout << a << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}

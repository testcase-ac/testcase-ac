#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int pw10[10];

int r(string s) {
  int n = s.size();

  string pre = s.substr(0, n / 2), suf = s.substr((n + 1) / 2);
  reverse(pre.begin(), pre.end());

  assert(pre.size() == suf.size());

  int ans = stoi(pre) - stoi(suf);
  if (ans < 0) {
    int diff = pw10[n / 2] - stoi(suf);
    string diff_s = to_string(diff);
    int diff_z = diff_s.size();

    int carry = 0;
    for (int i = 0; i < s.size(); i++) {
      int c = i < diff_s.size() ? diff_s[diff_z - i - 1] - '0' : 0;
      int p = s[n - i - 1] - '0';

      int r = p + c + carry;
      if (r >= 10) {
        r -= 10;
        carry = 1;
      }
      else carry = 0;

      s[n - i - 1] = r + '0';
    }

    return r(s) + diff;
  }
  else return ans;
}

int main() {
  fast_io();

  pw10[0] = 1;
  for (int i = 1; i < 10; i++) pw10[i] = pw10[i - 1] * 10;

  while (1) {
    string s;
    cin >> s;
    if (s == "0") break;
    cout << r(s) << '\n';
  }
}

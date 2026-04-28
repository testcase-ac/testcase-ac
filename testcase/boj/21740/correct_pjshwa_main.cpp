#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool greater_concat(string s1, string s2) {
  if (s1 + s2 == s2 + s1) return s1.size() > s2.size();
  else return s1 + s2 > s2 + s1;
}

string flip_string(string s) {
  int sz = s.size();
  string ns = "";
  for (int i = sz - 1; i >= 0; i--) {
    if (s[i] == '9') ns += '6';
    else if (s[i] == '6') ns += '9';
    else ns += s[i];
  }
  return ns;
}

string nums_s[100000];
int main() {
  fast_io();

  int n;
  string s;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> s;
    nums_s[i] = flip_string(s);
  }
  sort(nums_s, nums_s + n, greater_concat);

  string max_str = nums_s[0];
  for (int i = 1; i < n; i++) {
    if (max_str.size() < nums_s[i].size() || greater_concat(nums_s[i], max_str)) max_str = nums_s[i];
  }

  string ans = "";
  bool reps_out = false;
  for (int i = 0; i < n; i++) {
    ans += nums_s[i];
    if (!reps_out && nums_s[i] == max_str) {
      ans += max_str;
      reps_out = true;
    }
  }
  cout << flip_string(ans) << '\n';
}

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

string nums_s[1000];
int main() {
  fast_io();

  int n, k;
  cin >> k >> n;

  for (int i = 0; i < k; i++) cin >> nums_s[i];
  sort(nums_s, nums_s + k, greater_concat);

  string max_str = nums_s[0];
  for (int i = 1; i < k; i++) {
    if (max_str.size() < nums_s[i].size() || greater_concat(nums_s[i], max_str)) max_str = nums_s[i];
  }

  bool reps_out = false;
  for (int i = 0; i < k; i++) {
    cout << nums_s[i];
    if (!reps_out && nums_s[i] == max_str) {
      for (int i = 0; i < n - k; i++) cout << max_str;
      reps_out = true;
    }
  }
  cout << '\n';
}

#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool less_concat(string& s1, string& s2) {
  if (s1 + s2 == s2 + s1) return s1.size() < s2.size();
  else return s1 + s2 < s2 + s1;
}

string nums_s[100];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> nums_s[i];
  sort(nums_s, nums_s + n, less_concat);

  int nonzero_idx = 0;
  string zero_segment = "";
  while (nonzero_idx < n && nums_s[nonzero_idx][0] == '0') {
    zero_segment += nums_s[nonzero_idx];
    nonzero_idx++;
  }
  if (nonzero_idx == n) {
    cout << "INVALID\n";
    return 0;
  }

  int nonzero_s_idx = min_element(
    nums_s + nonzero_idx,
    nums_s + n,
    [&](string& s1, string& s2){ return s1 + zero_segment + s2 < s2 + zero_segment + s1; }
  ) - nums_s;

  cout << nums_s[nonzero_s_idx];
  for (int i = 0; i < n; i++) {
    if (i != nonzero_s_idx) cout << nums_s[i];
  }
  cout << '\n';
}

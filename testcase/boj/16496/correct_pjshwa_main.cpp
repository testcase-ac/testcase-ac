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

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> nums_s[i];
  sort(nums_s, nums_s + n, greater_concat);

  if (nums_s[0] == "0") {
    cout << "0\n";
    return 0;
  }

  for (int i = 0; i < n; i++) cout << nums_s[i];
  cout << '\n';
}

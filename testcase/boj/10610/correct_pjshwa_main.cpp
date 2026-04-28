#include <bits/stdc++.h>
using namespace std;

char s[100005];
int main() {
  cin >> s;
  int n = strlen(s), sum = 0;
  sort(s, s + n, greater<char>());
  bool able = false;
  for (int i = 0; i < n; ++i) able |= s[i] == '0', sum += s[i] - '0';
  if (able && sum % 3 == 0) cout << s;
  else cout << -1;
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  for (int i = 0; i < n; i++) if (s[i] == '6') s[i] = '9';

  ll ans = 0;
  int stack[20];

  int stack_pointer;
  bool finished;

  // combinations
  for (int i = 1; i <= (n + 1) / 2; i++) {
    stack_pointer = -1;
    stack[0] = 0;

    finished = false;
    while (!finished) {

      for (stack_pointer++; stack_pointer < i - 1; stack_pointer++) {
        stack[stack_pointer + 1] = stack[stack_pointer] + 1;
      }

      // stack[0]..stack[i - 1] contains the indexes
      // do work here
      int sp = 0;
      priority_queue<char> q1, q2;
      for (int j = 0; j < n; j++) {
        if (sp < i && j == stack[sp]) q1.push(s[j]), sp++;
        else q2.push(s[j]);
      }

      string s1 = "", s2 = "";
      while (!q1.empty()) s1 += q1.top(), q1.pop();
      while (!q2.empty()) s2 += q2.top(), q2.pop();
      ans = max(ans, stoll(s1) * stoll(s2));
      // do work here

      do {
        if (stack_pointer == -1) {
          finished = true;
          break;
        }
        stack[stack_pointer--]++;
      } while (stack[stack_pointer + 1] + i == n + stack_pointer + 2);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();

}

#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int pairs[4000];
bool anc[4000];
int main() {
  fast_io();

  int n, x, y;
  string s;
  cin >> n >> s >> x >> y;
  x--;
  y--;

  stack<int> st1, st2;
  for (int i = 0; i < 2 * n; i++) {
    if (s[i] == '0') st1.push(i);
    else {
      pairs[st1.top()] = i;
      pairs[i] = st1.top();
      st1.pop();
    }
  }
  int xs = min(x, pairs[x]), ys = min(y, pairs[y]);
  if (xs > ys) swap(xs, ys);

  if (pairs[xs] > pairs[ys]) cout << xs + 1 << ' ' << pairs[xs] + 1;
  else {
    for (int i = 0; i < 2 * n; i++) {
      if (s[i] == '0') st1.push(i);
      else {
        if (i == pairs[xs]) {
          while (!st1.empty()) {
            anc[st1.top()] = true;
            st2.push(st1.top());
            st1.pop();
          }
          while (!st2.empty()) {
            st1.push(st2.top());
            st2.pop();
          }
        }
        if (i == pairs[ys]) {
          while (!st1.empty()) {
            if (anc[st1.top()]) {
              int a = st1.top();
              cout << a + 1 << ' ' << pairs[a] + 1;
              break;
            }
            st1.pop();
          }
          break;
        }
        st1.pop();
      }
    }

  }

}

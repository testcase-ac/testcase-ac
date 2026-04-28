#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int h[(size_t)1e5];
ll s[(size_t)1e5];
int l[(size_t)1e5];
int r[(size_t)1e5];
int main() {
  fast_io();

  int n;
  ll l_ps, r_ps; // prefix sums
  ll max_v;
  stack<int> stk;

  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> h[i];
    l[i] = -1;
    r[i] = n;
  }

  s[0] = h[0];
  for (int i = 1; i < n; i++) {
    s[i] = s[i - 1] + h[i];
  }

  for (int i = 0; i < n; i++) {
    while (!stk.empty() && h[stk.top()] >= h[i]) stk.pop();
    if (!stk.empty()) l[i] = stk.top();
    stk.push(i);
  }
  while (!stk.empty()) stk.pop();

  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && h[stk.top()] >= h[i]) stk.pop();
    if (!stk.empty()) r[i] = stk.top();
    stk.push(i);
  }
  while (!stk.empty()) stk.pop();

  max_v = 0;
  for (int i = 0; i < n; i++) {
    r_ps = s[r[i] - 1];
    l_ps = (l[i] == -1) ? 0 : s[l[i]];
    max_v = max(max_v, (r_ps - l_ps) * h[i]);
  }
  cout << max_v << '\n';
}

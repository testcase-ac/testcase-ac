#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int h[(size_t)1e5];
int l[(size_t)1e5];
int r[(size_t)1e5];
int main() {
  fast_io();

  int n;
  ll max_v;
  stack<int> stk;
  while (1) {
    cin >> n;
    if (n == 0) break;

    for (int i = 0; i < n; i++) {
      cin >> h[i];
      l[i] = -1;
      r[i] = n;
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
      max_v = max(max_v, (ll)h[i] * (r[i] - l[i] - 1));
    }
    cout << max_v << '\n';
  }
}

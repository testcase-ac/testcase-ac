#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[(size_t)5e5];
int ret[(size_t)5e5];
int main() {
  fast_io();

  int n;
  cin >> n;
  stack<int> stk;

  memset(ret, 0, sizeof(ret));

  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() && a[stk.top()] < a[i]) {
      ret[stk.top()] = i + 1;
      stk.pop();
    }
    stk.push(i);
  }

  for (int i = 0; i < n; i++) cout << ret[i] << ' ';
  cout << '\n';
}

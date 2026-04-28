#include <bits/stdc++.h>
#define ll long long
using namespace std;

stack<int> ppl_stack;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n;

  ll res = 0;
  for (int i = 0; i < n; i++) {
    cin >> k;
    
    while (!ppl_stack.empty() && ppl_stack.top() <= k) {
      res += ppl_stack.size() - 1;
      ppl_stack.pop();
    }

    ppl_stack.push(k);
  }

  res += (ppl_stack.size() * (ppl_stack.size() - 1) / 2);
  cout << res << '\n';
}

#include <bits/stdc++.h>
#define pii pair<int, int>
#define ll long long
using namespace std;

stack<pii> ppl_stack;

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
    
    pii p(k, 1);
    while (!ppl_stack.empty() && ppl_stack.top().first <= k) {
      res += ppl_stack.top().second;
      if (ppl_stack.top().first == k) p.second += ppl_stack.top().second;

      ppl_stack.pop();
    }

    if (!ppl_stack.empty()) res++;
    ppl_stack.push(p);
  }

  cout << res << '\n';
}

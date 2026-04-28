#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k, mi, vi, ci;
  cin >> n >> k;

  priority_queue<pii> pqj;
  multiset<int> msb;

  for (int i = 0; i < n; i++) {
    cin >> mi >> vi;
    pqj.push({vi, mi});
  }

  for (int i = 0; i < k; i++) {
    cin >> ci;
    msb.insert(ci);
  }

  long long vsum = 0;
  while (!pqj.empty()) {
    tie(vi, mi) = pqj.top();
    pqj.pop();

    auto iter = msb.lower_bound(mi);
    if (iter == msb.end()) continue;

    msb.erase(iter);
    vsum += vi;
  }

  cout << vsum << '\n';
}

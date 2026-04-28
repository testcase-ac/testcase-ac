#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = (1 << 31) - 1;
int O[100];
int main() {
  fast_io();

  int k, n, p, nxt;
  cin >> k >> n;

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < k; i++) {
    cin >> O[i];
    pq.push(O[i]);
  }

  int cnt = 0;
  while (1) {
    nxt = pq.top();
    pq.pop();

    for (int i = 0; i < k; i++) {
      if (MAX / O[i] < nxt) continue;

      pq.push(O[i] * nxt);
      if (nxt % O[i] == 0) break;
    }

    if (++cnt == n) {
      cout << nxt;
      break;
    }
  }
}

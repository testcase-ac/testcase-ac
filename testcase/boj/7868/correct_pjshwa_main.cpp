#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const ll MAX = (1LL << 63) - 1;
int O[3];
int main() {
  fast_io();

  ll n, p, nxt;

  priority_queue<ll, vector<ll>, greater<ll>> pq;
  for (int i = 0; i < 3; i++) {
    cin >> O[i];
    pq.push(O[i]);
  }
  cin >> n;

  ll cnt = 0;
  while (1) {
    nxt = pq.top();
    pq.pop();

    for (int i = 0; i < 3; i++) {
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

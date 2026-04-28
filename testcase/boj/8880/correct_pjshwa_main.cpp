#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll INF = LLONG_MAX;
ll n, k;
int tcnt;
__int128_t x, u;
int primes[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};
int pcount[20];

void dfs(int i) {
  if (x > n) return;
  else if (x == n) {
    k = min(k, (ll)u);
    return;
  }

  if (u * primes[i] <= INF) {
    if (i == 0 || pcount[i - 1] > pcount[i]) {

      pcount[i]++;
      u *= primes[i];
      tcnt++;
      x *= tcnt;
      x /= pcount[i];

      dfs(i);

      x *= pcount[i];
      x /= tcnt;
      tcnt--;
      u /= primes[i];
      pcount[i]--;

    }

  }
  
  if (i < 19 && u * primes[i + 1] <= INF) {

    pcount[i + 1]++;
    u *= primes[i + 1];
    tcnt++;
    x *= tcnt;
    x /= pcount[i + 1];

    dfs(i + 1);

    x *= pcount[i + 1];
    x /= tcnt;
    tcnt--;
    u /= primes[i + 1];
    pcount[i + 1]--;

  }
}

void solve() {
  cout << n << ' ';
  
  memset(pcount, 0, sizeof(pcount));
  x = 1;
  u = primes[0];
  pcount[0] = tcnt = 1;
  k = INF;
  dfs(0);
  cout << k << '\n';
}

int main() {
  fast_io();

  while (cin >> n) solve();
}

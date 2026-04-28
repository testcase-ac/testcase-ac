#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll MAX = 1e6;
ll lp[MAX + 1], O[MAX + 1], P[MAX + 1];
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll newphi(int a, int b) {
  return P[b] - P[a - 1] - (b - a + 1);
}

int main(){
  fast_io();

  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      O[i] = 1;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++) {
      lp[i * pr[j]] = pr[j];
      O[i * pr[j]] = O[i] + 1;
    }
  }

  int s;
  for (ll i = 2; i <= MAX; ++i) {
    if (O[i] == 1) s = -1;
    else s = O[i];
    P[i] = P[i - 1] + s;
  }

  int L, U, maxL, iter = 0;
  while (1) {
    cin >> L >> U;
    if (L == -1 && U == -1) break;

    maxL = L;
    ll mv = newphi(L, U);
    for (int i = L; i <= U; i++) {
      if (newphi(i, U) > mv) {
        maxL = i;
        mv = newphi(i, U);
      }
    }

    for (int i = U; i >= maxL; i--) {
      if (newphi(maxL, i) > mv) mv = newphi(maxL, i);
    }

    cout << ++iter << ". " << mv << '\n';
  }
}

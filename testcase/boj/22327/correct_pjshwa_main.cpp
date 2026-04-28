/*
   Sample solution using alice library.
   This solution is incorrect.
   It is provided only to demonstrate the library usage.
   */

#include "alice.h"
#include <vector>
#define ll long long
using namespace std;

const ll MAX = 1e6;
ll lp[MAX + 1];
vector<int> pr;

void init() {
  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }
}

ll k, m, n;

void solve() {
  init();
	n = get_n();
	k = 1;
  bool stop = false;
  for (int prime : pr) {
    ll cp = prime;
    while (k * cp <= n && is_divisible_by(cp)) cp *= prime;
    k *= (cp / prime);
  }
	guess(k);
	return;
}


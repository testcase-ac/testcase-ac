#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 5e6;
ll lp[MAX + 1];
vector<int> pr;
set<int> p1, p2;

bool is_prime(int n) {
  if (n <= 1) return false;
  return lp[n] == n;
}

void solve() {
  int n;
  cin >> n;

  ll p1_score = 0, p2_score = 0;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;

    if (is_prime(x)) {
      if (p1.count(x) || p2.count(x)) p1_score -= 1000;
      else p1.insert(x);
    }
    else {
      if (p2.size() < 3) p2_score += 1000;
      else {
        auto it = p2.rbegin();
        it++; it++;
        p2_score += *it;
      }
    }

    if (is_prime(y)) {
      if (p1.count(y) || p2.count(y)) p2_score -= 1000;
      else p2.insert(y);
    }
    else {
      if (p1.size() < 3) p1_score += 1000;
      else {
        auto it = p1.rbegin();
        it++; it++;
        p1_score += *it;
      }
    }
  }

  if (p1_score > p2_score) cout << "소수의 신 갓대웅\n";
  else if (p1_score < p2_score) cout << "소수 마스터 갓규성\n";
  else cout << "우열을 가릴 수 없음\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

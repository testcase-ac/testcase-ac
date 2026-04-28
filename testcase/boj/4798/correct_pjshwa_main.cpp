#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int lp[MAX + 1];
bool npr[MAX + 1];
vector<int> pr;

ll mod(ll a, ll b) { return ((a % b) + b) % b; }

bool is_prime(ll n) {
  if (n < 2) return false;
  if (n <= MAX) return lp[n] == n;
  for (int prime : pr) if (n % prime == 0) return false;
  return true;
}

pll ext_gcd(ll a, ll b){
  if (b) {
    auto tmp = ext_gcd(b, a % b);
    return {tmp.second, tmp.first - (a / b) * tmp.second};
  } else return {1, 0};
}

void solve(ll a, ll b, ll l, ll u, int tc) {
  cout << "Case " << tc << ": ";

  if (gcd(a, b) > 1) {
    cout << is_prime(a * l + b) << '\n';
    return;
  }

  int itr = u - l + 1;
  fill(npr, npr + itr, true);
  npr[0] = is_prime(a * l + b);
  if (u > l) npr[1] = is_prime(a * l + a + b);

  for (ll prime : pr) {
    if (a % prime == 0) continue;
    if (prime * prime > a * u + b) break;

    ll a_inv = ext_gcd(a, prime).first;
    ll n = (a_inv * mod(-b, prime)) % prime;
    n -= l % prime;
    while (n < 0) n += prime;

    for (int i = n; i < itr; i += prime) if (a * (l + i) + b > prime) npr[i] = false;
  }
  cout << accumulate(npr, npr + itr, 0) << '\n';
}

int main() {
  fast_io();

  for (int i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=MAX; ++j)
      lp[i * pr[j]] = pr[j];
  }

  for (int tc = 1;; ++tc) {
    ll a, b, l, u;
    cin >> a;
    if (!a) break;
    cin >> b >> l >> u;
    solve(a, b, l, u, tc);
  }
}

// This is a collection of useful code for solving problems that
// involve modular linear equations.  Note that all of the
// algorithms described here work on nonnegative llegers.

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> VL;
typedef pair<ll, ll> PLL;

vector<VL> facts1;
vector<VL> facts2;
vector<PLL> factors;

// return a % b (positive value)
ll mod(ll a, ll b) {
  return ((a%b)+b)%b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
ll extended_euclid(ll a, ll b, ll &x, ll &y) {  
  ll xx = y = 0;
  ll yy = x = 1;
  while (b) {
    ll q = a/b;
    ll t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

// finds all solutions to ax = b (mod n)
VL modular_linear_equation_solver(ll a, ll b, ll n) {
  ll x, y;
  VL solutions;
  ll d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    for (int i = 0; i < d; i++) solutions.push_back(mod(x + i*(n/d), n));
  }
  return solutions;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
ll mod_inverse(ll a, ll n) {
  ll x, y;
  ll d = extended_euclid(a, n, x, y);
  if (d > 1) return -1;
  return mod(x, n);
}

// Chinese remainder theorem (special case): find z such that
// z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
PLL chinese_remainder_theorem(ll x, ll a, ll y, ll b) {
  ll s, t;
  ll d = extended_euclid(x, y, s, t);
  if (a%d != b%d) return make_pair(0, -1);
  return make_pair(mod(s*b*x+t*a*y,x*y)/d, x*y/d);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
PLL chinese_remainder_theorem(const VL &x, const VL &a) {
  PLL ret = make_pair(a[0], x[0]);
  for (int i = 1; i < x.size(); i++) {
    ret = chinese_remainder_theorem(ret.second, ret.first, x[i], a[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

// computes x and y such that ax + by = c; on failure, x = y =-1
void linear_diophantine(ll a, ll b, ll c, ll &x, ll &y) {
  ll d = gcd(a,b);
  if (c%d) x = y = -1;
  else {
    x = c/d * mod_inverse(a/d, b/d);
    y = (c-a*x)/b;
  }
}

// compute a^b % m
ll power_mod(ll a, ll b, ll m) {
  if (b == 0) return 1;
  else if (b == 1) return a % m;
  else {
    ll tmp = power_mod(a, b >> 1, m);
    if (b % 2 == 0) return tmp * tmp % m;
    else return tmp * tmp * a % m;
  }
}

// compute n! = a * p^e, return (a, e), p is a prime
PLL fact_mod(ll n, ll p, const VL& facts) {
  if (n == 0) return make_pair(1, 0);
  PLL tmp = fact_mod(n / p, p, facts);
  ll a = tmp.first;
  ll e = tmp.second;
  e += n / p;
  if (n / p % 2 != 0) return make_pair(a * (p - facts[n % p]) %p, e);
  else return make_pair(a * facts[n % p] % p, e);
}

// compute n!! (mod m), m is of type p^a, where p is a prime
ll n_fact_fact(ll n, ll m, ll p, const VL& facts) {
  if (n == 0 || n == 1) return 1;
  else if (n < m) return facts[n] * n_fact_fact(n / p, m, p, facts) % m;
  else {
    ll a = facts[m - 1];
    ll b = facts[n % m];
    ll c = n_fact_fact(n / p, m, p, facts);
    return power_mod(a, n / m, m) * b * c % m;
  }
}

ll power(ll a, ll i) {
  if (i == 0) return 1;
  else if (i == 1) return a;
  else {
    ll tmp = power(a, i >> 1);
    if (i % 2 == 0) return tmp * tmp;
    else return tmp * tmp * a;
  }
}

ll comb_mod2(ll n, ll r, ll m, PLL pa, const VL facts, const VL& tmp) {
  ll p, a;
  p = pa.first; a = pa.second;
  ll b = a;
  
  while (b > 0) {
    PLL t1 = fact_mod(n, p, tmp);
    PLL t2 = fact_mod(r, p, tmp);
    PLL t3 = fact_mod(n - r, p, tmp);
    ll e1, e2, e3;
    e1 = t1.second; e2 = t2.second; e3 = t3.second;
    if (e1 >= e2 + e3 + a) return 0;
    if (e1 >= e2 + e3 + b) break;
    b = b - 1;
  }
  ll m1 = n_fact_fact(n, m, p, facts);
  ll m2 = n_fact_fact(r, m, p ,facts);
  ll m3 = n_fact_fact(n - r, m, p, facts);
  return power(p, b) * m1 * mod_inverse(m2, m) * mod_inverse(m3, m) % m;
}

ll C(ll n, ll r) {
  if (n < r) return 0;

  int fsz = factors.size();

  VL xs(fsz, 0);
  VL as(fsz, 0);
  
  for (int i = 0; i < fsz; ++i) {
    xs[i] = power(factors[i].first, factors[i].second);
    as[i] = comb_mod2(n, r, xs[i], factors[i], facts1[i], facts2[i]);
  }
  return chinese_remainder_theorem(xs, as).first;
}

VL gen_fact(int m) {
  VL ret(m, 1);
  ret.push_back(1);
  for (int i = 1; i < m; ++i) {
    if (gcd(i, m) == 1) ret[i] = ret[i - 1] * i % m;
    else ret[i] = ret[i - 1];
  }
  return ret;
}

void init() {
  factors.push_back(make_pair(3, 3));
  factors.push_back(make_pair(11, 1));
  factors.push_back(make_pair(13, 1));
  factors.push_back(make_pair(37, 1));

  for (auto [p, a] : factors) {
    facts1.push_back(gen_fact(power(p, a)));
    facts2.push_back(gen_fact(p));
  }
}

int main() {
  int T, n, r;
  init();
  scanf("%d", &T);
  
  for (int i = 0; i < T; ++i) {
    scanf("%d%d", &n, &r);
    printf("%lld\n", C(n, r));
  }
}

#include <cstdio>
#include <queue>
#define MOD int(1e9 + 7)
#define ll long long
using namespace std;

int main(void){
  int t;
  scanf("%d", &t);

  while (t--) {
    int n;
    scanf("%d", &n);

    ll s;
    priority_queue<ll> pq;
    for(int i = 0; i < n; i++) {
      scanf("%lld", &s);
      pq.push(-s);
    }

    ll energy = 1;
    while (pq.size() >= 2) {
      ll a = pq.top(); pq.pop();
      ll b = pq.top(); pq.pop();
      ll c = a * b;
      pq.push(-c);

      energy = (c % MOD) * (energy % MOD) % MOD;
    }

    printf("%lld\n", energy);
  }
}

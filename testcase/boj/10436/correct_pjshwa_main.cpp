#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  scanf("%d", &t);

  while (t--) {
    long long tc, nom, denom;
    scanf("%lld %lld/%lld", &tc, &nom, &denom);

    int it = nom / denom;
    nom -= denom * it;
    denom -= nom;
    nom += denom;
    denom += nom * it;
    printf("%lld %lld/%lld\n", tc, nom, denom);
  }
}

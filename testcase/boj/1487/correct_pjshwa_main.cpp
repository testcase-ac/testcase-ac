#include <bits/stdc++.h>
typedef long long ll;
#define pii pair<int, int>
using namespace std;

const int MAX = 1e9 + 7;

pii a[1000];
int main() {
  int N, Pi, Di, Pj, Dj, mp = MAX;
  ll mx = 1, pd;
  cin >> N;

  for (int i = 0; i < N; i++) {
    cin >> Pi >> Di;
    a[i] = {Pi, Di};
  }
  sort(a, a + N);
  reverse(a, a + N);

  for (int i = 0; i < N; i++) {
    tie(Pi, Di) = a[i];

    pd = 0;
    for (int j = 0; j < N; j++) {
      tie(Pj, Dj) = a[j];
      if (Dj > Pi || Pj < Pi) continue;
      pd += (Pi - Dj);
    }

    if (mx <= pd) {
      mx = pd;
      mp = Pi;
    }
  }

  cout << (mp == MAX ? 0 : mp) << '\n';
}

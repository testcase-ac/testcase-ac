#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 987654321;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll d[5001];
int main() {
  fast_io();

  d[0] = d[1] = 1;
  for (int i = 2; i <= 5000; i++) {
    for (int j = 0; j < i; j++) d[i] = (d[i] + d[i - j - 1] * d[j]) % MOD;
  }

  int N;
  cin >> N;
  cout << d[N / 2];
}

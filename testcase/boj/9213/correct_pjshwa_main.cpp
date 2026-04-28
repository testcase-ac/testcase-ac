#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int start, stop, badness, cnt;
  vector<ll> fs(1000001, 1);

  for (int i = 2; i <= 1000000; i++) {
    for (int j = 1; i * j <= 1000000; j++) fs[i * j] += i;
  }

  // for (int i = 1; i <= 1e2; i++) {
  //   cout << "fs[" << i << "]: " << fs[i] << endl;
  // }

  int idx = 0;
  while (1) {
    idx++;
    cin >> start >> stop >> badness;
    if (start == stop && stop == badness && badness == 0) break;

    cnt = 0;
    for (int i = start; i <= stop; i++) {
      if (abs(fs[i] - 2 * i) <= badness) cnt++;
    }

    cout << "Test " << idx << ": " << cnt << '\n';
  }

}

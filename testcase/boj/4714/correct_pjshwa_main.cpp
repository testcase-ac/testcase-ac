#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int main() {
  fast_io();

  double d;
  while (1) {
    cin >> d;
    if (d == -1) break;

    cout << fixed << setprecision(2) <<
      "Objects weighing " << d << " on Earth will weigh " << d * 0.167 << " on the moon.\n";
  }
}

#include <iostream>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();

  int a, b, c; cin >> a >> b >> c;
  int abs_sum = abs(a) + abs(b);
  if (abs_sum <= c && (abs_sum - c) % 2 == 0) cout << "YES\n";
  else cout << "NO\n";

  return 0;
}

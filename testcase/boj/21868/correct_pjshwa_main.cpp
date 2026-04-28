#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(NULL); cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  int en, ed, c, d, x0;
  cin >> en >> ed >> c >> d >> x0;
  cout << c * x0 + d << '\n';
  if (c == 0) cout << "0 0";
  else cout << en << ' ' << ed * abs(c);
}

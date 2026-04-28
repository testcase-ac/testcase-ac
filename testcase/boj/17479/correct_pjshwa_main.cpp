#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int a, b, c;
  cin >> a >> b >> c;

  map<string, int> am;
  map<string, int> bm;
  map<string, int> cm;

  string menu;
  int price;
  for (int i = 0; i < a; i++) {
    cin >> menu >> price;
    am[menu] = price;
  }
  for (int i = 0; i < b; i++) {
    cin >> menu >> price;
    bm[menu] = price;
  }
  for (int i = 0; i < c; i++) {
    cin >> menu;
    cm[menu] = 0;
  }

  int n;
  cin >> n;
  bool able = true;

  ll ap = 0, bp = 0, cc = 0;
  while (n--) {
    cin >> menu;
    if (am.count(menu)) ap += am[menu];
    else if (bm.count(menu)) bp += bm[menu];
    else cc++;
  }

  if (
    cc > 1 ||
    (cc == 1 && ap + bp < 50000) ||
    (bp > 0 && ap < 20000)
  ) able = false;

  cout << (able ? "Okay" : "No") << '\n';
}

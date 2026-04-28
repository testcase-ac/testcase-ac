#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int d[601][601];
vector<pii> chunks;
int r(int w, int h) {
  if (d[w][h] == -1) {
    int wi, hi, mv = w * h;
    for (pii chunk : chunks) {
      tie(wi, hi) = chunk;
      if (w >= wi && h >= hi) {
        mv = min(mv, r(w - wi, hi) + r(w, h - hi));
        mv = min(mv, r(w - wi, h) + r(wi, h - hi));
      }
    }

    d[w][h] = mv;
  }

  return d[w][h];
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  int w, h, n, wi, hi;
  cin >> w >> h >> n;

  while (n--) {
    cin >> wi >> hi;
    chunks.push_back({wi, hi});
  }

  cout << r(w, h);
}

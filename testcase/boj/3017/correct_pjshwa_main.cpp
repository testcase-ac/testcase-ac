#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string a, b;
string bx, bm;
int n;

int main() {
  fast_io();

  cin >> a >> b;
  n = a.size();

  bool mfound = false, xfound = false;
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      int cpos = -1;
      for (int j = i - 1; j < n; j++) {
        if (b[j] == a[i - 1]) {
          cpos = j;
          break;
        }
      }
      if (cpos == -1) break;
      else if (cpos != i - 1) swap(b[cpos], b[i - 1]);
    }

    int gpos = -1;
    char gchar = '0' - 1;
    for (int j = i; j < n; j++) {
      if (b[j] < a[i] && b[j] > gchar) {
        gpos = j;
        gchar = b[j];
      }
    }
    if (gpos == -1) continue;
    if (i == 0 && gchar == '0') continue;

    if (i != gpos) swap(b[i], b[gpos]);
    sort(b.begin() + i + 1, b.end());
    reverse(b.begin() + i + 1, b.end());

    if (mfound) bm = max(bm, b);
    else bm = b;
    mfound = true;
  }

  for (int i = 0; i < n; i++) {
    if (i > 0) {
      int cpos = -1;
      for (int j = i - 1; j < n; j++) {
        if (b[j] == a[i - 1]) {
          cpos = j;
          break;
        }
      }
      if (cpos == -1) break;
      else if (cpos != i - 1) swap(b[cpos], b[i - 1]);
    }

    if (i == n - 1 && a == b) {
      bx = b;
      xfound = true;
      break;
    }

    int gpos = -1;
    char gchar = '9' + 1;
    for (int j = i; j < n; j++) {
      if (b[j] > a[i] && b[j] < gchar) {
        gpos = j;
        gchar = b[j];
      }
    }
    if (gpos == -1) continue;

    if (i != gpos) swap(b[i], b[gpos]);
    sort(b.begin() + i + 1, b.end());

    if (xfound) bx = min(bx, b);
    else bx = b;
    xfound = true;
  }

  cout << (xfound ? bx : "0") << '\n' << (mfound ? bm : "0") << '\n';
}

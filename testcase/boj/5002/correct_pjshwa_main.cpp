#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int x;
  string waiting_line;
  cin >> x >> waiting_line;

  if (x == 0) {
    cout << "0\n";
    return 0;
  }

  int line_sz = waiting_line.size();
  int cm = 0, cw = 0, idx = -1;
  bool skip = false;
  while (++idx < line_sz) {
    if (skip) {
      skip = false;
      continue;
    }

    if (cm - cw == x && waiting_line[idx] == 'M') {
      if (idx + 1 < line_sz && waiting_line[idx + 1] == 'W') {
        cw++;
        skip = true;
      }
      else break;
    }
    if (cw - cm == x && waiting_line[idx] == 'W') {
      if (idx + 1 < line_sz && waiting_line[idx + 1] == 'M') {
        cm++;
        skip = true;
      }
      else break;
    }
    waiting_line[idx] == 'M' ? cm++ : cw++;
  }

  cout << idx << '\n';
}

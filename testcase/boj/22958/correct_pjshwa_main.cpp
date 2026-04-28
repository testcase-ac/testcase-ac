#include <bits/stdc++.h>
using namespace std;

int ask(int s, int a, int b) {
  cout << "? " << s << ' ' << a << ' ' << b << endl;
  int ret;
  cin >> ret;
  return ret;
}

void answer(int x) {
  cout << "! " << x << endl;
}

int n, mh;
bool contains(int s, int step) {
  return ask(s, min(n, step), (n - s) / step + 1) == mh;
}

int main() {
  cin >> n;
  if (n == 1) return answer(1), 0;
  mh = ask(1, 1, n);

  int base = 1;
  for (int i = 1; i <= 19; i++) {
    int step = 1 << i;
    if (contains(base + step / 2, step)) base += step / 2;
    if (base + step > n) break;
  }
  answer(base);
}

#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
int a[50][50];
vector<tuple<char, int, int>> ops;

void rotate_right(int i, int c) {
  int b[n];
  for (int k = 0; k < n; k++) b[(k + c) % n] = a[i][k];
  for (int k = 0; k < n; k++) a[i][k] = b[k];
  ops.push_back(make_tuple('R', i + 1, c));
}

void rotate_left(int i, int c) {
  rotate_right(i, n - c);
}

void rotate_down(int j, int c) {
  int b[n];
  for (int k = 0; k < n; k++) b[(k + c) % n] = a[k][j];
  for (int k = 0; k < n; k++) a[k][j] = b[k];
  ops.push_back(make_tuple('D', j + 1, c));
}

void rotate_up(int j, int c) {
  rotate_down(j, n - c);
}

void print_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << a[i][j] << " ";
    cout << endl;
  }
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];

  for (int i = 0; i < n - 1; i++) for (int j = 0; j < n; j++) {
    if (a[i][j] == i + 1) continue;

    bool set = false;
    for (int k = j + 1; k < n; k++) {
      if (a[i][k] == i + 1) {
        rotate_down(j, 1);
        rotate_down(k, 1);
        rotate_left(i + 1, k - j);
        rotate_up(j, 1);
        rotate_up(k, 1);
        set = true;
        break;
      }
    }
    if (set) continue;

    for (int ri = i + 1; ri < n; ri++) {
      for (int ci = 0; ci < n; ci++) {
        if (a[ri][ci] == i + 1) {
          if (ci == j) {
            rotate_right(ri, 1);
            rotate_down(j, ri - i);
            rotate_left(ri, 1);
            rotate_up(j, ri - i);
          }
          else {
            rotate_down(j, ri - i);
            if (ci < j) rotate_right(ri, j - ci);
            else rotate_left(ri, ci - j);
            rotate_up(j, ri - i);
          }
          set = true;
          break;
        }
      }
      if (set) break;
    }
  }

  cout << ops.size() << '\n';
  for (auto t : ops) cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';
}

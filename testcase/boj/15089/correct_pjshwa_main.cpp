#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

unordered_map<string, int> friend_to_index;
int fc = 0;

bool is_a[500][500];
bool has_a[500][500];

int f_index(string f) {
  auto found = friend_to_index.find(f);
  if (friend_to_index.end() == found) {
    friend_to_index.insert({f, fc});
    return fc++;
  }
  else return found->second;
}

int main() {
  fast_io();

  int n, m, f1i, f2i;
  string s1, s2, r;
  cin >> n >> m;

  while (n--) {
    cin >> s1 >> r >> s2;

    if (r == "is-a") {
      f1i = f_index(s1);
      f2i = f_index(s2);
      is_a[f1i][f2i] = true;
    }
    else {
      f1i = f_index(s1);
      f2i = f_index(s2);
      has_a[f1i][f2i] = true;
    }
  }

  for (int i = 0; i < fc; i++) is_a[i][i] = true;

  // Floyd-warshall
  for (int k = 0; k < fc; k++) {
    for (int i = 0; i < fc; i++) {
      for (int j = 0; j < fc; j++) {
        is_a[i][j] = is_a[i][j] || (is_a[i][k] && is_a[k][j]);
        has_a[i][j] = has_a[i][j] || (has_a[i][k] && has_a[k][j]);

        has_a[i][j] = has_a[i][j] || (is_a[i][k] && has_a[k][j]);
        has_a[i][j] = has_a[i][j] || (has_a[i][k] && is_a[k][j]);
      }
    }
  }

  for (int i = 1; i <= m; i++) {
    cin >> s1 >> r >> s2;

    bool result;
    if (r == "is-a") {
      f1i = f_index(s1);
      f2i = f_index(s2);
      result = is_a[f1i][f2i];
    }
    else {
      f1i = f_index(s1);
      f2i = f_index(s2);
      result = has_a[f1i][f2i];
    }

    cout << "Query " << i << ": " << (result ? "true" : "false") << '\n';
  }
}

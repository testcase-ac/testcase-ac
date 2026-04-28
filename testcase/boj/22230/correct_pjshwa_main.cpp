#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
int table[MAX][MAX];

int n = 2;
int m = 3;

void print_table() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << table[i][j] << " ";
    }
    cout << endl;
  }
}


int main() {
  fast_io();

  memset(table, -1, sizeof(table));

  set<int> q;
  vector<int> v;

  for (int i = 10000; i < 100000; i++) {
    if (i % m == 0) q.insert(i), v.push_back(i);
  }

  int sz = v.size();
  cout << "sz: " << sz << endl;
  for (int i = 0; i < sz; i++) {
    for (int j = 0; j < sz; j++) {
      for (int k = 0; k < sz; k++) {
        for (int l = 0; l < sz; l++) {
          for (int m = 0; m < sz; m++) {
            string s1 = to_string(v[i]);
            string s2 = to_string(v[j]);
            string s3 = to_string(v[k]);
            string s4 = to_string(v[l]);
            string s5 = to_string(v[m]);

            if (i == j || i == k || i == l || i == m ||
                j == k || j == l || j == m ||
                k == l || k == m ||
                l == m) continue;

            if (s1[1] == '0' || s1[2] == '0' || s1[3] == '0' || s1[4] == '0') continue;

            for (int d = 0; d < 5; d++) {
              table[0][d] = s1[d] - '0';
              table[1][d] = s2[d] - '0';
              table[2][d] = s3[d] - '0';
              table[3][d] = s4[d] - '0';
              table[4][d] = s5[d] - '0';
            }

            int s, pw;

            s = 0, pw = 1;
            for (int u = 4; u >= 0; u--) {
              s += table[u][0] * pw;
              pw *= 10;
            }
            if (!q.count(s)) continue;

            s = 0, pw = 1;
            for (int u = 4; u >= 0; u--) {
              s += table[u][1] * pw;
              pw *= 10;
            }
            if (!q.count(s)) continue;

            s = 0, pw = 1;
            for (int u = 4; u >= 0; u--) {
              s += table[u][2] * pw;
              pw *= 10;
            }
            if (!q.count(s)) continue;

            s = 0, pw = 1;
            for (int u = 4; u >= 0; u--) {
              s += table[u][3] * pw;
              pw *= 10;
            }
            if (!q.count(s)) continue;

            s = 0, pw = 1;
            for (int u = 4; u >= 0; u--) {
              s += table[u][4] * pw;
              pw *= 10;
            }
            if (!q.count(s)) continue;

            print_table();
            exit(0);
          }
        }
      }
    }
  }
}

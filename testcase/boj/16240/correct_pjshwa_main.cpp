#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

const int MAX = 1e5 + 10000, BIAS = 1e5;
int A[MAX], B[MAX];
int parent[MAX];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int N;
  cin >> N;

  for (int i = 0; i < MAX; i++) parent[i] = i;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    if ('0' <= s[0] && s[0] <= '9') A[i] = stoi(s) + BIAS;
    else A[i] = fidx(s);
  }
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    if ('0' <= s[0] && s[0] <= '9') B[i] = stoi(s) + BIAS;
    else B[i] = fidx(s);

    Union(A[i], B[i]);
  }

  for (int i = 1; i <= 1000; i++) for (int j = i + 1; j <= 1000; j++) {
    if (Find(i + BIAS) == Find(j + BIAS)) return cout << "NE\n", void();
  }
  cout << "DA\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

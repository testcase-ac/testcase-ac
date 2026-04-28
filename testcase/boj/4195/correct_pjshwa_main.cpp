#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

unordered_map<string, int> friend_to_index;
int friends_count;

int parent[(int)2e5 + 1];
int cnts[(int)2e5 + 1];

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

int f_index(string f) {
  auto found = friend_to_index.find(f);
  if (friend_to_index.end() == found) {
    friend_to_index.insert({f, friends_count});
    return friends_count++;
  }
  else return found->second;
}

int main() {
  fast_io();

  int t, n, f1i, f2i;
  string f1, f2;
  cin >> t;

  while (t--) {
    friends_count = 0;
    friend_to_index.clear();

    cin >> n;
    for (int i = 0; i <= 2 * n; i++) {
      parent[i] = i;
      cnts[i] = 1;
    }

    while (n--) {
      cin >> f1 >> f2;
      f1i = f_index(f1);
      f2i = f_index(f2);

      if (Find(f1i) != Find(f2i)) {
        cnts[Find(f1i)] += cnts[Find(f2i)];
        Union(f1i, f2i);
      }
      cout << cnts[Find(f1i)] << '\n';
    }
  }
}

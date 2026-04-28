#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
list<int>::iterator id_to_idx[MAX + 1];

void print_list(list<int> &l) {
  for (auto it = l.begin(); it != l.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  list<int> stations;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    stations.push_back(x);
    id_to_idx[x] = stations.end();
    id_to_idx[x]--;
  }

  while (m--) {
    string op;
    int a, b;
    cin >> op;
    if (op == "BN") {
      cin >> a >> b;
      auto it = id_to_idx[a];
      it++;
      if (it == stations.end()) it = stations.begin();
      cout << *it << '\n';
      stations.insert(it, b);
    }
    if (op == "BP") {
      cin >> a >> b;
      auto it = id_to_idx[a];
      if (it == stations.begin()) it = stations.end();
      it--;
      cout << *it << '\n';
      stations.insert(id_to_idx[a], b);
    }
    if (op == "CN") {
      cin >> a;
      auto it = id_to_idx[a];
      it++;
      if (it == stations.end()) it = stations.begin();
      cout << *it << '\n';
      stations.erase(it);
    }
    if (op == "CP") {
      cin >> a;
      auto it = id_to_idx[a];
      if (it == stations.begin()) it = stations.end();
      it--;
      cout << *it << '\n';
      stations.erase(it);
    }

    // print_list(stations);
  }
}

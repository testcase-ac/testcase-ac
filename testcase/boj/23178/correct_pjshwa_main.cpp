#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e5;
int tree[1 << 19];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

bool presence[MAX];
priority_queue<int> max_pq;
priority_queue<int, vector<int>, greater<int>> min_pq;

int get_min() {
  while (!presence[min_pq.top()]) min_pq.pop();
  return min_pq.top();
}

int get_max() {
  while (!presence[max_pq.top()]) max_pq.pop();
  return max_pq.top();
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  string o;
  cin >> n >> o;
  SegmentTree s(n);
  for (int i = 0; i < n; i++) {
    if (o[i] == 'O') {
      presence[i] = true;
      max_pq.push(i);
      min_pq.push(i);
    }
    else s.update(i, 1);
  }

  int q;
  cin >> q;
  while (q--) {
    int x;
    cin >> x;
    x--;

    if (presence[x]) {
      presence[x] = false;
      s.update(x, 1);
    }
    else {
      presence[x] = true;
      s.update(x, 0);
      max_pq.push(x);
      min_pq.push(x);
    }

    cout << min(s.query(get_min(), n - 1), s.query(0, get_max())) << '\n';
  }
}

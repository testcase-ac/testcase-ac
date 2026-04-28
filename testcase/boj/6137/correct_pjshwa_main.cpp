#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
const ll INF = 1e18;
map<string, int> fi;
int fcount;
vector<int> graph[MAX];
ll cdist[20][MAX];
map<int, int> pos[MAX];
int inv[MAX];

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

void solve() {
  int n;
  cin >> n;

  deque<char> dq;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    dq.push_back(s[0]);
  }

  while (1) {
    if (dq.empty()) break;

    int it = 80;
    while (it--) {
      if (dq.empty()) break;

      if (dq.front() < dq.back()) {
        cout << dq.front();
        dq.pop_front();
      }
      else if (dq.front() > dq.back()) {
        cout << dq.back();
        dq.pop_back();
      }
      else {
        bool f = 1;
        stack<char> traj;
        while (dq.size() > 1 && dq.front() == dq.back()) {
          traj.push(dq.front());
          dq.pop_front();
          dq.pop_back();
        }

        if (dq.size() > 1 && dq.front() > dq.back()) f = false;
        while (!traj.empty()) {
          dq.push_back(traj.top());
          dq.push_front(traj.top());
          traj.pop();
        }

        if (f) {
          cout << dq.front();
          dq.pop_front();
        }
        else {
          cout << dq.back();
          dq.pop_back();
        }
      }

    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
 
using namespace std;
 
// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
typedef vector<int> vi;
#define f first
#define s second
// END NO SAD
 
template<class Fun>
class y_combinator_result {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
 
  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};
 
template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<vector<ll>> matrix;
 
void solve() {
  set<tuple<int, int, string>> lazy; // power level, timestamp, name
  set<tuple<int, int, string>> workers;
  map<string, int> nametots;
  map<string, int> nametolevel;
  auto rebalance = [&](bool print) -> void {
    int shouldhave = (sz(workers) + sz(lazy)) / 5;
    if(sz(workers) && sz(lazy) && *lazy.rbegin() > *workers.begin()) {
      auto lhs = *lazy.rbegin(); lazy.erase(lhs);
      auto rhs = *workers.begin(); workers.erase(rhs);
      lazy.insert(rhs); workers.insert(lhs);
    }
    if(sz(workers) < shouldhave) {
      auto curr = *lazy.rbegin();
      lazy.erase(curr);
      workers.insert(curr);
      if(print) {
        cout << get<2>(curr) << " is working hard now.\n";
      }
    }
    if(sz(workers) > shouldhave) {
      auto curr = *workers.begin();
      workers.erase(curr);
      lazy.insert(curr);
      if(print) {
        cout << get<2>(curr) << " is not working now.\n";
      }
    }
  };
  int n;
  cin >> n;
  int currt = 0;
  for(int i = 0; i < n; i++) {
    string ss;
    cin >> ss;
    int level;
    cin >> level;
    nametolevel[ss] = level;
    lazy.emplace(level, currt, ss);
    nametots[ss] = currt++;
    rebalance(false);
  }
  int qq;
  cin >> qq;
  while(qq--) {
    string op, ss;
    cin >> op >> ss;
    if(op[0] == '-') {
      int t = nametots[ss];
      int level = nametolevel[ss];
      tuple<int, int, string> want = {level, t, ss};
      assert(workers.erase(want) ^ lazy.erase(want));
    }
    else {
      assert(op[0] == '+');
      int level;
      cin >> level;
      nametots[ss] = currt;
      nametolevel[ss] = level;
      tuple<int, int, string> want = {level, currt++, ss};
      int numworkerswant = (sz(lazy) + sz(workers) + 1) / 5;
      if(numworkerswant > sz(workers) && want > *lazy.rbegin()) {
        cout << ss << " is working hard now.\n";
        workers.insert(want);
      }
      else if(sz(workers) && want > *workers.begin()) {
        cout << ss << " is working hard now.\n";
        workers.insert(want);
      }
      else {
        cout << ss << " is not working now.\n";
        lazy.insert(want);
      }
    }
    rebalance(true);
  }
}
 
// what would chika do
// are there edge cases (N=1?)
// are array sizes proper (scaled by proper constant, for example 2* for koosaga tree)
// integer overflow?
// DS reset properly between test cases
// are you doing geometry in floating points
// are you not using modint when you should
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}

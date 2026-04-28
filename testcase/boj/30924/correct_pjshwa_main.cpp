#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ask(char t, int x) {
  cout << "? " << t << ' ' << x << endl;
  int ret; cin >> ret;
  return ret;
}

vector<int> getRandomDistinctNumbers(int start, int end, int count) {
  // Initialize vector with numbers in the desired range
  vector<int> numbers;
  for (int i = start; i <= end; ++i) numbers.push_back(i);

  // Seed the random number generator
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  auto randint = [&rng](int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
  };

  // Use Fisher-Yates shuffle algorithm
  for (int i = static_cast<int>(numbers.size()) - 1; i > 0; --i) {
    int j = randint(0, i);
    swap(numbers[i], numbers[j]);
  }

  // Take the first 'count' elements
  numbers.resize(count);
  return numbers;
}

void solve() {

  int N = 1e4;
  vector<int> As = getRandomDistinctNumbers(1, N, 9999);
  vector<int> Bs = getRandomDistinctNumbers(1, N, 9998);

  int A, B;
  for (int e : As) {
    if (ask('A', e)) {
      A = e;
      break;
    }
  }
  for (int e : Bs) {
    if (ask('B', e)) {
      B = e;
      break;
    }
  }

  cout << "! " << A + B << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

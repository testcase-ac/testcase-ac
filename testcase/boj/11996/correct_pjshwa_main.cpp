#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// The first solution to this problem that people will likely come up with is something like the following: process each of the cows in some order. For each cow, have it walk around the barn until it comes across the first empty door, then enter that door.

// The important insight is to notice that for any two cows A and B, if A walks past B's start point, then A can exit at a door before B's endpoint. This is because, if A walked past both B's start and end points, then we could obtain a solution that's just as good by switching A and B's endpoints. Thus, if we are choosing between many cows to drop off at one door, we may as well choose the cow that started walking first without hurting our solution.

// This suggests an order in which to process the cows: we simply start at any point on the circle and begin walking all the cows at that point around the circle. We keep track of the distance walked by all our active cows, and pick up any cows we encounter along the way. At every door, we "drop a cow off", and subtract 1 from our running total. We have to make sure that we find a point to start at such that we always have a cow to drop off at each door, and such a point is guaranteed to exist in some optimal solution because of our insight above. One way to find this point is to go around the circle like this once and finding the point where we have the largest number of cows. Then we can start at that point when we actually want to compute the solution.

// Here's Mark Gordon's code:

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

long long sumn2(long long v) {
  return v * (v + 1) * (2 * v + 1) / 6;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<ll> A(n);

  int c = 0;
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    c = max(0ll, c + A[i] - 1);
  }

  for (int i = 0; ; i++) {
    if (c == 0) {
      rotate(A.begin(), A.begin() + i, A.begin() + n);
      break;
    }
    c = max(0ll, c + A[i] - 1);
  }

  long long result = 0;
  for (int i = 0; i < n; i++) {
    result += sumn2(A[i] + c - 1) - sumn2(c - 1);
    c = max(0ll, c + A[i] - 1);
  }
  cout << result << endl;
}

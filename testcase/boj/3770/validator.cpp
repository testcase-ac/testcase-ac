#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

class Fenwick {
 public:
  explicit Fenwick(int n) : tree_(n + 1, 0) {}

  void add(int index, long long value) {
    for (int i = index; i < static_cast<int>(tree_.size()); i += i & -i) {
      tree_[i] += value;
    }
  }

  long long sum(int index) const {
    long long result = 0;
    for (int i = index; i > 0; i -= i & -i) {
      result += tree_[i];
    }
    return result;
  }

 private:
  vector<long long> tree_;
};

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);

  const int maxCities = 1000;
  const int maxHighways = 400000;
  const long long maxAnswer = 9223372036854775807LL;

  int t = inf.readInt(1, 100000, "T");
  inf.readEoln();

  long long totalHighways = 0;
  for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
    setTestCase(caseIndex);

    int n = inf.readInt(1, maxCities, "N");
    inf.readSpace();
    int m = inf.readInt(1, maxCities, "M");
    inf.readSpace();
    int k = inf.readInt(0, maxHighways, "K");
    inf.readEoln();

    totalHighways += k;
    // CHECK: The statement says the number of highways is at most 400000; enforce it over the whole input.
    ensuref(totalHighways <= maxHighways,
            "total number of highways exceeds %d after case %d: %lld", maxHighways, caseIndex,
            totalHighways);

    vector<vector<int>> westByEast(n + 1);
    for (int i = 1; i <= k; ++i) {
      int east = inf.readInt(1, n, "east");
      inf.readSpace();
      int west = inf.readInt(1, m, "west");
      inf.readEoln();

      // CHECK: The statement does not say endpoint pairs are unique, so duplicate highway endpoints are accepted.
      westByEast[east].push_back(west);
    }

    Fenwick seen(m);
    long long crossings = 0;
    for (int east = 1; east <= n; ++east) {
      sort(westByEast[east].begin(), westByEast[east].end());
      for (int west : westByEast[east]) {
        crossings += seen.sum(m) - seen.sum(west);
        ensuref(crossings <= maxAnswer, "answer exceeds 2^63-1 in case %d", caseIndex);
      }
      for (int west : westByEast[east]) {
        seen.add(west, 1);
      }
    }

    // CHECK: The statement's geometric no-triple-crossing guarantee is not validated because coordinates are absent.
  }

  inf.readEof();
}

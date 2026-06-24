#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Claim {
  bool hasWitness;
};

int testCount;
vector<int> nByCase;
vector<vector<int>> aByCase;

Claim readClaim(InStream& stream, int tc) {
  string verdict = stream.readWord("YES|NO", format("verdict for case %d", tc).c_str());
  if (verdict == "NO") {
    return {false};
  }

  int n = nByCase[tc - 1];
  const vector<int>& a = aByCase[tc - 1];
  vector<int> used(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    int value = stream.readInt(1, n, format("case %d P[%d]", tc, i + 1).c_str());
    if (used[value]) {
      stream.quitf(_wa, "case %d: value %d appears more than once", tc, value);
    }
    used[value] = 1;
    if (value == a[i]) {
      stream.quitf(_wa, "case %d: P[%d] equals A[%d] = %d", tc, i + 1, i + 1, value);
    }
  }

  return {true};
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  testCount = inf.readInt();
  nByCase.resize(testCount);
  aByCase.resize(testCount);
  for (int tc = 1; tc <= testCount; ++tc) {
    int n = inf.readInt();
    nByCase[tc - 1] = n;
    aByCase[tc - 1].resize(n);
    for (int i = 0; i < n; ++i) {
      aByCase[tc - 1][i] = inf.readInt();
    }
  }

  for (int tc = 1; tc <= testCount; ++tc) {
    Claim jury = readClaim(ans, tc);
    Claim participant = readClaim(ouf, tc);

    if (jury.hasWitness) {
      if (!participant.hasWitness) {
        quitf(_wa, "case %d: jury has a valid permutation but participant answered NO", tc);
      }
    } else if (participant.hasWitness) {
      quitf(_fail, "case %d: participant found a valid permutation while jury answered NO", tc);
    }
  }

  if (!ans.seekEof()) {
    quitf(_fail, "extra output after jury answer");
  }
  if (!ouf.seekEof()) {
    quitf(_wa, "extra output after participant answer");
  }

  quitf(_ok, "all %d cases match the jury feasibility claims", testCount);
}

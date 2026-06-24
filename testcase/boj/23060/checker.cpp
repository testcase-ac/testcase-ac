#include "testlib.h"

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

struct Claim {
  bool impossible;
};

int n, startR, startC;

bool isKnightMove(int r1, int c1, int r2, int c2) {
  int dr = abs(r1 - r2);
  int dc = abs(c1 - c2);
  return (dr == 1 && dc == 2) || (dr == 2 && dc == 1);
}

Claim readClaim(InStream& stream) {
  string first = stream.readToken();
  if (first == "-1") {
    if (!stream.seekEof()) {
      stream.quitf(_wa, "extra output after -1");
    }
    return {true};
  }

  long long k;
  try {
    size_t pos = 0;
    k = stoll(first, &pos);
    if (pos != first.size()) {
      stream.quitf(_wa, "visit count is not an integer: %s", first.c_str());
    }
  } catch (...) {
    stream.quitf(_wa, "visit count is not an integer: %s", first.c_str());
  }

  long long maxVisits = 2LL * n * n;
  if (k < 1 || k > maxVisits) {
    stream.quitf(_wa, "visit count %lld is outside [1, %lld]", k, maxVisits);
  }

  vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));
  int prevR = -1, prevC = -1;
  for (long long i = 0; i < k; ++i) {
    int r = stream.readInt(1, n, format("row[%lld]", i + 1).c_str());
    int c = stream.readInt(1, n, format("col[%lld]", i + 1).c_str());

    if (i == 0) {
      if (r != startR || c != startC) {
        stream.quitf(_wa,
                     "first visit is (%d, %d), expected start (%d, %d)",
                     r, c, startR, startC);
      }
    } else if (!isKnightMove(prevR, prevC, r, c)) {
      stream.quitf(_wa,
                   "move %lld from (%d, %d) to (%d, %d) is not a knight move",
                   i, prevR, prevC, r, c);
    }

    visited[r][c] = true;
    prevR = r;
    prevC = c;
  }

  for (int r = 1; r <= n; ++r) {
    for (int c = 1; c <= n; ++c) {
      if (!visited[r][c]) {
        stream.quitf(_wa, "cell (%d, %d) was not visited", r, c);
      }
    }
  }

  if (!stream.seekEof()) {
    stream.quitf(_wa, "extra output after travel plan");
  }
  return {false};
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  n = inf.readInt(1, 500, "N");
  startR = inf.readInt(1, n, "start row");
  startC = inf.readInt(1, n, "start column");

  Claim jury = readClaim(ans);
  Claim participant = readClaim(ouf);

  if (jury.impossible) {
    if (participant.impossible) {
      quitf(_ok, "both outputs claim impossible");
    }
    quitf(_fail, "participant provided a valid travel plan while jury says impossible");
  }

  if (participant.impossible) {
    quitf(_wa, "participant claims impossible while jury provides a valid travel plan");
  }

  quitf(_ok, "valid travel plan");
}

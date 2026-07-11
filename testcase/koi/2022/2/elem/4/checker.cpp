#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using pii = pair<int, int>;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int participant_ans = ouf.readInt();
  int jury_ans = ans.readInt();
  if(participant_ans != jury_ans)
    quitf(_wa, "Answer is different");

  int n = inf.readInt();
  int m = inf.readInt();
  int w = inf.readInt();
  int h = inf.readInt();
  vector<pii> rdots(n), bdots(m);
  for(pii &p : rdots) {
    p.first = inf.readInt();
    p.second = inf.readInt();
  }
  for(pii &p : bdots) {
    p.first = inf.readInt();
    p.second = inf.readInt();
  }

  // if coordinates too big(small), it must be wrong
  constexpr int MAX_X = int(1e9);
  int sx = ouf.readInt(-MAX_X, MAX_X, "output x");
  int sy = ouf.readInt(-MAX_X, MAX_X, "output y");

  int real_ans = 0;
  for(pii p : rdots) {
    int cx = p.first, cy = p.second;
    if(sx <= cx && cx <= sx + w && sy <= cy && cy <= sy + h) ++real_ans;
  }
  for(pii p : bdots) {
    int cx = p.first, cy = p.second;
    if(sx <= cx && cx <= sx + w && sy <= cy && cy <= sy + h) --real_ans;
  }
  real_ans = abs(real_ans);
  if(jury_ans != real_ans)
    quitf(_wa, "Given rectangle is not valid answer");

  quitf(_ok, "n=%d m=%d", n, m);
}

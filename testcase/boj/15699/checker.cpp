#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Dsu {
  vector<int> parent, size;

  explicit Dsu(int n) : parent(n), size(n, 1) {
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (size[a] < size[b]) swap(a, b);
    parent[b] = a;
    size[a] += size[b];
    return true;
  }
};

struct Answer {
  int changed;
};

int n, m;
vector<int> originalDegree;

Answer readAnswer(InStream& stream) {
  int claimedChanged = stream.readInt(0, n, "changed_count");
  int outputN = stream.readInt(0, n, "output_n");
  int outputM = stream.readInt(0, max(0, n - 1), "output_m");

  if (outputN != n) {
    stream.quitf(_wa, "output_n is %d, expected %d", outputN, n);
  }
  if (outputM != n - 1) {
    stream.quitf(_wa, "output_m is %d, expected %d", outputM, n - 1);
  }

  Dsu dsu(n);
  vector<int> treeDegree(n, 0);
  for (int i = 0; i < outputM; ++i) {
    int a = stream.readInt(0, n - 1, format("edge[%d].a", i + 1).c_str());
    int b = stream.readInt(0, n - 1, format("edge[%d].b", i + 1).c_str());
    if (a == b) {
      stream.quitf(_wa, "edge %d is a self-loop at node %d", i + 1, a);
    }
    if (!dsu.unite(a, b)) {
      stream.quitf(_wa, "edge %d creates a cycle between %d and %d", i + 1, a, b);
    }
    ++treeDegree[a];
    ++treeDegree[b];
  }
  if (!stream.seekEof()) {
    stream.quitf(_wa, "extra output after the wireless links");
  }

  int changed = 0;
  for (int i = 0; i < n; ++i) {
    if (treeDegree[i] != originalDegree[i]) ++changed;
  }

  if (claimedChanged != changed) {
    stream.quitf(_wa, "claimed changed_count is %d, but tree has %d changed nodes",
                 claimedChanged, changed);
  }

  return {changed};
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  n = inf.readInt(2, 10000, "n");
  m = inf.readInt(1, 100000, "m");
  originalDegree.assign(n, 0);
  for (int i = 0; i < m; ++i) {
    int a = inf.readInt(0, n - 1, format("input_edge[%d].a", i + 1).c_str());
    int b = inf.readInt(0, n - 1, format("input_edge[%d].b", i + 1).c_str());
    ++originalDegree[a];
    ++originalDegree[b];
  }

  Answer jury = readAnswer(ans);
  Answer participant = readAnswer(ouf);

  if (participant.changed > jury.changed) {
    quitf(_wa, "jury has better answer: jury=%d participant=%d",
          jury.changed, participant.changed);
  }
  if (participant.changed < jury.changed) {
    quitf(_fail, "participant found better answer: jury=%d participant=%d",
          jury.changed, participant.changed);
  }
  quitf(_ok, "answer=%d", participant.changed);
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct PotionType {
    int i;
    int j;
    long long count;
};

struct Output {
    vector<PotionType> potions;
    long long total;
};

int n;
vector<long long> bottles;

Output readOutput(InStream& stream) {
    long long maxTotal = 0;
    for (int i = 1; i <= n; ++i) {
        maxTotal += bottles[i];
    }
    maxTotal /= 2;

    int maxLines = (int)min<long long>(maxTotal, 1000000);
    int m = stream.readInt(0, maxLines, "m");
    vector<long long> used(n + 1, 0);
    vector<PotionType> potions;
    potions.reserve(m);

    int lastI = 0;
    int lastJ = 0;
    long long total = 0;

    for (int line = 1; line <= m; ++line) {
        int i = stream.readInt(1, n, format("i[%d]", line).c_str());
        int j = stream.readInt(1, n, format("j[%d]", line).c_str());
        long long count = stream.readLong(1, 1000000000000000000LL, format("c[%d]", line).c_str());

        if (i >= j) {
            stream.quitf(_wa, "line %d has i=%d, j=%d, expected i < j", line, i, j);
        }
        if (line > 1 && make_pair(i, j) <= make_pair(lastI, lastJ)) {
            stream.quitf(_wa,
                         "line %d has pair (%d,%d) after (%d,%d), expected decreasing price order",
                         line,
                         i,
                         j,
                         lastI,
                         lastJ);
        }

        if (used[i] > bottles[i] - count) {
            stream.quitf(_wa, "substance %d uses more bottles than available", i);
        }
        if (used[j] > bottles[j] - count) {
            stream.quitf(_wa, "substance %d uses more bottles than available", j);
        }
        if (total > maxTotal - count) {
            stream.quitf(_wa, "total potion count exceeds the input bottle limit");
        }

        used[i] += count;
        used[j] += count;
        total += count;
        potions.push_back({i, j, count});
        lastI = i;
        lastJ = j;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after potion plan");
    }
    return {potions, total};
}

int compareOutputs(const Output& participant, const Output& jury) {
    if (participant.total != jury.total) {
        return participant.total < jury.total ? -1 : 1;
    }

    size_t p = 0;
    size_t q = 0;
    while (p < participant.potions.size() || q < jury.potions.size()) {
        int pi = n + 1;
        int pj = n + 1;
        long long pc = 0;
        if (p < participant.potions.size()) {
            pi = participant.potions[p].i;
            pj = participant.potions[p].j;
        }

        int qi = n + 1;
        int qj = n + 1;
        long long qc = 0;
        if (q < jury.potions.size()) {
            qi = jury.potions[q].i;
            qj = jury.potions[q].j;
        }

        pair<int, int> cur = min(make_pair(pi, pj), make_pair(qi, qj));
        if (p < participant.potions.size() && make_pair(pi, pj) == cur) {
            pc = participant.potions[p].count;
            ++p;
        }
        if (q < jury.potions.size() && make_pair(qi, qj) == cur) {
            qc = jury.potions[q].count;
            ++q;
        }

        if (pc != qc) {
            return pc < qc ? -1 : 1;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "n");
    bottles.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        bottles[i] = inf.readLong(1, 1000000000LL, format("a[%d]", i).c_str());
    }

    Output jury = readOutput(ans);
    Output participant = readOutput(ouf);

    int cmp = compareOutputs(participant, jury);
    if (cmp < 0) {
        quitf(_wa,
              "participant output is worse than jury output: participant total=%lld, jury total=%lld",
              participant.total,
              jury.total);
    }
    if (cmp > 0) {
        quitf(_fail,
              "participant output is better than jury output: participant total=%lld, jury total=%lld",
              participant.total,
              jury.total);
    }

    quitf(_ok, "valid optimal potion plan with %lld potions", participant.total);
}

#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int V, P;
long long L;
vector<long long> villages;
map<long long, int> villageCount;

struct Answer {
    long long cost;
    vector<long long> offices;
};

long long circularDistance(long long a, long long b) {
    long long diff = llabs(a - b);
    return min(diff, L - diff);
}

Answer readAnswer(InStream& stream) {
    long long reported = stream.readLong(0, 9000000000000000000LL, "minimum distance sum");

    vector<long long> offices(P);
    map<long long, int> used;
    for (int i = 0; i < P; ++i) {
        offices[i] = stream.readLong(0, L - 1, format("office[%d]", i + 1).c_str());
        if (i > 0 && offices[i - 1] > offices[i]) {
            stream.quitf(_wa,
                         "office positions must be nondecreasing, but office[%d]=%lld and office[%d]=%lld",
                         i,
                         offices[i - 1],
                         i + 1,
                         offices[i]);
        }

        auto it = villageCount.find(offices[i]);
        if (it == villageCount.end()) {
            stream.quitf(_wa, "office[%d]=%lld is not a village position", i + 1, offices[i]);
        }
        ++used[offices[i]];
        if (used[offices[i]] > it->second) {
            stream.quitf(_wa,
                         "office position %lld is used %d times, but appears as a village %d times",
                         offices[i],
                         used[offices[i]],
                         it->second);
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after office positions");
    }

    long long computed = 0;
    for (long long village : villages) {
        long long best = L;
        for (long long office : offices) {
            best = min(best, circularDistance(village, office));
        }
        computed += best;
    }

    if (computed != reported) {
        stream.quitf(_wa,
                     "reported distance sum is %lld, but selected offices have distance sum %lld",
                     reported,
                     computed);
    }

    return {computed, offices};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    V = inf.readInt(1, 100, "V");
    P = inf.readInt(1, V, "P");
    L = inf.readLong(1, 1000000000000LL, "L");

    villages.resize(V);
    for (int i = 0; i < V; ++i) {
        villages[i] = inf.readLong(0, L - 1, format("village[%d]", i + 1).c_str());
        ++villageCount[villages[i]];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.cost > jury.cost) {
        quitf(_wa,
              "participant distance sum %lld is worse than jury distance sum %lld",
              participant.cost,
              jury.cost);
    }
    if (participant.cost < jury.cost) {
        quitf(_fail,
              "participant distance sum %lld is better than jury distance sum %lld",
              participant.cost,
              jury.cost);
    }

    quitf(_ok, "distance sum %lld", participant.cost);
}

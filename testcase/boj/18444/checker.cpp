#include "testlib.h"

#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int V, P;
long long L;
vector<long long> villages;
map<long long, int> villageCount;

long long circularDistance(long long a, long long b) {
    long long diff = llabs(a - b);
    return min(diff, L - diff);
}

struct Answer {
    long long claimed;
    long long actual;
    vector<long long> offices;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0LL, 1000000000000000000LL, "S");
    stream.readEoln();

    vector<long long> offices(P);
    map<long long, int> used;
    for (int i = 0; i < P; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        offices[i] = stream.readLong(0LL, L - 1, format("office[%d]", i + 1).c_str());
        if (i > 0 && offices[i] < offices[i - 1]) {
            stream.quitf(_wa,
                         "office positions must be nondecreasing, but office[%d]=%lld > office[%d]=%lld",
                         i, offices[i - 1], i + 1, offices[i]);
        }

        ++used[offices[i]];
        auto it = villageCount.find(offices[i]);
        if (it == villageCount.end()) {
            stream.quitf(_wa, "office[%d]=%lld is not a village position", i + 1, offices[i]);
        }
        if (used[offices[i]] > it->second) {
            stream.quitf(_wa,
                         "office position %lld is used %d times, but only %d villages have that position",
                         offices[i], used[offices[i]], it->second);
        }
    }
    stream.readEoln();
    stream.readEof();

    long long actual = 0;
    for (long long village : villages) {
        long long best = L;
        for (long long office : offices) {
            best = min(best, circularDistance(village, office));
        }
        actual += best;
    }

    if (actual != claimed) {
        stream.quitf(_wa, "claimed S=%lld, but supplied offices have total distance %lld", claimed, actual);
    }

    return {claimed, actual, offices};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    V = inf.readInt();
    P = inf.readInt();
    L = inf.readLong();
    villages = inf.readLongs(V);
    for (long long village : villages) {
        ++villageCount[village];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actual > jury.actual) {
        quitf(_wa, "jury has better answer: jury=%lld participant=%lld", jury.actual, participant.actual);
    }
    if (participant.actual < jury.actual) {
        quitf(_fail, "participant found better answer: jury=%lld participant=%lld", jury.actual, participant.actual);
    }

    quitf(_ok, "answer=%lld", participant.actual);
}

#include "testlib.h"

#include <vector>

using namespace std;

const long long MAX_K = 2000000000LL;

int n;
vector<long long> a;
vector<int> steps;

struct Answer {
    int count;
    long long k;
};

int countHits(long long k) {
    long long played = a[0];
    int hits = 1;

    for (int i = 1; i < n; ++i) {
        played += steps[i] * k;
        if (played == a[i]) {
            ++hits;
        }
    }

    return hits;
}

Answer readAnswer(InStream& stream, TResult invalidResult) {
    int claimed = stream.readInt(0, n, "maximum correct keys");
    long long k = stream.readLong(0, MAX_K, "K");
    if (!stream.seekEof()) {
        stream.quitf(invalidResult, "extra output after K");
    }

    int actual = countHits(k);
    if (claimed != actual) {
        stream.quitf(invalidResult,
                     "claimed count %d does not match K=%lld, which hits %d keys",
                     claimed,
                     k,
                     actual);
    }

    return {actual, k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong();
    }

    steps.assign(n, 0);
    for (int i = 1; i < n; ++i) {
        if (a[i] > a[i - 1]) {
            steps[i] = 1;
        } else if (a[i] < a[i - 1]) {
            steps[i] = -1;
        }
    }

    Answer jury = readAnswer(ans, _fail);
    Answer participant = readAnswer(ouf, _wa);

    if (participant.count < jury.count) {
        quitf(_wa,
              "jury has better answer: jury=%d participant=%d",
              jury.count,
              participant.count);
    }
    if (participant.count > jury.count) {
        quitf(_fail,
              "participant found better answer: jury=%d participant=%d",
              jury.count,
              participant.count);
    }

    quitf(_ok, "answer=%d K=%lld", participant.count, participant.k);
}

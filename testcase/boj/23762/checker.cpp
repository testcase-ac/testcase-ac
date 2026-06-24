#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<long long> skill;

struct Answer {
    long long claimed;
    long long actual;
};

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0LL, 100000000000000LL, "minimum total skill difference");
    int omittedCount = n % 4;

    vector<int> omitted(n, 0);
    for (int i = 0; i < omittedCount; ++i) {
        int person = stream.readInt(0, n - 1, format("omitted[%d]", i + 1).c_str());
        if (omitted[person]) {
            stream.quitf(_wa, "person %d is omitted more than once", person);
        }
        omitted[person] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after omitted players");
    }

    vector<long long> playing;
    playing.reserve(n - omittedCount);
    for (int i = 0; i < n; ++i) {
        if (!omitted[i]) {
            playing.push_back(skill[i]);
        }
    }
    sort(playing.begin(), playing.end());

    long long actual = 0;
    for (int i = 0; i < (int)playing.size(); i += 4) {
        actual += playing[i + 3] - playing[i];
    }

    if (claimed != actual) {
        stream.quitf(_wa,
                     "claimed total skill difference is %lld, but omitted players give %lld",
                     claimed,
                     actual);
    }
    return {claimed, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    skill.resize(n);
    for (int i = 0; i < n; ++i) {
        skill[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.actual > jury.actual) {
        quitf(_wa,
              "jury has better answer: jury=%lld participant=%lld",
              jury.actual,
              participant.actual);
    }
    if (participant.actual < jury.actual) {
        quitf(_fail,
              "participant found better answer: jury=%lld participant=%lld",
              jury.actual,
              participant.actual);
    }
    quitf(_ok, "answer=%lld", participant.actual);
}

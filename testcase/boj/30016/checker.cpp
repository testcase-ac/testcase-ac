#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

int n, tLimit;
vector<vector<int>> scoreBySubject;
vector<int> fatiguePenalty;

struct Answer {
    long long score;
    vector<int> hours;
};

[[noreturn]] void invalid(InStream& stream, bool isJury, const char* format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (isJury) {
        quitf(_fail, "%s", buffer);
    }
    stream.quitf(_wa, "%s", buffer);
    __builtin_unreachable();
}

Answer readAnswer(InStream& stream, bool isJury) {
    long long claimedScore = stream.readLong(-1000000000000000LL, 1000000000000000LL, "score");
    stream.readEoln();

    vector<int> hours(n);
    int totalHours = 0;
    long long earned = 0;
    for (int i = 0; i < n; ++i) {
        hours[i] = stream.readInt(0, tLimit, format("A[%d]", i + 1).c_str());
        totalHours += hours[i];
        if (totalHours > tLimit) {
            invalid(stream, isJury, "total study time exceeds T: total=%d T=%d", totalHours, tLimit);
        }
        earned += scoreBySubject[i][hours[i]];
    }
    stream.readEoln();
    stream.readEof();

    long long actualScore = earned - fatiguePenalty[totalHours];
    if (claimedScore != actualScore) {
        invalid(stream, isJury, "claimed score %lld does not match schedule score %lld",
                claimedScore, actualScore);
    }

    return {actualScore, hours};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    tLimit = inf.readInt();

    scoreBySubject.assign(n, vector<int>(tLimit + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= tLimit; ++j) {
            scoreBySubject[i][j] = inf.readInt();
        }
    }

    fatiguePenalty.assign(tLimit + 1, 0);
    for (int j = 0; j <= tLimit; ++j) {
        fatiguePenalty[j] = inf.readInt();
    }

    Answer jury = readAnswer(ans, true);
    Answer participant = readAnswer(ouf, false);

    if (participant.score < jury.score) {
        quitf(_wa, "jury has better score: jury=%lld participant=%lld",
              jury.score, participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant found better score: jury=%lld participant=%lld",
              jury.score, participant.score);
    }

    quitf(_ok, "score=%lld", participant.score);
}

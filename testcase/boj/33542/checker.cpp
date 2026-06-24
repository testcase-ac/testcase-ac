#include "testlib.h"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

long long A, B;
int N;
vector<long long> leftScore, rightScore;

struct Answer {
    bool impossible;
    int leftTarget;
    int rightTarget;
    long long finalScore;
};

int parseTargetToken(InStream& stream, const string& token, const char* name) {
    char* end = nullptr;
    errno = 0;
    long value = strtol(token.c_str(), &end, 10);
    if (errno != 0 || end == token.c_str() || *end != '\0') {
        stream.quitf(_wa, "%s is not an integer: %s", name, token.c_str());
    }
    if (value < -1 || value > N || value == 0) {
        stream.quitf(_wa, "%s must be -1 or in [1, %d], found %ld", name, N, value);
    }
    return static_cast<int>(value);
}

long long finalScoreFor(int x, int y) {
    if (x == y) {
        return B;
    }

    long long added = 0;
    if (x != -1) {
        added += leftScore[x];
    }
    if (y != -1) {
        added += rightScore[y];
    }
    return B + added;
}

Answer readAnswer(InStream& stream) {
    string first = stream.readToken("[^\\s]+", "first token");

    if (first == "No") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after No");
        }
        return {true, -1, -1, -1};
    }

    int x = parseTargetToken(stream, first, "X");
    int y = stream.readInt(-1, N, "Y");
    if (y == 0) {
        stream.quitf(_wa, "Y must be -1 or in [1, %d], found 0", N);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after target pair");
    }

    return {false, x, y, finalScoreFor(x, y)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    A = inf.readLong();
    B = inf.readLong();
    N = inf.readInt();

    leftScore.assign(N + 1, 0);
    rightScore.assign(N + 1, 0);
    for (int i = 1; i <= N; ++i) {
        leftScore[i] = inf.readLong();
        rightScore[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both answers are No");
        }
        if (participant.finalScore > A) {
            quitf(_fail,
                  "participant found a winning pair while jury says No: X=%d Y=%d score=%lld",
                  participant.leftTarget,
                  participant.rightTarget,
                  participant.finalScore);
        }
        quitf(_wa,
              "jury says No, but participant pair does not win: X=%d Y=%d score=%lld",
              participant.leftTarget,
              participant.rightTarget,
              participant.finalScore);
    }

    if (jury.finalScore <= A) {
        quitf(_fail,
              "jury target pair does not win: X=%d Y=%d score=%lld A=%lld",
              jury.leftTarget,
              jury.rightTarget,
              jury.finalScore,
              A);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says No, but jury has a winning score %lld", jury.finalScore);
    }

    if (participant.finalScore <= A) {
        quitf(_wa,
              "participant target pair does not win: X=%d Y=%d score=%lld A=%lld",
              participant.leftTarget,
              participant.rightTarget,
              participant.finalScore,
              A);
    }

    if (participant.finalScore < jury.finalScore) {
        quitf(_fail,
              "participant found a better dramatic win: participant=%lld jury=%lld",
              participant.finalScore,
              jury.finalScore);
    }
    if (participant.finalScore > jury.finalScore) {
        quitf(_wa,
              "participant score is not minimal: participant=%lld jury=%lld",
              participant.finalScore,
              jury.finalScore);
    }

    quitf(_ok, "score=%lld", participant.finalScore);
}

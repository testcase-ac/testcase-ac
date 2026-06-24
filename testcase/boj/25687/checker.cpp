#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Fraction {
    long long num;
    long long den;
};

bool lessFraction(const Fraction& a, const Fraction& b) {
    return (__int128)a.num * b.den < (__int128)b.num * a.den;
}

bool equalFraction(const Fraction& a, const Fraction& b) {
    return (__int128)a.num * b.den == (__int128)b.num * a.den;
}

struct Answer {
    Fraction score;
};

int n;

void improveScore(const vector<int>& values, Fraction& score) {
    vector<int> sorted = values;
    sort(sorted.begin(), sorted.end());

    for (int i = 1; i < n; ++i) {
        Fraction candidate{sorted[i], sorted[i - 1]};
        if (lessFraction(candidate, score)) {
            score = candidate;
        }
    }
}

Answer readAnswer(InStream& stream) {
    const int maxValue = n * n;
    vector<vector<int>> matrix(n, vector<int>(n));
    vector<int> seen(maxValue + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = stream.readInt(1, maxValue, format("a[%d][%d]", i + 1, j + 1).c_str());
            if (seen[matrix[i][j]]) {
                stream.quitf(_wa, "value %d appears more than once", matrix[i][j]);
            }
            seen[matrix[i][j]] = 1;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after matrix");
    }

    Fraction score{maxValue, 1};
    for (int i = 0; i < n; ++i) {
        improveScore(matrix[i], score);
    }
    for (int j = 0; j < n; ++j) {
        vector<int> column(n);
        for (int i = 0; i < n; ++i) {
            column[i] = matrix[i][j];
        }
        improveScore(column, score);
    }

    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 2000, "N");
    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (lessFraction(participant.score, jury.score)) {
        quitf(_wa,
              "participant score is worse than jury score: participant=%lld/%lld jury=%lld/%lld",
              participant.score.num,
              participant.score.den,
              jury.score.num,
              jury.score.den);
    }
    if (equalFraction(participant.score, jury.score)) {
        quitf(_ok, "score=%lld/%lld", participant.score.num, participant.score.den);
    }

    quitf(_fail,
          "participant score is better than jury score: participant=%lld/%lld jury=%lld/%lld",
          participant.score.num,
          participant.score.den,
          jury.score.num,
          jury.score.den);
}

#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string firstDna, secondDna;

struct Answer {
    int claimedScore;
    int computedScore;
    string firstSub;
    string secondSub;
};

bool isDnaString(const string& value) {
    if (value.empty()) {
        return false;
    }
    for (char ch : value) {
        if (ch != 'A' && ch != 'C' && ch != 'G' && ch != 'T') {
            return false;
        }
    }
    return true;
}

bool isContiguousSubstring(const string& text, const string& candidate) {
    return text.find(candidate) != string::npos;
}

int similarityScore(const string& a, const string& b) {
    const int gapOrMismatch = -2;
    const int match = 3;
    const int n = (int)a.size();
    const int m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        dp[i][0] = dp[i - 1][0] + gapOrMismatch;
    }
    for (int j = 1; j <= m; ++j) {
        dp[0][j] = dp[0][j - 1] + gapOrMismatch;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int pairScore = (a[i - 1] == b[j - 1]) ? match : gapOrMismatch;
            dp[i][j] = max({
                dp[i - 1][j - 1] + pairScore,
                dp[i - 1][j] + gapOrMismatch,
                dp[i][j - 1] + gapOrMismatch,
            });
        }
    }
    return dp[n][m];
}

Answer readAnswer(InStream& stream) {
    int claimedScore = stream.readInt(-1000000, 1000000, "similarity score");
    string firstSub = stream.readToken("[ACGT]+", "first substring");
    string secondSub = stream.readToken("[ACGT]+", "second substring");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the third line");
    }

    if (!isDnaString(firstSub)) {
        stream.quitf(_wa, "first substring is not a non-empty DNA string");
    }
    if (!isDnaString(secondSub)) {
        stream.quitf(_wa, "second substring is not a non-empty DNA string");
    }
    if (!isContiguousSubstring(firstDna, firstSub)) {
        stream.quitf(_wa, "first substring '%s' is not contained in the first DNA sequence",
                     firstSub.c_str());
    }
    if (!isContiguousSubstring(secondDna, secondSub)) {
        stream.quitf(_wa, "second substring '%s' is not contained in the second DNA sequence",
                     secondSub.c_str());
    }

    int computedScore = similarityScore(firstSub, secondSub);
    if (claimedScore != computedScore) {
        stream.quitf(_wa, "claimed score %d does not match supplied substrings' score %d",
                     claimedScore, computedScore);
    }

    return {claimedScore, computedScore, firstSub, secondSub};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    firstDna = inf.readToken();
    int m = inf.readInt();
    secondDna = inf.readToken();
    (void)n;
    (void)m;

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.computedScore < jury.computedScore) {
        quitf(_wa, "jury has better score: jury=%d participant=%d",
              jury.computedScore, participant.computedScore);
    }
    if (participant.computedScore > jury.computedScore) {
        quitf(_fail, "participant found better score: jury=%d participant=%d",
              jury.computedScore, participant.computedScore);
    }
    quitf(_ok, "score=%d", participant.computedScore);
}

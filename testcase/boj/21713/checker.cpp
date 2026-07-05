#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <vector>

using namespace std;

int n, k, targetAverage;
vector<int> scores;

int parseScoreToken(InStream& stream, const char* name) {
    string token = stream.readToken();
    if (token.empty() || token.size() > 4 || !isdigit(token[0])) {
        stream.quitf(_wa, "%s=%s is not a valid score", name, token.c_str());
    }

    int whole = token[0] - '0';
    int cents = whole * 100;

    size_t dot = token.find('.');
    if (dot == string::npos) {
        if (token.size() != 1) {
            stream.quitf(_wa, "%s=%s is not a valid score", name, token.c_str());
        }
    } else {
        if (dot != 1 || token.find('.', dot + 1) != string::npos ||
            token.size() < dot + 2 || token.size() > dot + 3) {
            stream.quitf(_wa, "%s=%s is not a valid score", name, token.c_str());
        }
        for (size_t i = dot + 1; i < token.size(); ++i) {
            if (!isdigit(token[i])) {
                stream.quitf(_wa, "%s=%s is not a valid score", name, token.c_str());
            }
        }
        int first = token[dot + 1] - '0';
        int second = (dot + 2 < token.size()) ? token[dot + 2] - '0' : 0;
        cents += first * 10 + second;
    }

    if (cents < 100 || cents > 600) {
        stream.quitf(_wa, "%s=%s is outside the score range", name, token.c_str());
    }
    return cents;
}

int roundedAverageCents(long long sum, int count) {
    return int((2 * sum + count) / (2 * count));
}

struct Claim {
    vector<int> removed;
};

Claim readClaim(InStream& stream) {
    Claim claim;
    claim.removed.reserve(k + 2);

    map<int, int> available;
    for (int score : scores) {
        ++available[score];
    }

    for (int i = 0; i < k + 2; ++i) {
        int score = parseScoreToken(stream, format("score[%d]", i + 1).c_str());
        auto it = available.find(score);
        if (it == available.end() || it->second == 0) {
            stream.quitf(_wa, "score[%d]=%.2f is not available in the input multiset",
                         i + 1, score / 100.0);
        }
        --it->second;
        claim.removed.push_back(score);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the claimed scores");
    }

    vector<int> kept;
    kept.reserve(n - k - 2);
    for (const auto& [score, count] : available) {
        for (int i = 0; i < count; ++i) {
            kept.push_back(score);
        }
    }

    if (int(kept.size()) != n - k - 2) {
        stream.quitf(_wa, "wrong number of removed scores");
    }

    int minKept = *min_element(kept.begin(), kept.end());
    int maxKept = *max_element(kept.begin(), kept.end());

    bool hasErasedExtremes = false;
    for (int low = 0; low < int(claim.removed.size()); ++low) {
        if (claim.removed[low] > minKept) {
            continue;
        }
        for (int high = 0; high < int(claim.removed.size()); ++high) {
            if (low != high && claim.removed[high] >= maxKept) {
                hasErasedExtremes = true;
            }
        }
    }
    if (!hasErasedExtremes) {
        stream.quitf(_wa, "no two claimed scores can be the erased minimum and maximum");
    }

    long long sum = 0;
    for (int score : kept) {
        sum += score;
    }

    int average = roundedAverageCents(sum, int(kept.size()));
    if (average != targetAverage) {
        stream.quitf(_wa, "remaining average is %.2f, expected %.2f",
                     average / 100.0, targetAverage / 100.0);
    }

    sort(claim.removed.begin(), claim.removed.end());
    return claim;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    k = inf.readInt();

    scores.resize(n);
    for (int i = 0; i < n; ++i) {
        scores[i] = parseScoreToken(inf, format("input score[%d]", i + 1).c_str());
    }
    targetAverage = parseScoreToken(inf, "target average");

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    quitf(_ok, "valid removed-score claim with %d scores", int(participant.removed.size()));
}

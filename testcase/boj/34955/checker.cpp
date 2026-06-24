#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

struct Claim {
    long long score;
};

int n, m;
multiset<long long> initialBaits;
multiset<long long> initialPond;

[[noreturn]] void invalid(InStream& stream, bool jury, const string& message) {
    stream.quitf(jury ? _fail : _wa, "%s", message.c_str());
}

long long readValueToken(InStream& stream, bool jury, const string& token, const string& name) {
    if (token.empty()) {
        invalid(stream, jury, name + " is empty");
    }
    int start = token[0] == '-';
    if (start == 1 && token.size() == 1) {
        invalid(stream, jury, name + " is not an integer");
    }
    for (int i = start; i < (int)token.size(); ++i) {
        if (!isdigit((unsigned char)token[i])) {
            invalid(stream, jury, name + " is not an integer");
        }
    }

    try {
        size_t used = 0;
        long long value = stoll(token, &used);
        if (used != token.size()) {
            invalid(stream, jury, name + " is not an integer");
        }
        return value;
    } catch (...) {
        invalid(stream, jury, name + " is outside 64-bit integer range");
    }
}

Claim readClaim(InStream& stream, bool jury) {
    const int maxActions = 1000000;
    int q = stream.readInt(0, maxActions, "Q");
    stream.readEoln();

    multiset<long long> baits = initialBaits;
    multiset<long long> pond = initialPond;
    multiset<long long> heldFish;

    for (int actionIndex = 1; actionIndex <= q; ++actionIndex) {
        string line = stream.readLine();
        istringstream iss(line);

        string kind;
        if (!(iss >> kind)) {
            invalid(stream, jury, format("action %d is empty", actionIndex));
        }

        if (kind == "fish") {
            vector<long long> usedBaits;
            string token;
            long long sum = 0;
            while (iss >> token) {
                long long value = readValueToken(
                    stream, jury, token, format("bait value in action %d", actionIndex));
                if (value <= 0) {
                    invalid(stream, jury,
                            format("bait value %lld in action %d is not positive", value,
                                   actionIndex));
                }
                if (sum > LLONG_MAX - value) {
                    invalid(stream, jury, format("bait sum overflows in action %d", actionIndex));
                }
                sum += value;
                usedBaits.push_back(value);
            }
            if (usedBaits.empty()) {
                invalid(stream, jury, format("fish action %d uses no bait", actionIndex));
            }

            for (long long value : usedBaits) {
                auto it = baits.find(value);
                if (it == baits.end()) {
                    invalid(stream, jury,
                            format("fish action %d uses unavailable bait value %lld", actionIndex,
                                   value));
                }
                baits.erase(it);
            }

            auto caught = pond.upper_bound(sum);
            if (caught != pond.end()) {
                heldFish.insert(*caught);
                pond.erase(caught);
            }
        } else if (kind == "bait") {
            string token;
            if (!(iss >> token)) {
                invalid(stream, jury, format("bait action %d has no fish value", actionIndex));
            }
            long long value =
                readValueToken(stream, jury, token, format("fish value in action %d", actionIndex));
            if (value <= 0) {
                invalid(stream, jury,
                        format("fish value %lld in action %d is not positive", value, actionIndex));
            }
            string extra;
            if (iss >> extra) {
                invalid(stream, jury, format("bait action %d has extra tokens", actionIndex));
            }

            auto it = heldFish.find(value);
            if (it == heldFish.end()) {
                invalid(stream, jury,
                        format("bait action %d uses unavailable fish value %lld", actionIndex,
                               value));
            }
            heldFish.erase(it);
            baits.insert(value);
        } else {
            invalid(stream, jury, format("action %d has unknown operation '%s'", actionIndex,
                                         kind.c_str()));
        }
    }

    long long computedScore = 0;
    for (long long value : heldFish) {
        if (computedScore > LLONG_MAX - value) {
            invalid(stream, jury, "final score overflows 64-bit integer range");
        }
        computedScore += value;
    }

    long long reportedScore = stream.readLong(0LL, LLONG_MAX, "S");
    stream.readEoln();
    stream.readEof();

    if (reportedScore != computedScore) {
        invalid(stream, jury,
                format("reported score %lld does not match simulated score %lld", reportedScore,
                       computedScore));
    }
    return {computedScore};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    for (int i = 0; i < n; ++i) {
        initialBaits.insert(inf.readLong());
    }
    for (int i = 0; i < m; ++i) {
        initialPond.insert(inf.readLong());
    }

    Claim jury = readClaim(ans, true);
    Claim participant = readClaim(ouf, false);

    if (participant.score < jury.score) {
        quitf(_wa, "jury has better score: jury=%lld participant=%lld", jury.score,
              participant.score);
    }
    if (participant.score > jury.score) {
        quitf(_fail, "participant found better score: jury=%lld participant=%lld", jury.score,
              participant.score);
    }
    quitf(_ok, "score=%lld", participant.score);
}

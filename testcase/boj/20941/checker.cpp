#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int n;
int totalOrders;
string firstOrder;

int parseOrder(const string& order) {
    int value = 0;
    for (char c : order) {
        value = value * 2 + (c - '0');
    }
    return value;
}

struct Claim {
    long long score;
};

Claim readClaim(InStream& stream) {
    vector<unsigned char> seen(totalOrders, 0);
    string previous;
    long long score = 0;

    for (int i = 0; i < totalOrders; ++i) {
        string current = stream.readToken(format("[01]{%d}", n), format("order[%d]", i + 1).c_str());
        stream.readEoln();

        if (i == 0 && current != firstOrder) {
            stream.quitf(_wa, "first order is %s instead of %s", current.c_str(), firstOrder.c_str());
        }

        int value = parseOrder(current);
        if (seen[value]) {
            stream.quitf(_wa, "order %s appears more than once", current.c_str());
        }
        seen[value] = 1;

        if (i > 0) {
            int diff = parseOrder(previous) ^ value;
            score += n - __builtin_popcount(static_cast<unsigned int>(diff));
        }
        previous = current;
    }

    stream.readEof();
    return {score};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    firstOrder = inf.readToken();
    totalOrders = 1 << n;

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (participant.score > jury.score) {
        quitf(_wa, "participant score %lld is worse than jury score %lld",
              participant.score, jury.score);
    }
    if (participant.score < jury.score) {
        quitf(_fail, "participant score %lld is better than jury score %lld",
              participant.score, jury.score);
    }

    quitf(_ok, "score %lld", participant.score);
}

#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

const int MAX_OPERATIONS = 10000;

struct Claim {
    int operations;
};

Claim readClaim(InStream& stream, const string& target) {
    string current = target;
    sort(current.begin(), current.end());

    const int n = int(target.size());
    int operations = 0;

    while (!stream.seekEof()) {
        if (operations == MAX_OPERATIONS) {
            stream.quitf(_wa, "more than %d operations", MAX_OPERATIONS);
        }

        int a = stream.readInt(1, n, format("A_%d", operations + 1).c_str());
        int b = stream.readInt(1, n, format("B_%d", operations + 1).c_str());
        ++operations;

        --a;
        --b;
        if (current[a] >= current[b]) {
            swap(current[a], current[b]);
        }
    }

    if (current != target) {
        stream.quitf(_wa, "operations produce '%s' instead of '%s'",
                     current.c_str(), target.c_str());
    }

    return {operations};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string target = inf.readToken("[a-z]{0,1000}", "S");

    Claim jury = readClaim(ans, target);
    Claim participant = readClaim(ouf, target);

    quitf(_ok, "accepted %d operations, jury used %d",
          participant.operations, jury.operations);
}

#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    int adjectiveCount = -1;
    vector<set<string>> adjectivesByPosition;
    set<vector<string>> missingCows;

    for (int i = 0; i < n; ++i) {
        inf.readToken("Farmer", "Farmer");
        inf.readSpace();
        inf.readToken("John", "John");
        inf.readSpace();
        inf.readToken("has", "has");
        inf.readSpace();
        inf.readToken("no", "no");
        inf.readSpace();

        vector<string> cow;
        while (true) {
            string token = inf.readToken("[a-z.]{1,11}", "word");
            if (token == "cow.") {
                break;
            }

            ensuref(cow.size() < 30, "line %d has more than 30 adjectives", i + 2);
            ensuref(token.size() <= 10, "line %d adjective %d is too long", i + 2, int(cow.size()) + 1);
            ensuref(token.find('.') == string::npos, "line %d adjective %d contains a period", i + 2, int(cow.size()) + 1);
            cow.push_back(token);
            inf.readSpace();
        }
        inf.readEoln();

        ensuref(cow.size() >= 2, "line %d has fewer than 2 adjectives", i + 2);
        if (adjectiveCount == -1) {
            adjectiveCount = int(cow.size());
            adjectivesByPosition.resize(adjectiveCount);
        } else {
            ensuref(int(cow.size()) == adjectiveCount,
                    "line %d has %d adjectives, expected %d",
                    i + 2, int(cow.size()), adjectiveCount);
        }

        for (int j = 0; j < adjectiveCount; ++j) {
            adjectivesByPosition[j].insert(cow[j]);
        }

        // CHECK: The statement describes N listed missing cows; reject duplicate descriptions.
        ensuref(missingCows.insert(cow).second, "duplicate missing cow description on line %d", i + 2);
    }

    long long combinations = 1;
    for (int i = 0; i < adjectiveCount; ++i) {
        combinations *= int(adjectivesByPosition[i].size());
        ensuref(combinations <= 1000000000LL + n,
                "total adjective combinations exceed the stated cow-count guarantee");
    }

    long long ownedCows = combinations - n;
    ensuref(ownedCows <= 1000000000LL, "Farmer John has more than 1000000000 cows");
    ensuref(k <= ownedCows, "K=%lld exceeds the number of owned cows %lld", k, ownedCows);

    inf.readEof();
}

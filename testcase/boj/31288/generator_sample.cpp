#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> primes = {
        "2",
        "3",
        "5",
        "7",
        "89",
        "211",
        "1151",
        "10193",
        "100237",
        "1000273",
        "10000303",
        "100000357",
        "1000000403",
        "100000000447",
        "100000000000601",
        "10000000000000000741",
        "1000000000000000000000931",
        "100000000000000000000000001131",
        "1000000000000000000000000000000000001543",
        "100000000000000000000000000000000000000000000000000000002251",
        "10000000000000000000000000000000000000000000000000000000000000000000000000003069",
        "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000003841",
    };

    vector<string> cases;
    int mode = rnd.next(0, 2);

    if (mode == 0) {
        cases.push_back(rnd.any(primes));
    } else if (mode == 1) {
        int count = rnd.next(2, 12);
        for (int i = 0; i < count; ++i) {
            cases.push_back(primes[rnd.next(0, 7)]);
        }
    } else {
        shuffle(primes.begin(), primes.end());
        int count = rnd.next(2, 10);
        int sumN = 0;
        for (const string& prime : primes) {
            if (sumN + static_cast<int>(prime.size()) > 3545) {
                continue;
            }
            cases.push_back(prime);
            sumN += static_cast<int>(prime.size());
            if (static_cast<int>(cases.size()) == count) {
                break;
            }
        }
    }

    println(static_cast<int>(cases.size()));
    for (const string& prime : cases) {
        println(static_cast<int>(prime.size()), prime);
    }

    return 0;
}

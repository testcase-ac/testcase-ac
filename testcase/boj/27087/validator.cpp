#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41,
                             43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100, "A");
        inf.readSpace();
        inf.readInt(1, 100, "B");
        inf.readSpace();
        inf.readInt(1, 100, "C");
        inf.readSpace();
        int p = inf.readInt(2, 97, "p");
        inf.readEoln();

        ensuref(primes.count(p) == 1, "p must be prime, got %d", p);
    }

    inf.readEof();
    return 0;
}

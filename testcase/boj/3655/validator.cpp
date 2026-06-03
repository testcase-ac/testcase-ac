#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 25000, "n");
        inf.readEoln();

        string queue = inf.readToken("[A-Za-z0-9]{1,25000}", "queue");
        ensuref((int)queue.size() == n, "queue length must be n: expected %d, found %d", n,
                (int)queue.size());
        inf.readEoln();
    }

    inf.readEof();
}

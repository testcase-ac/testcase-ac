#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 499999, "N");
    inf.readEoln();

    long long totalInputLength = to_string(n).size() + 1;
    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        string initial = inf.readToken("[a-z]+", "initial");
        inf.readSpace();
        string target = inf.readToken("[a-z]+", "target");
        inf.readEoln();

        ensuref(initial.size() >= target.size(),
                "initial string shorter than target string: initial length %d, target length %d",
                int(initial.size()), int(target.size()));

        totalInputLength += initial.size() + 1 + target.size() + 1;
        ensuref(totalInputLength < 500000,
                "total input length must be less than 500000 characters, got %lld",
                totalInputLength);
    }

    inf.readEof();
}

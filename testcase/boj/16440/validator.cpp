#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 200000, "N");
    inf.readEoln();
    ensuref(n % 4 == 0, "N must be divisible by 4: %d", n);

    string cake = inf.readToken("[sk]{4,200000}", "cake");
    inf.readEoln();
    ensuref(static_cast<int>(cake.size()) == n,
            "cake length must be N: length=%d, N=%d",
            static_cast<int>(cake.size()), n);

    int strawberries = 0;
    for (char fruit : cake) {
        if (fruit == 's') {
            ++strawberries;
        }
    }
    ensuref(strawberries == n / 2,
            "number of strawberries must be N/2: strawberries=%d, N=%d",
            strawberries, n);

    inf.readEof();
}

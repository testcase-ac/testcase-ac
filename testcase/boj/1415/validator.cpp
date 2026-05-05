#include "testlib.h"
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<int> prices;
    for (int i = 0; i < N; ++i) {
        int price = inf.readInt(0, 10000, "price");
        inf.readEoln();
        prices.push_back(price);
    }

    // No further global constraints are implied by the problem statement.
    // (No requirement for distinct prices, no requirement for at least one nonzero price, etc.)

    inf.readEof();
}

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(4, 10, "n");
    inf.readEoln();

    // Read k
    int k = inf.readInt(2, 4, "k");
    inf.readEoln();
    ensuref(k <= n, "k must be <= n, but k=%d and n=%d", k, n);

    // Read the card values
    vector<int> cards(n);
    for (int i = 0; i < n; i++) {
        cards[i] = inf.readInt(1, 99, "card_value");
        inf.readEoln();
    }

    // No further global constraints (duplicates allowed, always possible to choose k <= n)
    inf.readEof();
    return 0;
}

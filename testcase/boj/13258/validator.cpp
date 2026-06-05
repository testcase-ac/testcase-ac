#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readEoln();

    vector<int> balances = inf.readInts(n, 0, 100000, "balance");
    inf.readEoln();

    long long totalBalance = 0;
    for (int balance : balances) {
        totalBalance += balance;
    }
    ensuref(totalBalance > 0, "at least one balance must be positive");

    inf.readInt(1, 1000, "J");
    inf.readEoln();

    inf.readInt(1, 1000, "C");
    inf.readEoln();

    inf.readEof();
}

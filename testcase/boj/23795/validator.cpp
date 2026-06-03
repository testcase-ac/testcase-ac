#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long sum = 0;
    int values = 0;

    while (true) {
        // CHECK: The statement does not give a minimum number of bets, so a
        // leading -1 is accepted as the empty sequence of bets.
        long long money = inf.readLong(-1LL, 2147483647LL, "money");
        inf.readEoln();
        ++values;

        ensuref(values < 2000, "number of input values must be less than 2000");

        if (money == -1) {
            break;
        }

        ensuref(money >= 1, "bet amount must be positive, got %lld", money);
        sum += money;
        ensuref(sum <= 2147483647LL, "sum of bets exceeds 2147483647");
    }

    inf.readEof();
    return 0;
}

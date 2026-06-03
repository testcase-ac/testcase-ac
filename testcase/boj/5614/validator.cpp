#include "testlib.h"

#include <map>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement bounds product names, order counts, and totals, but
    // not the number of order records. Cap records to keep validation practical.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    map<string, long long> totals;
    for (int i = 0; i < n; ++i) {
        string product = inf.readToken("[A-Z]{1,5}", "product");
        inf.readSpace();
        int quantity = inf.readInt(1, 100000000, "quantity");
        inf.readEoln();

        long long total = totals[product] + quantity;
        ensuref(total <= 100000000LL,
                "total quantity for product %s exceeds 10^8 at row %d",
                product.c_str(), i + 1);
        totals[product] = total;
    }

    inf.readEof();
}

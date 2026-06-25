#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int scenarios = 0;
    int totalProductRows = 0;
    int totalRequestedProducts = 0;

    while (true) {
        int n = inf.readInt(0, 50, "N");
        inf.readEoln();
        if (n == 0) {
            break;
        }

        ++scenarios;
        // CHECK: The statement gives no scenario count limit; this local cap keeps
        // validation finite while still allowing very large multi-scenario files.
        ensuref(scenarios <= 100000, "too many scenarios: %d", scenarios);

        set<string> products;
        for (int i = 1; i <= n; ++i) {
            // CHECK: Product names are only specified as non-space strings of up to
            // 20 characters, so accept any visible ASCII token without spaces.
            string name = inf.readToken("[!-~]{1,20}", "product_name");
            ensuref(products.insert(name).second,
                    "duplicate product name in scenario %d: %s",
                    scenarios,
                    name.c_str());
            inf.readSpace();
            int points = inf.readInt(0, 1000, "points");
            inf.readSpace();
            int days = inf.readInt(0, 100, "days");
            inf.readEoln();

            (void)points;
            (void)days;
            ++totalProductRows;
            // CHECK: Derived from the default 100000 scenario cap and N <= 50.
            ensuref(totalProductRows <= 5000000,
                    "too many product rows: %d",
                    totalProductRows);
        }

        int c = inf.readInt(1, 500, "C");
        inf.readEoln();

        for (int customer = 1; customer <= c; ++customer) {
            int customerNumber = inf.readInt(0, 2147483647, "customer_number");
            inf.readSpace();
            int p = inf.readInt(1, n, "P");
            inf.readSpace();
            int maxDays = inf.readInt(1, 99, "M");
            inf.readEoln();

            (void)customerNumber;
            (void)maxDays;
            for (int i = 1; i <= p; ++i) {
                string requested = inf.readToken("[!-~]{1,20}", "requested_product");
                inf.readEoln();
                ensuref(products.count(requested) == 1,
                        "unknown requested product in scenario %d customer %d: %s",
                        scenarios,
                        customer,
                        requested.c_str());

                ++totalRequestedProducts;
                // CHECK: The statement gives no total request limit; this local cap
                // follows the repository default for primarily token-based inputs.
                ensuref(totalRequestedProducts <= 5000000,
                        "too many requested products: %d",
                        totalRequestedProducts);
            }
        }
    }

    inf.readEof();
}

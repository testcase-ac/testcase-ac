#include "testlib.h"

#include <map>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(2, 200000, "Q");
    inf.readEoln();

    map<int, int> count_by_price;
    bool has_report_query = false;

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 3, "query_type");

        if (type == 3) {
            has_report_query = true;
            inf.readEoln();
            continue;
        }

        inf.readSpace();
        int price = inf.readInt(1000, 1000000, "S");
        inf.readEoln();

        if (type == 1) {
            ++count_by_price[price];
        } else {
            auto it = count_by_price.find(price);
            ensuref(it != count_by_price.end() && it->second > 0,
                    "query %d removes absent price %d", i, price);
            --it->second;
            if (it->second == 0) {
                count_by_price.erase(it);
            }
        }
    }

    ensuref(has_report_query, "there must be at least one type 3 query");
    inf.readEof();
}

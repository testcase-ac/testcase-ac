#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50000, "n");
    inf.readEoln();

    int update_count = 0;
    int sum_query_count = 0;
    vector<int> sum_query_versions;

    for (int q = 1; q <= n; ++q) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        int i = inf.readInt(1, 1000000000, "i");
        inf.readSpace();
        int j = inf.readInt(i, 1000000000, "j");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(-100000, 100000, "k");
            ++update_count;
        } else {
            int k = inf.readInt(1, n, "k");
            sum_query_versions.push_back(k);
            ++sum_query_count;
        }
        inf.readEoln();
    }

    ensuref(update_count >= 1, "at least one type 1 query is required");
    ensuref(sum_query_count >= 1, "at least one type 2 query is required");

    for (int k : sum_query_versions) {
        ensuref(k <= update_count,
                "type 2 query refers to update %d, but only %d type 1 queries exist",
                k,
                update_count);
    }

    inf.readEof();
}

#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 10, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10, "M");
    inf.readEoln();
    ensuref(N % 2 == 0, "N must be even, got %d", N);

    // Read registrations until sentinel "0 0"
    set<pair<int,string>> seen;
    int reg_cnt = 0;
    while (true) {
        // read class index, allow 0 for sentinel
        int c = inf.readInt(0, N, "class_i");
        inf.readSpace();
        if (c == 0) {
            // sentinel line: second token must be 0
            int mz = inf.readInt(0, 0, "end_M");
            (void)mz; // always 0
            inf.readEoln();
            break;
        }
        // normal registration
        string name = inf.readToken("[a-z]{1,15}", "name_i");
        inf.readEoln();

        // uniqueness check
        ensuref(!seen.count({c, name}),
                "Duplicate registration for class %d name '%s'",
                c, name.c_str());
        seen.insert({c, name});

        // count registrations
        reg_cnt++;
        ensuref(reg_cnt <= 500,
                "Too many registrations: %d (max 500)", reg_cnt);
    }

    inf.readEof();
    return 0;
}

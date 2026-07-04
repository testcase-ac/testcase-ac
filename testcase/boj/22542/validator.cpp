#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int dataset = 1;
    while (true) {
        int n = inf.readInt(0, 50, "N");
        inf.readEoln();
        if (n == 0) {
            inf.readEof();
            return 0;
        }

        setTestCase(dataset++);

        set<string> names;
        for (int i = 1; i <= n; ++i) {
            string name = inf.readToken("[a-z]{1,20}", "L_i");
            ensuref(names.insert(name).second,
                    "duplicate crop name in dataset: %s", name.c_str());

            inf.readSpace();
            inf.readInt(1, 100, "P_i");
            inf.readSpace();
            inf.readInt(1, 100, "A_i");
            inf.readSpace();
            inf.readInt(1, 100, "B_i");
            inf.readSpace();
            inf.readInt(1, 100, "C_i");
            inf.readSpace();
            inf.readInt(1, 100, "D_i");
            inf.readSpace();
            inf.readInt(1, 100, "E_i");
            inf.readSpace();
            inf.readInt(1, 100, "F_i");
            inf.readSpace();
            inf.readInt(1, 100, "S_i");
            inf.readSpace();
            inf.readInt(1, 5, "M_i");
            inf.readEoln();
        }
    }
}

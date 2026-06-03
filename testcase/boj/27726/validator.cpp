#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    int m1 = inf.readInt(1, 100000, "M_1");
    inf.readSpace();
    int m2 = inf.readInt(1, 100000, "M_2");
    inf.readSpace();
    int m3 = inf.readInt(1, 100000, "M_3");
    inf.readEoln();

    int counts[3] = {m1, m2, m3};
    for (int study = 0; study < 3; ++study) {
        setTestCase(study + 1);
        for (int i = 0; i < counts[study]; ++i) {
            int a = inf.readInt(1, n, "a");
            inf.readSpace();
            int b = inf.readInt(1, n, "b");
            inf.readEoln();

            ensuref(a != b, "agreement %d in study %d has equal endpoints %d", i + 1,
                    study + 1, a);
        }
    }

    inf.readEof();
}

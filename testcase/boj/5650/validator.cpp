#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const double maxPrice = 1000000000.0;
    const double maxGrowthFactor = 10.0;
    const int maxFractionDigits = 12;

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        // CHECK: the statement gives no upper bound or precision for P_j.
        // Cap prices and fractional digits to keep inputs finite and inspectable.
        double price = inf.readStrictDouble(0.0, maxPrice, 0, maxFractionDigits, "P_j");
        ensuref(price > 0.0, "P_%d must be positive", i);
        inf.readSpace();

        // CHECK: the statement only says R_j > 1. Cap growth factors and
        // fractional digits to avoid astronomically large numeric instances.
        double growthFactor = inf.readStrictDouble(1.0, maxGrowthFactor, 0, maxFractionDigits, "R_j");
        ensuref(growthFactor > 1.0, "R_%d must be greater than 1", i);
        inf.readEoln();
    }

    inf.readEof();
}

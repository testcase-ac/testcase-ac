#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    long long totalIngredients = 0;
    for (int i = 1; i <= m; ++i) {
        int k = inf.readInt(1, n - 1, "k_i");
        totalIngredients += k;
        ensuref(totalIngredients <= 400000,
                "sum of k_i exceeds 400000 at recipe %d", i);

        vector<int> ingredients(k);
        for (int j = 0; j < k; ++j) {
            inf.readSpace();
            ingredients[j] = inf.readInt(1, n, "x_ij");
        }

        inf.readSpace();
        int result = inf.readInt(1, n, "r_i");
        inf.readEoln();

        for (int j = 0; j < k; ++j) {
            ensuref(ingredients[j] != result,
                    "ingredient equals result at recipe %d ingredient %d: %d",
                    i, j + 1, result);
        }
        // CHECK: The statement does not require ingredients inside one recipe
        // to be distinct, so duplicate x_ij values are accepted.
    }

    int l = inf.readInt(1, n - 1, "l");
    inf.readEoln();

    vector<bool> seen(n + 1, false);
    for (int i = 1; i <= l; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        int y = inf.readInt(1, n, "y_i");
        ensuref(!seen[y], "duplicate initial potion type at position %d: %d", i, y);
        seen[y] = true;
    }
    inf.readEoln();

    inf.readEof();
}

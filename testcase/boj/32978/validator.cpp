#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    set<string> ingredients;
    for (int i = 0; i < n; ++i) {
        string ingredient = inf.readToken("[A-Za-z]{1,20}", "ingredient");
        ensuref(ingredients.insert(ingredient).second,
                "duplicate ingredient at index %d: %s", i + 1, ingredient.c_str());
        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    set<string> used;
    for (int i = 0; i < n - 1; ++i) {
        string ingredient = inf.readToken("[A-Za-z]{1,20}", "used_ingredient");
        ensuref(ingredients.count(ingredient) == 1,
                "used ingredient at index %d is not in original list: %s", i + 1,
                ingredient.c_str());
        ensuref(used.insert(ingredient).second,
                "duplicate used ingredient at index %d: %s", i + 1, ingredient.c_str());
        if (i + 1 == n - 1) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}

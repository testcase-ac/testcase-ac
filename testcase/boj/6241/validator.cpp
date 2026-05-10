#include "testlib.h"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, F, D
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int F = inf.readInt(1, 100, "F");
    inf.readSpace();
    int D = inf.readInt(1, 100, "D");
    inf.readEoln();

    // To check for duplicate foods/drinks per cow
    for (int cow = 1; cow <= N; ++cow) {
        int Fi = inf.readInt(1, F, "F_i");
        inf.readSpace();
        int Di = inf.readInt(1, D, "D_i");

        // Check that Fi + Di <= F + D (trivial, but for sanity)
        ensuref(Fi >= 1 && Fi <= F, "Cow %d: F_i out of range: %d", cow, Fi);
        ensuref(Di >= 1 && Di <= D, "Cow %d: D_i out of range: %d", cow, Di);

        vector<int> foods;
        vector<int> drinks;

        // Read foods
        for (int j = 0; j < Fi; ++j) {
            inf.readSpace();
            int food = inf.readInt(1, F, "food");
            foods.push_back(food);
        }
        // Check for duplicate foods
        sort(foods.begin(), foods.end());
        for (int j = 1; j < Fi; ++j) {
            ensuref(foods[j] != foods[j-1], "Cow %d: duplicate food %d in preference list", cow, foods[j]);
        }

        // Read drinks
        for (int j = 0; j < Di; ++j) {
            inf.readSpace();
            int drink = inf.readInt(1, D, "drink");
            drinks.push_back(drink);
        }
        // Check for duplicate drinks
        sort(drinks.begin(), drinks.end());
        for (int j = 1; j < Di; ++j) {
            ensuref(drinks[j] != drinks[j-1], "Cow %d: duplicate drink %d in preference list", cow, drinks[j]);
        }

        inf.readEoln();
    }

    inf.readEof();
}

#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int F = inf.readInt(1, 100, "F");
    inf.readSpace();
    int D = inf.readInt(1, 100, "D");
    inf.readEoln();

    for (int cow = 1; cow <= N; ++cow) {
        int Fi = inf.readInt(0, F, "F_i");
        inf.readSpace();
        int Di = inf.readInt(0, D, "D_i");

        vector<int> foods;
        vector<int> drinks;

        for (int j = 0; j < Fi; ++j) {
            inf.readSpace();
            int food = inf.readInt(1, F, "food");
            foods.push_back(food);
        }
        sort(foods.begin(), foods.end());
        for (int j = 1; j < Fi; ++j) {
            ensuref(foods[j] != foods[j-1], "Cow %d: duplicate food %d in preference list", cow, foods[j]);
        }

        for (int j = 0; j < Di; ++j) {
            inf.readSpace();
            int drink = inf.readInt(1, D, "drink");
            drinks.push_back(drink);
        }
        sort(drinks.begin(), drinks.end());
        for (int j = 1; j < Di; ++j) {
            ensuref(drinks[j] != drinks[j-1], "Cow %d: duplicate drink %d in preference list", cow, drinks[j]);
        }

        inf.readEoln();
    }

    inf.readEof();
}

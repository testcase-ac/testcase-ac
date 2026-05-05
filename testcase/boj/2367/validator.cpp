#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, K, D
    int N = inf.readInt(3, 200, "N");
    inf.readSpace();
    int K = inf.readInt(1, 5, "K");
    inf.readSpace();
    int D = inf.readInt(5, 100, "D");
    inf.readEoln();

    // Read dish limits
    vector<int> dish_limit = inf.readInts(D, 0, N, "dish_limit");
    inf.readEoln();

    // Validate dish_limit: each value is 0 <= x <= N
    for (int i = 0; i < D; ++i) {
        ensuref(dish_limit[i] <= N, "dish_limit[%d]=%d > N=%d", i+1, dish_limit[i], N);
        ensuref(dish_limit[i] >= 0, "dish_limit[%d]=%d < 0", i+1, dish_limit[i]);
    }

    // For each person, read their skills
    vector< set<int> > person_skills(N);
    for (int i = 0; i < N; ++i) {
        int Z = inf.readInt(1, D, "Z");
        inf.readSpace();
        vector<int> skills = inf.readInts(Z, 1, D, "skill");
        inf.readEoln();

        set<int> skillset;
        for (int j = 0; j < Z; ++j) {
            int dish = skills[j];
            ensuref(1 <= dish && dish <= D, "Person %d: skill %d = %d out of range [1, D=%d]", i+1, j+1, dish, D);
            ensuref(skillset.count(dish) == 0, "Person %d: duplicate dish %d in skill list", i+1, dish);
            skillset.insert(dish);
        }
        person_skills[i] = skillset;
    }

    inf.readEof();
}

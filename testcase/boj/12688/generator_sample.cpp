#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Animal {
    int h;
    int w;
    string label;
};

int clampCoord(int x) {
    return max(1, min(1000000, x));
}

Animal makeAnimal(int h, int w, const string& label) {
    return {clampCoord(h), clampCoord(w), label};
}

int nearValue(int x, int spread) {
    return clampCoord(x + rnd.next(-spread, spread));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(3, 7);
    println(cases);

    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 4);
        vector<Animal> known;
        vector<pair<int, int>> queries;

        if (mode == 0) {
            int h = rnd.next(1, 1000000);
            int w = rnd.next(1, 1000000);
            known.push_back(makeAnimal(h, w, "NOT BIRD"));
            known.push_back(makeAnimal(nearValue(h, 12), nearValue(w, 12), "NOT BIRD"));

            int q = rnd.next(3, 6);
            for (int i = 0; i < q; ++i) {
                queries.push_back({rnd.next(1, 1000000), rnd.next(1, 1000000)});
            }
        } else if (mode == 1) {
            int h = rnd.next(2, 999999);
            int w = rnd.next(2, 999999);
            known.push_back(makeAnimal(h, w, "BIRD"));
            known.push_back(makeAnimal(h + rnd.next(1, 20), w, "NOT BIRD"));
            known.push_back(makeAnimal(h, w + rnd.next(1, 20), "NOT BIRD"));

            queries.push_back({h, w});
            queries.push_back({nearValue(h, 1), w});
            queries.push_back({h, nearValue(w, 1)});
            queries.push_back({rnd.next(1, 1000000), rnd.next(1, 1000000)});
        } else if (mode == 2) {
            int lowH = rnd.next(1, 999900);
            int highH = rnd.next(lowH, min(1000000, lowH + rnd.next(0, 80)));
            int lowW = rnd.next(1, 999900);
            int highW = rnd.next(lowW, min(1000000, lowW + rnd.next(0, 80)));

            known.push_back(makeAnimal(lowH, lowW, "BIRD"));
            known.push_back(makeAnimal(highH, lowW, "BIRD"));
            known.push_back(makeAnimal(lowH, highW, "BIRD"));
            known.push_back(makeAnimal(highH, highW, "BIRD"));

            known.push_back(makeAnimal(lowH - rnd.next(1, 15), rnd.next(lowW, highW), "NOT BIRD"));
            known.push_back(makeAnimal(rnd.next(lowH, highH), highW + rnd.next(1, 15), "NOT BIRD"));

            queries.push_back({rnd.next(lowH, highH), rnd.next(lowW, highW)});
            queries.push_back({clampCoord(lowH - 1), rnd.next(lowW, highW)});
            queries.push_back({rnd.next(lowH, highH), clampCoord(highW + 1)});
            queries.push_back({nearValue(lowH, 20), nearValue(highW, 20)});
        } else if (mode == 3) {
            int base = rnd.any(vector<int>{1, 999990});
            int lowH = base;
            int highH = clampCoord(base + rnd.next(0, 10));
            int lowW = rnd.any(vector<int>{1, 999990});
            int highW = clampCoord(lowW + rnd.next(0, 10));

            known.push_back(makeAnimal(lowH, lowW, "BIRD"));
            known.push_back(makeAnimal(highH, highW, "BIRD"));
            known.push_back(makeAnimal(clampCoord(highH + 1), highW, "NOT BIRD"));
            known.push_back(makeAnimal(highH, clampCoord(highW + 1), "NOT BIRD"));

            queries.push_back({lowH, lowW});
            queries.push_back({highH, highW});
            queries.push_back({clampCoord(highH + 1), highW});
            queries.push_back({1000000, 1000000});
        } else {
            int birdCount = rnd.next(1, 8);
            int h = rnd.next(20, 999980);
            int w = rnd.next(20, 999980);
            for (int i = 0; i < birdCount; ++i) {
                known.push_back(makeAnimal(nearValue(h, 30), nearValue(w, 30), "BIRD"));
            }

            int notCount = rnd.next(1, 8);
            for (int i = 0; i < notCount; ++i) {
                int side = rnd.next(0, 3);
                int nh = h + (side == 0 ? -60 : side == 1 ? 60 : rnd.next(-50, 50));
                int nw = w + (side == 2 ? -60 : side == 3 ? 60 : rnd.next(-50, 50));
                known.push_back(makeAnimal(nh, nw, "NOT BIRD"));
            }

            int q = rnd.next(4, 9);
            for (int i = 0; i < q; ++i) {
                queries.push_back({nearValue(h, 80), nearValue(w, 80)});
            }
        }

        shuffle(known.begin(), known.end());
        shuffle(queries.begin(), queries.end());

        println(static_cast<int>(known.size()));
        for (const Animal& animal : known) {
            cout << animal.h << ' ' << animal.w << ' ' << animal.label << '\n';
        }

        println(static_cast<int>(queries.size()));
        for (auto [h, w] : queries) {
            println(h, w);
        }
    }

    return 0;
}

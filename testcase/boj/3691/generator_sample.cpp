#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Component {
    string type;
    string name;
    int price;
    int quality;
};

string id(char prefix, int x) {
    return string(1, prefix) + to_string(x);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tc = rnd.next(3, 8);
    println(tc);

    for (int t = 0; t < tc; ++t) {
        int mode = rnd.next(0, 4);
        int typeCount = rnd.next(1, mode == 4 ? 12 : 6);
        vector<int> perType(typeCount);
        int n = 0;

        for (int i = 0; i < typeCount; ++i) {
            if (mode == 1) {
                perType[i] = rnd.next(1, 2);
            } else if (mode == 4) {
                perType[i] = rnd.next(3, 12);
            } else {
                perType[i] = rnd.next(1, 5);
            }
            n += perType[i];
        }

        vector<Component> components;
        vector<int> cheapest(typeCount, 1000001);
        int nameSerial = 0;

        for (int type = 0; type < typeCount; ++type) {
            string typeName = id('T', type);
            int basePrice = (mode == 2 && rnd.next(0, 3) == 0) ? 0 : rnd.next(0, 80);
            int baseQuality = (mode == 2 && rnd.next(0, 4) == 0) ? 0 : rnd.next(0, 120);

            for (int j = 0; j < perType[type]; ++j) {
                int price;
                int quality;

                if (mode == 3 && j == perType[type] - 1) {
                    price = rnd.next(800000, 1000000);
                    quality = rnd.next(900000000, 1000000000);
                } else if (j == 0) {
                    price = basePrice;
                    quality = baseQuality;
                } else if (mode == 0) {
                    price = max(0, basePrice + rnd.next(-10, 80));
                    quality = max(0, baseQuality + rnd.next(-20, 160));
                } else if (mode == 1) {
                    price = basePrice + rnd.next(0, 4);
                    quality = baseQuality + rnd.next(0, 4);
                } else {
                    price = rnd.next(0, 200);
                    quality = rnd.next(0, 300);
                }

                if (mode == 4 && j % 3 == 2) {
                    price = min(1000000, basePrice + j * rnd.next(3, 11));
                    quality = max(0, baseQuality - rnd.next(0, 20));
                }

                components.push_back({typeName, id('C', nameSerial++), price, quality});
                if (price < cheapest[type]) {
                    cheapest[type] = price;
                }
            }
        }

        long long cheapestBuild = accumulate(cheapest.begin(), cheapest.end(), 0LL);
        long long budget;
        if (mode == 3) {
            budget = min(1000000000LL, cheapestBuild + rnd.next(0, 2000000));
        } else if (mode == 1) {
            budget = cheapestBuild + rnd.next(0, 3);
        } else {
            budget = cheapestBuild + rnd.next(0, 300);
        }

        if (mode == 2 && rnd.next(0, 1) == 0) {
            budget = cheapestBuild;
        }
        budget = max(1LL, budget);

        shuffle(components.begin(), components.end());

        println(n, budget);
        for (const Component& component : components) {
            println(component.type, component.name, component.price, component.quality);
        }
    }

    return 0;
}

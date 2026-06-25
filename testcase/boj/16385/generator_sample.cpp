#include "testlib.h"
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Stop {
    int r;
    int c;
    string name;
};

int coordForMode(int mode) {
    if (mode == 0) return rnd.next(-8, 8);
    if (mode == 1) return rnd.next(-100, 100);
    if (mode == 2) return rnd.next(-3, 3) * rnd.next(0, 30);

    vector<int> extremes = {-100, -75, -50, -25, 0, 25, 50, 75, 100};
    return rnd.any(extremes);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> names = {
        "Abra", "Bulba", "Charm", "Ditto", "Eevee",
        "Flare", "Gastly", "Horsea", "Jynx", "Kabuto",
        "Lapras", "Mew", "Onix", "Pidgey", "Zubat"
    };

    int mode = rnd.next(0, 5);
    int uniqueCount = rnd.next(1, 15);
    int n = rnd.next(uniqueCount, 20);
    int coordMode = rnd.next(0, 3);

    if (mode == 0) {
        uniqueCount = rnd.next(1, 5);
        n = rnd.next(uniqueCount, 10);
        coordMode = 0;
    } else if (mode == 1) {
        uniqueCount = rnd.next(10, 15);
        n = rnd.next(uniqueCount, 20);
        coordMode = 1;
    } else if (mode == 2) {
        uniqueCount = rnd.next(1, 8);
        n = rnd.next(uniqueCount, 20);
        coordMode = 3;
    } else if (mode == 3) {
        uniqueCount = rnd.next(2, 12);
        n = rnd.next(uniqueCount, 20);
        coordMode = 0;
    }

    vector<Stop> stops;
    stops.reserve(n);

    for (int i = 0; i < uniqueCount; ++i) {
        stops.push_back({coordForMode(coordMode), coordForMode(coordMode), names[i]});
    }

    while (static_cast<int>(stops.size()) < n) {
        string name = names[rnd.next(0, uniqueCount - 1)];
        int r = coordForMode(coordMode);
        int c = coordForMode(coordMode);

        if (mode == 2 && !stops.empty() && rnd.next(0, 99) < 35) {
            const Stop& base = rnd.any(stops);
            r = base.r;
            c = base.c;
        }

        if (mode == 3 && rnd.next(0, 99) < 45) {
            if (rnd.next(0, 1) == 0) r = 0;
            else c = 0;
        }

        stops.push_back({r, c, name});
    }

    if (mode == 4) {
        for (int i = 0; i < static_cast<int>(stops.size()); ++i) {
            if (i % 2 == 0) stops[i].r = -stops[i].r;
            else stops[i].c = -stops[i].c;
        }
    }

    shuffle(stops.begin(), stops.end());

    println(static_cast<int>(stops.size()));
    for (const Stop& stop : stops) {
        println(stop.r, stop.c, stop.name);
    }

    return 0;
}

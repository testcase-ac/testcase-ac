#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

struct Road {
    int city;
    int duration;
    int capacity;
};

int clampWeight(int value) {
    return max(1, min(1000000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 0 ? 2 : rnd.next(3, 12));
    int maxCompactRoads = min(40, 4 * (n - 1) + 8);
    vector<Road> roads;
    vector<int> capacities;

    int baseCapacity = rnd.next(1, 1000000);
    if (mode == 1) baseCapacity = rnd.next(1, 30);
    if (mode == 2) baseCapacity = rnd.next(999970, 1000000);

    for (int city = 1; city < n; ++city) {
        int duration;
        int capacity;

        if (mode == 3) {
            duration = rnd.next(1, 20) + city * rnd.next(0, 3);
            capacity = clampWeight(baseCapacity + rnd.next(-5, 5));
        } else if (mode == 4) {
            duration = rnd.next(9000, 10000);
            capacity = rnd.next(1, 1000000);
        } else {
            duration = rnd.next(1, 200);
            capacity = clampWeight(baseCapacity + rnd.next(-1000, 1000));
        }

        roads.push_back({city, duration, capacity});
        capacities.push_back(capacity);
    }

    int extraRoads = rnd.next(0, maxCompactRoads - (n - 1));
    for (int k = 0; k < extraRoads; ++k) {
        int city = rnd.next(1, n - 1);
        int duration;
        int capacity;

        if (mode == 0) {
            duration = rnd.next(1, 10000);
            capacity = rnd.any(capacities);
            if (rnd.next(0, 1)) capacity = clampWeight(capacity + rnd.next(-3, 3));
        } else if (mode == 1) {
            duration = rnd.next(1, 50);
            capacity = rnd.next(1, 60);
        } else if (mode == 2) {
            duration = rnd.next(1, 10000);
            capacity = rnd.next(999900, 1000000);
        } else if (mode == 3) {
            duration = rnd.next(1, 100);
            capacity = clampWeight(baseCapacity + rnd.next(-10, 10));
        } else if (mode == 4) {
            duration = rnd.next(1, 10000);
            capacity = rnd.next(1, 1000000);
        } else {
            duration = rnd.next(1, 10000);
            capacity = rnd.next(1, 1000000);
        }

        roads.push_back({city, duration, capacity});
        capacities.push_back(capacity);
    }

    shuffle(roads.begin(), roads.end());

    vector<int> queries;
    queries.push_back(1);
    queries.push_back(1000000);
    queries.push_back(rnd.any(capacities));

    int q = rnd.next(4, 14);
    while ((int)queries.size() < q) {
        int pivot = rnd.any(capacities);
        int weight;
        if (rnd.next(0, 2) == 0) {
            weight = clampWeight(pivot + rnd.next(-2, 2));
        } else if (mode == 1) {
            weight = rnd.next(1, 70);
        } else {
            weight = rnd.next(1, 1000000);
        }
        queries.push_back(weight);
    }
    shuffle(queries.begin(), queries.end());

    println(n, (int)roads.size());
    for (const Road& road : roads) {
        println(road.city, road.duration, road.capacity);
    }
    println((int)queries.size());
    for (int weight : queries) {
        println(weight);
    }

    return 0;
}

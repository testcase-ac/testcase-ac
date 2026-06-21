#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Resident = pair<int, int>;

constexpr int MIN_VALUE = 1;
constexpr int MAX_VALUE = 1000000000;

void addResident(vector<Resident>& residents, int x, int e) {
    residents.push_back({x, e});
}

int clampValue(long long value) {
    return static_cast<int>(max<long long>(MIN_VALUE, min<long long>(MAX_VALUE, value)));
}

void makeEqualInfluence(vector<Resident>& residents) {
    int n = rnd.next(2, 18);
    int e = rnd.next(1, 20);
    int base = rnd.next(1, 80);
    int step = rnd.next(0, 7);

    for (int i = 0; i < n; ++i) {
        int jitter = rnd.next(0, 3);
        addResident(residents, clampValue(base + i * step + jitter), e);
    }
}

void makeDuplicateCoordinates(vector<Resident>& residents) {
    int n = rnd.next(3, 24);
    int clusters = rnd.next(1, min(5, n));
    vector<int> xs;
    for (int i = 0; i < clusters; ++i) {
        xs.push_back(rnd.next(1, 100));
    }

    for (int i = 0; i < n; ++i) {
        int x = rnd.any(xs);
        int e = rnd.next(1, 150);
        if (rnd.next(4) == 0) e = rnd.any(vector<int>{1, 2, 1000000000});
        addResident(residents, x, e);
    }
}

void makeNestedIntervals(vector<Resident>& residents) {
    int n = rnd.next(4, 22);
    int center = rnd.next(100, 500);
    int radius = rnd.next(20, 120);

    for (int i = 0; i < n; ++i) {
        int offset = rnd.next(-radius, radius);
        int e = radius + 5 - abs(offset) + rnd.next(0, 20);
        addResident(residents, center + offset, max(1, e));
    }
}

void makeBoundaryValues(vector<Resident>& residents) {
    int n = rnd.next(4, 16);
    addResident(residents, 1, 1);
    addResident(residents, 1, MAX_VALUE);
    addResident(residents, MAX_VALUE, 1);
    addResident(residents, MAX_VALUE, MAX_VALUE);

    while (static_cast<int>(residents.size()) < n) {
        int x = rnd.any(vector<int>{
            rnd.next(1, 10),
            rnd.next(MAX_VALUE - 9, MAX_VALUE),
            rnd.next(450000000, 550000000)
        });
        int e = rnd.any(vector<int>{
            rnd.next(1, 10),
            rnd.next(MAX_VALUE - 9, MAX_VALUE),
            rnd.next(450000000, 550000000)
        });
        addResident(residents, x, e);
    }
}

void makeRandomSmall(vector<Resident>& residents) {
    int n = rnd.next(1, 30);
    int maxX = rnd.next(1, 200);
    int maxE = rnd.next(1, 200);

    for (int i = 0; i < n; ++i) {
        addResident(residents, rnd.next(1, maxX), rnd.next(1, maxE));
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Resident> residents;
    int mode = rnd.next(5);
    if (mode == 0) {
        makeEqualInfluence(residents);
    } else if (mode == 1) {
        makeDuplicateCoordinates(residents);
    } else if (mode == 2) {
        makeNestedIntervals(residents);
    } else if (mode == 3) {
        makeBoundaryValues(residents);
    } else {
        makeRandomSmall(residents);
    }

    if (rnd.next(2) == 0) {
        sort(residents.begin(), residents.end());
    } else {
        shuffle(residents.begin(), residents.end());
    }

    println(static_cast<int>(residents.size()));
    for (const auto& [x, e] : residents) {
        println(x, e);
    }

    return 0;
}

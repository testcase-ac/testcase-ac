#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MIN_VALUE = -536870912;
const int MAX_VALUE = 536870911;

void addValue(vector<int>& values, set<int>& used, int value) {
    if (value < MIN_VALUE || value > MAX_VALUE || used.count(value)) {
        return;
    }
    used.insert(value);
    values.push_back(value);
}

void fillRandomDistinct(vector<int>& values, set<int>& used, int targetSize,
                        int low, int high) {
    while ((int)values.size() < targetSize) {
        addValue(values, used, rnd.next(low, high));
    }
}

vector<int> plantedCase() {
    int a = rnd.next(-80, 80);
    int b = rnd.next(-80, 80);
    int c = rnd.next(-80, 80);
    int d = a + b + c;

    set<int> used;
    vector<int> values;
    addValue(values, used, a);
    addValue(values, used, b);
    addValue(values, used, c);
    addValue(values, used, d);

    while ((int)values.size() < 4) {
        used.clear();
        values.clear();
        a = rnd.next(-80, 80);
        b = rnd.next(-80, 80);
        c = rnd.next(-80, 80);
        d = a + b + c;
        addValue(values, used, a);
        addValue(values, used, b);
        addValue(values, used, c);
        addValue(values, used, d);
    }

    fillRandomDistinct(values, used, rnd.next(4, 18), -120, 120);
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> powersNoSolutionCase() {
    int n = rnd.next(1, 16);
    int startPower = rnd.next(0, 6);
    vector<int> values;
    set<int> used;
    for (int i = 0; i < n; ++i) {
        addValue(values, used, 1 << (startPower + i));
    }
    if (rnd.next(0, 1) == 1) {
        for (int& value : values) {
            value = -value;
        }
        shuffle(values.begin(), values.end());
    }
    return values;
}

vector<int> mixedSignCase() {
    int targetSize = rnd.next(5, 22);
    set<int> used;
    vector<int> values;

    int base = rnd.next(-40, 40);
    addValue(values, used, base);
    addValue(values, used, -base);
    addValue(values, used, base + rnd.next(1, 30));
    addValue(values, used, rnd.next(-100, -1));
    addValue(values, used, rnd.next(1, 100));

    fillRandomDistinct(values, used, targetSize, -150, 150);
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> sparseRandomCase() {
    int targetSize = rnd.next(1, 28);
    set<int> used;
    vector<int> values;
    int low = rnd.next(-500, -20);
    int high = rnd.next(20, 500);
    fillRandomDistinct(values, used, targetSize, low, high);
    shuffle(values.begin(), values.end());
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 8);
    for (int tc = 0; tc < caseCount; ++tc) {
        int mode = rnd.next(0, 3);
        vector<int> values;
        if (mode == 0) {
            values = plantedCase();
        } else if (mode == 1) {
            values = powersNoSolutionCase();
        } else if (mode == 2) {
            values = mixedSignCase();
        } else {
            values = sparseRandomCase();
        }

        println((int)values.size());
        for (int value : values) {
            println(value);
        }
    }
    println(0);

    return 0;
}

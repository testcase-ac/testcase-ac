#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomComposition(int n, int total) {
    vector<int> cuts;
    cuts.reserve(n + 1);
    cuts.push_back(0);
    cuts.push_back(total);
    for (int i = 1; i < n; ++i) {
        cuts.push_back(rnd.next(0, total));
    }
    shuffle(cuts.begin(), cuts.end());
    sort(cuts.begin(), cuts.end());

    vector<int> values;
    values.reserve(n);
    for (int i = 1; i < (int)cuts.size(); ++i) {
        values.push_back(cuts[i] - cuts[i - 1]);
    }
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> sparseComposition(int n, int total) {
    vector<int> values(n, 0);
    int used = rnd.next(1, n);
    vector<int> positions(n);
    for (int i = 0; i < n; ++i) {
        positions[i] = i;
    }
    shuffle(positions.begin(), positions.end());

    vector<int> parts = randomComposition(used, total);
    for (int i = 0; i < used; ++i) {
        values[positions[i]] = parts[i];
    }
    return values;
}

vector<int> steppedComposition(int n, int total) {
    int divisor = 1;
    vector<int> divisors;
    for (int d = 1; d * d <= total; ++d) {
        if (total % d != 0) {
            continue;
        }
        divisors.push_back(d);
        if (d * d != total) {
            divisors.push_back(total / d);
        }
    }
    divisor = rnd.any(divisors);

    vector<int> units = randomComposition(n, total / divisor);
    for (int& value : units) {
        value *= divisor;
    }
    return units;
}

vector<int> nearlyUniformComposition(int n, int total) {
    vector<int> values(n, total / n);
    int remaining = total % n;
    for (int i = 0; i < remaining; ++i) {
        ++values[i];
    }

    int moves = rnd.next(0, min(total, n * 4));
    for (int i = 0; i < moves; ++i) {
        int from = rnd.next(0, n - 1);
        int to = rnd.next(0, n - 1);
        if (values[from] > 0) {
            --values[from];
            ++values[to];
        }
    }
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> makeRow(int n, int total, int mode) {
    if (mode == 0) {
        return randomComposition(n, total);
    }
    if (mode == 1) {
        return sparseComposition(n, total);
    }
    if (mode == 2) {
        return steppedComposition(n, total);
    }
    return nearlyUniformComposition(n, total);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int p = rnd.next(0, 6);
    int total = 100;
    for (int i = 0; i < p; ++i) {
        total *= 10;
    }

    int sizeMode = rnd.next(0, 4);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 15);
    } else if (sizeMode == 3) {
        n = rnd.next(16, 30);
    } else {
        n = rnd.next(31, 100);
    }

    int previousMode = rnd.next(0, 3);
    int currentMode = rnd.next(0, 3);
    vector<int> previous = makeRow(n, total, previousMode);
    vector<int> current = makeRow(n, total, currentMode);

    println(n, p);
    println(previous);
    println(current);

    return 0;
}

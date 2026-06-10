#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

using Year = pair<int, int>;

void hideSomeValues(vector<Year>& years, int percent) {
    for (auto& year : years) {
        if (rnd.next(100) < percent) {
            year.first = 0;
        }
        if (rnd.next(100) < percent) {
            year.second = 0;
        }
    }
}

vector<int> distinctValues(int count, int lo, int hi) {
    vector<int> values;
    for (int value = lo; value <= hi && (int)values.size() < count; ++value) {
        values.push_back(value);
    }
    shuffle(values.begin(), values.end());
    return values;
}

vector<Year> makeClearSplit(int n, int k) {
    vector<Year> years(n);

    vector<int> highHappy = distinctValues(k, 700, 700 + k + 20);
    vector<int> lowHappy = distinctValues(n - k, 100, 100 + n - k + 20);
    vector<int> lowFatigue = distinctValues(k, 200, 200 + k + 20);
    vector<int> highFatigue = distinctValues(n - k, 800, 800 + n - k + 20);

    for (int i = 0; i < k; ++i) {
        years[i] = {highHappy[i], lowFatigue[i]};
    }
    for (int i = k; i < n; ++i) {
        years[i] = {lowHappy[i - k], highFatigue[i - k]};
    }

    return years;
}

vector<Year> makeCrossingTrends(int n) {
    vector<Year> years(n);

    vector<int> happiness = distinctValues(n, 100, 100 + n + 20);
    vector<int> fatigue = distinctValues(n, 500, 500 + n + 20);
    sort(happiness.begin(), happiness.end());
    sort(fatigue.begin(), fatigue.end());

    for (int i = 0; i < n; ++i) {
        years[i] = {happiness[i], fatigue[i]};
    }

    return years;
}

vector<Year> makeRandomDistinct(int n) {
    vector<Year> years(n);
    vector<int> happiness = distinctValues(n, 1, 1 + n * 4);
    vector<int> fatigue = distinctValues(n, 1000000, 1000000 + n * 4);

    for (int i = 0; i < n; ++i) {
        years[i] = {happiness[i], fatigue[i]};
    }

    return years;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 60 : 25);
    vector<Year> years;

    if (mode == 0) {
        years.assign(n, {0, 0});
    } else if (mode == 1) {
        int k = rnd.next(1, n - 1);
        years = makeClearSplit(n, k);
        hideSomeValues(years, rnd.next(10, 45));
    } else if (mode == 2) {
        years = makeCrossingTrends(n);
        hideSomeValues(years, rnd.next(0, 25));
    } else if (mode == 3) {
        n = 2;
        years = makeRandomDistinct(n);
        hideSomeValues(years, rnd.next(0, 60));
    } else {
        years = makeRandomDistinct(n);
        hideSomeValues(years, rnd.next(15, 70));
    }

    println(n);
    for (const auto& year : years) {
        println(year.first, year.second);
    }

    return 0;
}

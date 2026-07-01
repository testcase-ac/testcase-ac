#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>
using namespace std;

static vector<long long> measurableWith(const vector<long long>& weights) {
    set<long long> values;
    int limit = 1;
    for (int i = 0; i < (int)weights.size(); ++i) {
        limit *= 3;
    }

    for (int mask = 0; mask < limit; ++mask) {
        int x = mask;
        long long sum = 0;
        for (long long weight : weights) {
            int side = x % 3;
            x /= 3;
            if (side == 1) {
                sum += weight;
            } else if (side == 2) {
                sum -= weight;
            }
        }
        values.insert(llabs(sum));
    }

    return vector<long long>(values.begin(), values.end());
}

static long long randomAmount() {
    if (rnd.next(6) == 0) {
        return rnd.next(900000000LL, 1000000000LL);
    }
    return rnd.next(1LL, 200000LL);
}

static vector<long long> makeWeights(int m) {
    vector<long long> weights;
    int mode = rnd.next(5);
    for (int i = 0; i < m; ++i) {
        if (mode == 0) {
            weights.push_back(rnd.next(1LL, 12LL));
        } else if (mode == 1) {
            weights.push_back(1LL << rnd.next(0, 12));
        } else if (mode == 2) {
            weights.push_back(rnd.next(1LL, 4LL) * rnd.next(1LL, 25LL));
        } else if (mode == 3 && i > 0 && rnd.next(3) == 0) {
            weights.push_back(rnd.any(weights));
        } else {
            weights.push_back(rnd.next(1LL, 100000000LL));
        }
    }
    shuffle(weights.begin(), weights.end());
    return weights;
}

static vector<long long> uniqueSample(vector<long long> candidates, int count) {
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    candidates.erase(remove(candidates.begin(), candidates.end(), 0LL), candidates.end());
    shuffle(candidates.begin(), candidates.end());
    if ((int)candidates.size() > count) {
        candidates.resize(count);
    }
    return candidates;
}

static vector<long long> fillDistinct(vector<long long> amounts, int n) {
    vector<long long> distinct;
    set<long long> used;
    for (long long value : amounts) {
        if (1 <= value && value <= 1000000000LL && used.insert(value).second) {
            distinct.push_back(value);
        }
    }
    amounts = distinct;
    while ((int)amounts.size() < n) {
        long long value = randomAmount();
        if (used.insert(value).second) {
            amounts.push_back(value);
        }
    }
    shuffle(amounts.begin(), amounts.end());
    return amounts;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasets = rnd.next(4, 12);
    for (int tc = 0; tc < datasets; ++tc) {
        int m = rnd.next(1, 10);
        vector<long long> weights = makeWeights(m);
        vector<long long> base = measurableWith(weights);

        int n = rnd.next(1, 20);
        int mode = rnd.next(5);
        vector<long long> amounts;
        if (mode == 0) {
            amounts = uniqueSample(base, n);
        } else if (mode == 1) {
            long long extra = rnd.next(1LL, 5000LL);
            vector<long long> extended = weights;
            extended.push_back(extra);
            amounts = uniqueSample(measurableWith(extended), n);
        } else if (mode == 2) {
            long long extra = rnd.next(1LL, 1000000000LL);
            for (long long value : uniqueSample(base, n)) {
                long long candidate = value + extra;
                if (1 <= candidate && candidate <= 1000000000LL) {
                    amounts.push_back(candidate);
                }
            }
        } else if (mode == 3) {
            long long value = 1000000000LL;
            for (int i = 0; i < n; ++i) {
                amounts.push_back(value);
                value -= rnd.next(1LL, 97LL);
            }
        } else {
            amounts = uniqueSample(base, n / 2 + 1);
        }

        amounts = fillDistinct(amounts, n);
        println((int)amounts.size(), m);
        println(amounts);
        println(weights);
    }

    println(0, 0);
    return 0;
}

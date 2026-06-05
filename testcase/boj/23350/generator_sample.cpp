#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int chooseWeight(int mode, int index, int count) {
    if (mode == 0) {
        return index + 1;
    }
    if (mode == 1) {
        return count - index;
    }
    if (mode == 2) {
        return rnd.next(1, 8);
    }
    if (mode == 3) {
        return rnd.next(1, 100);
    }
    return (index % 2 == 0 ? rnd.next(45, 100) : rnd.next(1, 55));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 8);
    int extra = rnd.next(0, 24);
    int n = m + extra;

    vector<int> count(m + 1, 1);
    for (int i = 0; i < extra; ++i) {
        int p;
        if (mode == 0) {
            p = 1;
        } else if (mode == 1) {
            p = m;
        } else {
            p = rnd.next(1, m);
        }
        ++count[p];
    }

    vector<pair<int, int>> containers;
    for (int p = 1; p <= m; ++p) {
        int weightMode = rnd.next(0, 4);
        for (int i = 0; i < count[p]; ++i) {
            containers.push_back({p, chooseWeight(weightMode, i, count[p])});
        }
    }

    if (mode == 0) {
        sort(containers.begin(), containers.end());
    } else if (mode == 1) {
        sort(containers.begin(), containers.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs.first != rhs.first) {
                return lhs.first > rhs.first;
            }
            return lhs.second < rhs.second;
        });
    } else if (mode == 2) {
        shuffle(containers.begin(), containers.end());
    } else if (mode == 3) {
        vector<pair<int, int>> alternated;
        for (int round = 0; round < n; ++round) {
            for (int p = 1; p <= m; ++p) {
                auto it = find_if(containers.begin(), containers.end(), [p](const auto& item) {
                    return item.first == p;
                });
                if (it != containers.end()) {
                    alternated.push_back(*it);
                    containers.erase(it);
                }
            }
        }
        containers = alternated;
    } else {
        sort(containers.begin(), containers.end(), [](const auto& lhs, const auto& rhs) {
            if (lhs.first != rhs.first) {
                return lhs.first < rhs.first;
            }
            return lhs.second > rhs.second;
        });
        int prefix = rnd.next(0, n);
        shuffle(containers.begin(), containers.begin() + prefix);
        shuffle(containers.begin() + prefix, containers.end());
    }

    println(n, m);
    for (const auto& [priority, weight] : containers) {
        println(priority, weight);
    }

    return 0;
}

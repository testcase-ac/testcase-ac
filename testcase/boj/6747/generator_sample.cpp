#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int oddInRange(int lo, int hi) {
    int value = rnd.next(lo, hi);
    if (value % 2 == 0) {
        if (value < hi) {
            ++value;
        } else {
            --value;
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 6);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int minN = mode == 0 ? 1 : 3;
        int n = oddInRange(minN, mode == 5 ? 21 : 15);

        vector<pair<int, int>> comparisons;

        if (mode == 0) {
            // Sparse random comparisons.
            int target = rnd.next(0, min(n * (n - 1), 2 * n));
            for (int i = 0; i < target; ++i) {
                int heavier = rnd.next(1, n);
                int lighter = rnd.next(1, n - 1);
                if (lighter >= heavier) {
                    ++lighter;
                }
                comparisons.push_back({heavier, lighter});
            }
        } else if (mode == 1) {
            // A chain gives many transitive known order relationships.
            vector<int> bead(n);
            for (int i = 0; i < n; ++i) {
                bead[i] = i + 1;
            }
            shuffle(bead.begin(), bead.end());
            for (int i = 0; i + 1 < n; ++i) {
                comparisons.push_back({bead[i], bead[i + 1]});
            }
            int extra = rnd.next(0, n);
            for (int i = 0; i < extra; ++i) {
                int a = rnd.next(0, n - 2);
                int b = rnd.next(a + 1, n - 1);
                comparisons.push_back({bead[a], bead[b]});
            }
        } else if (mode == 2) {
            // One bead known heavier or lighter than many others.
            int center = rnd.next(1, n);
            bool centerHeavier = rnd.next(0, 1);
            vector<int> others;
            for (int bead = 1; bead <= n; ++bead) {
                if (bead != center) {
                    others.push_back(bead);
                }
            }
            shuffle(others.begin(), others.end());
            int degree = rnd.next(0, n - 1);
            for (int i = 0; i < degree; ++i) {
                if (centerHeavier) {
                    comparisons.push_back({center, others[i]});
                } else {
                    comparisons.push_back({others[i], center});
                }
            }
        } else if (mode == 3) {
            // Two ranked groups with random cross-group comparisons.
            vector<int> bead(n);
            for (int i = 0; i < n; ++i) {
                bead[i] = i + 1;
            }
            shuffle(bead.begin(), bead.end());
            int split = rnd.next(1, n - 1);
            for (int i = 0; i < split; ++i) {
                for (int j = split; j < n; ++j) {
                    if (rnd.next(0, 99) < 45) {
                        comparisons.push_back({bead[i], bead[j]});
                    }
                }
            }
        } else if (mode == 4) {
            // Duplicate comparisons are valid and exercise repeated edges.
            int baseCount = rnd.next(1, max(1, n / 2));
            for (int i = 0; i < baseCount; ++i) {
                int heavier = rnd.next(1, n);
                int lighter = rnd.next(1, n - 1);
                if (lighter >= heavier) {
                    ++lighter;
                }
                int repeats = rnd.next(2, 5);
                for (int r = 0; r < repeats; ++r) {
                    comparisons.push_back({heavier, lighter});
                }
            }
        } else {
            // Moderately dense directed graph without self-comparisons.
            int probability = rnd.next(15, 65);
            for (int heavier = 1; heavier <= n; ++heavier) {
                for (int lighter = 1; lighter <= n; ++lighter) {
                    if (heavier != lighter && rnd.next(0, 99) < probability) {
                        comparisons.push_back({heavier, lighter});
                    }
                }
            }
        }

        shuffle(comparisons.begin(), comparisons.end());
        println(n, static_cast<int>(comparisons.size()));
        for (const auto& comparison : comparisons) {
            println(comparison.first, comparison.second);
        }
    }

    return 0;
}

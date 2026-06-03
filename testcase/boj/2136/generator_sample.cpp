#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Ant {
    int position;
    int direction;
};

int fallTime(const Ant& ant, int length) {
    if (ant.direction < 0) {
        return ant.position;
    }
    return length - ant.position;
}

bool hasUniqueLastFall(const vector<Ant>& ants, int length) {
    int best = -1;
    int count = 0;
    for (const Ant& ant : ants) {
        int current = fallTime(ant, length);
        if (current > best) {
            best = current;
            count = 1;
        } else if (current == best) {
            ++count;
        }
    }
    return count == 1;
}

vector<int> candidatePositions(int length, int n, int mode) {
    vector<int> candidates;
    if (mode == 1) {
        int edge = min(length - 1, max(1, length / 4));
        for (int position = 1; position < length; ++position) {
            if (position <= edge || position >= length - edge) {
                candidates.push_back(position);
            }
        }
    } else if (mode == 2) {
        int center = length / 2;
        int radius = min(length - 1, max(1, length / 5));
        for (int position = max(1, center - radius);
             position <= min(length - 1, center + radius); ++position) {
            candidates.push_back(position);
        }
    }

    if (!candidates.empty() && (int)candidates.size() < n) {
        candidates.clear();
        for (int position = 1; position < length; ++position) {
            candidates.push_back(position);
        }
    }

    if (!candidates.empty()) {
        shuffle(candidates.begin(), candidates.end());
    }
    return candidates;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    int length;

    if (mode == 0) {
        n = 1;
        length = rnd.next(2, 40);
    } else if (mode == 4) {
        n = rnd.next(6, 18);
        length = rnd.next(100000000, 1000000000);
    } else {
        n = rnd.next(2, 12);
        length = rnd.next(n + 1, 80);
    }

    vector<Ant> ants;
    for (int attempt = 0; attempt < 1000; ++attempt) {
        ants.clear();
        vector<int> positions = candidatePositions(length, n, mode);
        if (positions.empty()) {
            set<int> usedPositions;
            while ((int)positions.size() < n) {
                int position = rnd.next(1, length - 1);
                if (usedPositions.insert(position).second) {
                    positions.push_back(position);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            int position = positions[i];
            int direction;
            if (mode == 1) {
                direction = -1;
            } else if (mode == 2) {
                direction = 1;
            } else {
                direction = rnd.next(2) == 0 ? -1 : 1;
            }

            ants.push_back({position, direction});
        }

        if (hasUniqueLastFall(ants, length)) {
            break;
        }
    }

    if (!hasUniqueLastFall(ants, length)) {
        ants.clear();
        for (int position = 1; position <= n; ++position) {
            ants.push_back({position, -1});
        }
    }

    shuffle(ants.begin(), ants.end());

    println(n, length);
    for (const Ant& ant : ants) {
        println(ant.direction * ant.position);
    }

    return 0;
}

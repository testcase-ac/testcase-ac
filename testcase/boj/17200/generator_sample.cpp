#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string featureName(int idx) {
    string s;
    do {
        s.push_back(char('a' + (idx % 26)));
        idx /= 26;
    } while (idx > 0);
    reverse(s.begin(), s.end());
    return s;
}

void addUnique(vector<vector<int>>& populations, const vector<int>& features) {
    set<int> candidate(features.begin(), features.end());
    for (const auto& population : populations) {
        if (set<int>(population.begin(), population.end()) == candidate) {
            return;
        }
    }
    vector<int> normalized(candidate.begin(), candidate.end());
    populations.push_back(normalized);
}

vector<vector<int>> makeProperCase() {
    int targetN = rnd.next(2, 14);
    int featureCount = rnd.next(1, min(12, targetN + 4));

    vector<vector<int>> populations;
    addUnique(populations, {});

    vector<int> chain;
    for (int i = 0; i < featureCount && (int)populations.size() < targetN; ++i) {
        chain.push_back(i);
        addUnique(populations, chain);
    }

    for (int i = 1; (int)populations.size() < targetN && i < featureCount; ++i) {
        vector<int> branch;
        int prefix = rnd.next(0, i - 1);
        for (int j = 0; j <= prefix; ++j) {
            branch.push_back(j);
        }
        branch.push_back(featureCount++);
        addUnique(populations, branch);
    }

    return populations;
}

vector<vector<int>> makeCrossingCase() {
    vector<vector<int>> populations;
    addUnique(populations, {0, 1});
    addUnique(populations, {1, 2});

    int targetN = rnd.next(3, 12);
    int featureCount = rnd.next(4, 12);
    vector<int> masks;
    for (int mask = 0; mask < (1 << featureCount); ++mask) {
        masks.push_back(mask);
    }
    shuffle(masks.begin(), masks.end());

    for (int mask : masks) {
        if ((int)populations.size() >= targetN) {
            break;
        }
        vector<int> features;
        for (int feature = 0; feature < featureCount; ++feature) {
            if (mask & (1 << feature)) {
                features.push_back(feature);
            }
        }
        addUnique(populations, features);
    }

    return populations;
}

vector<vector<int>> makeDenseCase() {
    vector<vector<int>> populations;
    int targetN = rnd.next(2, 10);
    int featureCount = rnd.next(max(8, targetN), 25);

    for (int i = 0; (int)populations.size() < targetN; ++i) {
        vector<int> features;
        for (int f = 0; f < featureCount; ++f) {
            if (f != i % featureCount) {
                features.push_back(f);
            }
        }
        addUnique(populations, features);
    }

    return populations;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<int>> populations;
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        populations = makeProperCase();
    } else if (mode == 1) {
        populations = makeCrossingCase();
    } else {
        populations = makeDenseCase();
    }

    vector<int> featureIds;
    for (const auto& population : populations) {
        for (int feature : population) {
            featureIds.push_back(feature);
        }
    }
    sort(featureIds.begin(), featureIds.end());
    featureIds.erase(unique(featureIds.begin(), featureIds.end()), featureIds.end());
    shuffle(featureIds.begin(), featureIds.end());

    int maxFeatureId = featureIds.empty() ? 0 : *max_element(featureIds.begin(), featureIds.end());
    vector<string> names(maxFeatureId + 1);
    for (int i = 0; i < (int)featureIds.size(); ++i) {
        names[featureIds[i]] = featureName(i);
    }

    shuffle(populations.begin(), populations.end());

    println((int)populations.size());
    for (auto population : populations) {
        shuffle(population.begin(), population.end());
        printf("%d", (int)population.size());
        for (int feature : population) {
            printf(" %s", names[feature].c_str());
        }
        printf("\n");
    }

    return 0;
}

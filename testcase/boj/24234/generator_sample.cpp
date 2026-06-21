// Generates compact one-dimensional chess records with shared-prefix and duplicate patterns.
#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAX_VALUE = 10000;

int randomValue() {
    return rnd.next(1, MAX_VALUE);
}

int randomValueExcept(int banned) {
    int value = randomValue();
    while (value == banned) {
        value = randomValue();
    }
    return value;
}

void addQueryCandidate(vector<int>& candidates, int value) {
    if (1 <= value && value <= MAX_VALUE) {
        candidates.push_back(value);
    }
}

vector<int> buildQueries(int q, vector<int> candidates) {
    shuffle(candidates.begin(), candidates.end());

    vector<int> queries;
    set<int> used;
    for (int value : candidates) {
        if ((int)queries.size() == q) {
            break;
        }
        if (used.insert(value).second) {
            queries.push_back(value);
        }
    }

    while ((int)queries.size() < q) {
        int value = randomValue();
        if (used.insert(value).second) {
            queries.push_back(value);
        }
    }

    shuffle(queries.begin(), queries.end());
    return queries;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    vector<vector<int>> records;
    vector<int> queryCandidates;

    if (mode == 0) {
        int first = randomValue();
        int second = randomValueExcept(first);
        records.push_back({first});
        records.push_back({second});
        addQueryCandidate(queryCandidates, first);
        addQueryCandidate(queryCandidates, second);
    } else if (mode == 1) {
        int pivot = randomValue();
        int left = randomValue();
        int right = randomValueExcept(left);
        records.push_back({pivot, left});
        records.push_back({pivot, right});
        addQueryCandidate(queryCandidates, pivot);
        addQueryCandidate(queryCandidates, left);
        addQueryCandidate(queryCandidates, right);
    } else if (mode == 2) {
        int pivot = randomValue();
        int commonTail = randomValue();
        int branchA = randomValue();
        int branchB = randomValueExcept(branchA);

        records.push_back({pivot, commonTail, branchA});
        records.push_back({pivot, commonTail, branchB});
        records.push_back({pivot, commonTail, branchB});
        records.push_back({pivot});
        addQueryCandidate(queryCandidates, pivot);
        addQueryCandidate(queryCandidates, commonTail);
        addQueryCandidate(queryCandidates, branchA);
        addQueryCandidate(queryCandidates, branchB);
    } else if (mode == 3) {
        int n = rnd.next(5, 10);
        int prefixLen = rnd.next(1, 4);
        vector<int> prefix;
        for (int i = 0; i < prefixLen; ++i) {
            prefix.push_back(randomValue());
            addQueryCandidate(queryCandidates, prefix.back());
        }

        for (int i = 0; i < n; ++i) {
            vector<int> record = prefix;
            int extra = rnd.next(0, 3);
            for (int j = 0; j < extra; ++j) {
                record.push_back(randomValue());
                addQueryCandidate(queryCandidates, record.back());
            }
            records.push_back(record);
        }

        if (records[0].size() == records[1].size()) {
            records[1].push_back(randomValue());
            addQueryCandidate(queryCandidates, records[1].back());
        }
    } else {
        int n = rnd.next(6, 12);
        int rootChoices = rnd.next(2, 4);
        vector<int> roots;
        for (int i = 0; i < rootChoices; ++i) {
            roots.push_back(randomValue());
            addQueryCandidate(queryCandidates, roots.back());
        }

        for (int i = 0; i < n; ++i) {
            vector<int> record;
            int root = rnd.any(roots);
            record.push_back(root);
            int len = rnd.next(1, 5);
            for (int j = 1; j < len; ++j) {
                int value = (rnd.next(0, 99) < 45 ? rnd.any(roots) : randomValue());
                record.push_back(value);
                addQueryCandidate(queryCandidates, value);
            }
            records.push_back(record);
        }
    }

    int q = rnd.next(1, min(10, MAX_VALUE));
    vector<int> queries = buildQueries(q, queryCandidates);

    println((int)records.size(), q);
    for (const vector<int>& record : records) {
        printf("%d", (int)record.size());
        for (int value : record) {
            printf(" %d", value);
        }
        printf("\n");
    }
    for (int query : queries) {
        println(query);
    }

    return 0;
}

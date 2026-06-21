#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

long long freshDescriptor(set<long long>& used) {
    long long value;
    do {
        if (rnd.next(4) == 0) {
            value = 1000000000LL - rnd.next(0, 1000);
        } else {
            value = rnd.next(1, 2000);
        }
    } while (used.count(value));
    used.insert(value);
    return value;
}

void addDescriptor(vector<set<long long>>& people, int person, long long value) {
    people[person].insert(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(2, 12);
    int mode = rnd.next(5);
    vector<set<long long>> people(n);
    set<long long> used;

    if (mode == 0) {
        long long hub = freshDescriptor(used);
        for (int i = 0; i < n; ++i) {
            addDescriptor(people, i, hub);
        }
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) {
            long long link = freshDescriptor(used);
            addDescriptor(people, i - 1, link);
            addDescriptor(people, i, link);
        }
    } else if (mode == 2) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) {
            order[i] = i;
        }
        shuffle(order.begin(), order.end());
        for (int i = 1; i < n; ++i) {
            int parent = rnd.next(i);
            long long link = freshDescriptor(used);
            addDescriptor(people, order[parent], link);
            addDescriptor(people, order[i], link);
        }
    } else {
        int firstSize = rnd.next(1, n - 1);
        for (int i = 1; i < firstSize; ++i) {
            long long link = freshDescriptor(used);
            addDescriptor(people, i - 1, link);
            addDescriptor(people, i, link);
        }
        for (int i = firstSize + 1; i < n; ++i) {
            long long link = freshDescriptor(used);
            addDescriptor(people, i - 1, link);
            addDescriptor(people, i, link);
        }
    }

    for (int i = 0; i < n; ++i) {
        int extra = rnd.next(0, 3);
        while (people[i].empty() || extra-- > 0) {
            addDescriptor(people, i, freshDescriptor(used));
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        vector<long long> descriptors(people[i].begin(), people[i].end());
        shuffle(descriptors.begin(), descriptors.end());
        printf("%d", static_cast<int>(descriptors.size()));
        for (long long descriptor : descriptors) {
            printf(" %lld", descriptor);
        }
        printf("\n");
    }

    return 0;
}

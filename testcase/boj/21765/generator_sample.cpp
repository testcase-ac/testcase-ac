#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> shuffledPeople(int n) {
    vector<int> people;
    for (int i = 1; i <= n; ++i) people.push_back(i);
    shuffle(people.begin(), people.end());
    return people;
}

static void addSet(vector<vector<int>>& sets, vector<int> members) {
    sort(members.begin(), members.end());
    members.erase(unique(members.begin(), members.end()), members.end());
    shuffle(members.begin(), members.end());
    sets.push_back(members);
}

static void ensureCoverage(vector<vector<int>>& sets, int n) {
    vector<bool> appears(n + 1, false);
    for (const auto& members : sets) {
        for (int person : members) appears[person] = true;
    }
    for (int person = 1; person <= n; ++person) {
        if (!appears[person]) addSet(sets, vector<int>{person});
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 12);
    vector<vector<int>> sets;

    if (mode == 0) {
        vector<int> people = shuffledPeople(n);
        for (int person : people) addSet(sets, vector<int>{person});
        int extra = rnd.next(0, min(4, n));
        for (int i = 0; i < extra; ++i) {
            vector<int> members;
            for (int person = 1; person <= n; ++person) {
                if (rnd.next(2) == 0) members.push_back(person);
            }
            addSet(sets, members);
        }
    } else if (mode == 1) {
        vector<int> people = shuffledPeople(n);
        for (int i = 0; i < n;) {
            int len = rnd.next(1, min(4, n - i));
            vector<int> members(people.begin() + i, people.begin() + i + len);
            addSet(sets, members);
            i += len;
        }
    } else if (mode == 2) {
        for (int start = 1; start <= n; ++start) {
            int len = rnd.next(1, min(5, n - start + 1));
            vector<int> members;
            for (int person = start; person < start + len; ++person) {
                members.push_back(person);
            }
            addSet(sets, members);
        }
    } else if (mode == 3) {
        int hub = rnd.next(1, n);
        for (int person = 1; person <= n; ++person) {
            vector<int> members{hub, person};
            int extras = rnd.next(0, min(3, n));
            for (int i = 0; i < extras; ++i) members.push_back(rnd.next(1, n));
            addSet(sets, members);
        }
    } else {
        int m = rnd.next(1, min(18, n + 6));
        for (int i = 0; i < m; ++i) {
            vector<int> members;
            int target = rnd.next(0, min(6, n));
            while ((int)members.size() < target) members.push_back(rnd.next(1, n));
            addSet(sets, members);
        }
    }

    ensureCoverage(sets, n);
    shuffle(sets.begin(), sets.end());

    println(n, (int)sets.size());
    for (const auto& members : sets) {
        printf("%d", (int)members.size());
        for (int person : members) printf(" %d", person);
        printf("\n");
    }

    return 0;
}

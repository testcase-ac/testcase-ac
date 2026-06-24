#include "testlib.h"

#include <map>
#include <set>
#include <vector>

using namespace std;

int n;
long long m;
vector<long long> target;

struct State {
    vector<long long> gifts;
    map<long long, set<int>> by_count;

    explicit State(const vector<long long>& initial) : gifts(initial) {
        for (int i = 1; i <= n; ++i) {
            by_count[gifts[i]].insert(i);
        }
    }

    void remove_member(int index) {
        auto it = by_count.find(gifts[index]);
        it->second.erase(index);
        if (it->second.empty()) {
            by_count.erase(it);
        }
    }

    void add_member(int index) {
        by_count[gifts[index]].insert(index);
    }

    void add_gifts(int index, long long delta) {
        remove_member(index);
        gifts[index] += delta;
        add_member(index);
    }

    int max_excluding(int excluded) const {
        for (auto it = by_count.rbegin(); it != by_count.rend(); ++it) {
            const set<int>& members = it->second;
            int candidate = *members.begin();
            if (candidate != excluded) {
                return candidate;
            }
            auto next_it = members.upper_bound(excluded);
            if (next_it != members.end()) {
                return *next_it;
            }
        }
        return -1;
    }

    int min_excluding(int excluded) const {
        for (auto it = by_count.begin(); it != by_count.end(); ++it) {
            const set<int>& members = it->second;
            int candidate = *members.begin();
            if (candidate != excluded) {
                return candidate;
            }
            auto next_it = members.upper_bound(excluded);
            if (next_it != members.end()) {
                return *next_it;
            }
        }
        return -1;
    }
};

void read_and_validate_answer(InStream& stream, const vector<long long>& initial) {
    int k = stream.readInt(0, 2 * n, "K");
    stream.readEoln();

    State state(initial);
    for (int op_index = 1; op_index <= k; ++op_index) {
        string type = stream.readToken("[+-]", format("operation[%d].type", op_index).c_str());
        int i = stream.readInt(1, n, format("operation[%d].i", op_index).c_str());
        long long x = stream.readLong(1LL, m, format("operation[%d].x", op_index).c_str());
        stream.readEoln();

        if (n == 1) {
            stream.quitf(_wa, "operation %d cannot choose another member when N=1", op_index);
        }

        if (type == "+") {
            int j = state.max_excluding(i);
            if (j == -1) {
                stream.quitf(_wa, "operation %d cannot choose a donor", op_index);
            }
            if (state.gifts[j] < x) {
                stream.quitf(_wa,
                             "operation %d asks member %d to give %lld gifts, but they have %lld",
                             op_index,
                             j,
                             x,
                             state.gifts[j]);
            }
            state.add_gifts(j, -x);
            state.add_gifts(i, x);
        } else {
            int j = state.min_excluding(i);
            if (j == -1) {
                stream.quitf(_wa, "operation %d cannot choose a recipient", op_index);
            }
            if (state.gifts[i] < x) {
                stream.quitf(_wa,
                             "operation %d asks member %d to give %lld gifts, but they have %lld",
                             op_index,
                             i,
                             x,
                             state.gifts[i]);
            }
            state.add_gifts(i, -x);
            state.add_gifts(j, x);
        }
    }

    stream.readEof();

    for (int i = 1; i <= n; ++i) {
        if (state.gifts[i] != target[i]) {
            stream.quitf(_wa,
                         "member %d has %lld gifts after all operations, expected %lld",
                         i,
                         state.gifts[i],
                         target[i]);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readLong();

    vector<long long> initial(n + 1);
    target.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        initial[i] = inf.readLong();
    }
    for (int i = 1; i <= n; ++i) {
        target[i] = inf.readLong();
    }

    read_and_validate_answer(ans, initial);
    read_and_validate_answer(ouf, initial);

    quitf(_ok, "valid redistribution sequence");
}

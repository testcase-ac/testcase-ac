#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Operation {
    string op;
    long long a;
    long long l;
};

long long randomLength(int mode) {
    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.any(vector<long long>{1, 2, 3, 5, 8, 13, 21});
    if (mode == 2) return rnd.next(1000000000LL, 1000000000000LL);
    return rnd.any(vector<long long>{1LL, 999999999999999999LL, 1000000000000000000LL});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_L = 1000000000000000000LL;

    vector<Operation> ops;
    long long m = 1;
    long long adHocLengthSum = 0;

    int mode = rnd.next(0, 4);
    int targetQ = rnd.next(6, 36);
    int lengthMode = rnd.next(0, 3);

    auto addQuery = [&](long long x) {
        long long l;
        if (rnd.next(0, 4) == 0) {
            l = MAX_L;
        } else if (lengthMode == 2) {
            l = rnd.next(1LL, 1000000000000LL);
        } else {
            l = rnd.next(1LL, 30LL);
        }
        ops.push_back({"query", x, l});
    };

    auto addAdHoc = [&](long long k, long long l) {
        if (adHocLengthSum > MAX_L - l) return;
        ops.push_back({"ad-hoc", k, l});
        adHocLengthSum += l;
        ++m;
    };

    if (mode == 0) {
        int queries = rnd.next(1, min(5, targetQ));
        for (int i = 0; i < queries; ++i) addQuery(0);
    } else if (mode == 1) {
        int n = rnd.next(3, targetQ - 1);
        for (int i = 0; i < n; ++i) {
            long long len = randomLength(lengthMode);
            if (adHocLengthSum > MAX_L - len) len = 1;
            addAdHoc(m - 1, len);
            if (rnd.next(0, 2) == 0) addQuery(rnd.next(0LL, m - 1));
        }
        addQuery(m - 1);
    } else if (mode == 2) {
        int n = rnd.next(3, targetQ - 1);
        for (int i = 0; i < n; ++i) {
            long long len = randomLength(lengthMode);
            if (adHocLengthSum > MAX_L - len) len = 1;
            addAdHoc(0, len);
            if (rnd.next(0, 2) == 0) addQuery(m - 1);
        }
        addQuery(rnd.next(0LL, m - 1));
    } else if (mode == 3) {
        while ((int)ops.size() + 1 < targetQ) {
            if (m == 1 || rnd.next(0, 99) < 65) {
                long long k;
                int attachMode = rnd.next(0, 3);
                if (attachMode == 0) {
                    k = 0;
                } else if (attachMode == 1) {
                    k = m - 1;
                } else {
                    k = rnd.next(0LL, m - 1);
                }

                long long len = randomLength(lengthMode);
                if (adHocLengthSum > MAX_L - len) len = 1;
                addAdHoc(k, len);
            } else {
                addQuery(rnd.next(0LL, m - 1));
            }
        }
        addQuery(rnd.next(0LL, m - 1));
    } else {
        addAdHoc(0, MAX_L);
        addQuery(1);
        if (rnd.next(0, 1) == 1) addQuery(0);
    }

    if ((int)ops.size() > targetQ) ops.resize(targetQ);
    if (none_of(ops.begin(), ops.end(), [](const Operation& op) { return op.op == "query"; })) {
        ops.push_back({"query", 0, 1});
    }

    println((int)ops.size());
    for (const Operation& op : ops) {
        println(op.op, op.a, op.l);
    }

    return 0;
}

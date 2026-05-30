#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const long long SAL_MIN = 1LL;
const long long SAL_MAX = 2147483647LL;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n+1), r(n+1, 0) {
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int find(int x) {
        return p[x] == x ? x : p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a,b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct SegmentTree {
    int n;
    vector<long long> mn, mx, lazy;

    SegmentTree(const vector<long long>& values) {
        n = (int)values.size() - 1;
        mn.assign(4 * n + 4, 0);
        mx.assign(4 * n + 4, 0);
        lazy.assign(4 * n + 4, 0);
        build(1, 1, n, values);
    }

    void build(int node, int left, int right, const vector<long long>& values) {
        if (left == right) {
            mn[node] = mx[node] = values[left];
            return;
        }
        int mid = (left + right) / 2;
        build(node * 2, left, mid, values);
        build(node * 2 + 1, mid + 1, right, values);
        pull(node);
    }

    void pull(int node) {
        mn[node] = min(mn[node * 2], mn[node * 2 + 1]);
        mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
    }

    void apply(int node, long long delta) {
        mn[node] += delta;
        mx[node] += delta;
        lazy[node] += delta;
    }

    void push(int node) {
        if (lazy[node] == 0) return;
        apply(node * 2, lazy[node]);
        apply(node * 2 + 1, lazy[node]);
        lazy[node] = 0;
    }

    void add(int queryLeft, int queryRight, long long delta) {
        if (queryLeft > queryRight) return;
        add(1, 1, n, queryLeft, queryRight, delta);
    }

    void add(int node, int left, int right, int queryLeft, int queryRight, long long delta) {
        if (queryRight < left || right < queryLeft) return;
        if (queryLeft <= left && right <= queryRight) {
            apply(node, delta);
            return;
        }
        push(node);
        int mid = (left + right) / 2;
        add(node * 2, left, mid, queryLeft, queryRight, delta);
        add(node * 2 + 1, mid + 1, right, queryLeft, queryRight, delta);
        pull(node);
    }

    long long minValue() const {
        return mn[1];
    }

    long long maxValue() const {
        return mx[1];
    }
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500000, "M");
    inf.readEoln();

    // Read employee data
    vector<int> manager(N+1, 0);
    vector<vector<int>> children(N+1);
    vector<long long> salary(N+1, 0);
    // i = 1: only salary
    salary[1] = inf.readLong(SAL_MIN, SAL_MAX, "salary[1]");
    inf.readEoln();
    // i = 2..N: salary and manager
    for (int i = 2; i <= N; i++) {
        salary[i] = inf.readLong(SAL_MIN, SAL_MAX, "salary");
        inf.readSpace();
        int m = inf.readInt(1, N, "manager");
        inf.readEoln();
        manager[i] = m;
        children[m].push_back(i);
        // no self-loop
        ensuref(m != i, "Employee %d has self as manager", i);
    }

    // Validate tree structure: no cycles, all connected to 1
    DSU dsu(N);
    for (int i = 2; i <= N; i++) {
        int m = manager[i];
        // union; detect cycle if already connected
        if (!dsu.unite(i, m)) {
            ensuref(false, "Cycle detected at employee %d with manager %d", i, m);
        }
    }
    // Check connectivity: all must be in same comp as 1
    int root1 = dsu.find(1);
    for (int i = 2; i <= N; i++) {
        ensuref(dsu.find(i) == root1, "Employee %d is not connected to root 1", i);
    }

    vector<int> tin(N+1), tout(N+1);
    vector<long long> eulerSalary(N+1);
    vector<pair<int, int>> stack;
    stack.reserve(2 * N);
    stack.push_back({1, 0});
    int timer = 0;
    while (!stack.empty()) {
        int node = stack.back().first;
        int state = stack.back().second;
        stack.pop_back();
        if (state == 0) {
            tin[node] = ++timer;
            eulerSalary[tin[node]] = salary[node];
            stack.push_back({node, 1});
            for (int i = (int)children[node].size() - 1; i >= 0; i--) {
                stack.push_back({children[node][i], 0});
            }
        } else {
            tout[node] = timer;
        }
    }

    SegmentTree salaries(eulerSalary);

    // Read queries
    for (int q = 0; q < M; q++) {
        // type: 'p' or 'u'
        string type = inf.readToken("p|u", "query_type");
        inf.readSpace();
        int a = inf.readInt(1, N, "a");
        if (type == "p") {
            inf.readSpace();
            int x = inf.readInt(-10000, 10000, "x");
            salaries.add(tin[a] + 1, tout[a], x);
            ensuref(salaries.minValue() >= SAL_MIN,
                    "salary becomes non-positive after query %d", q + 1);
            ensuref(salaries.maxValue() <= SAL_MAX,
                    "salary exceeds signed 32-bit int after query %d", q + 1);
        } else {
            // type == "u"
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

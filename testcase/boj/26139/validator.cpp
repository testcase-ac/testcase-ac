#include "testlib.h"

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Operation {
    char type;
    vector<int> inputs;
    vector<int> outputs;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long m = inf.readLong(1LL, 1000000000LL, "m");
    inf.readSpace();
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 1000, "q");
    inf.readEoln();

    vector<Operation> operations;
    operations.reserve(n);
    vector<int> producedBy(20002, 0);
    vector<int> consumedBy(20002, 0);
    vector<int> producedIds;
    producedIds.reserve(2 * n);

    for (int i = 1; i <= n; ++i) {
        string typeToken = inf.readToken("S|M", "node_type");
        char type = typeToken[0];
        inf.readSpace();
        int x = inf.readInt(1, 20001, "x");
        inf.readSpace();
        int y = inf.readInt(1, 20001, "y");
        inf.readSpace();
        int z = inf.readInt(1, 20001, "z");
        inf.readEoln();

        ensuref(x != y && x != z && y != z,
                "node %d identifiers must be distinct: %d %d %d", i, x, y, z);

        Operation op;
        op.type = type;
        if (type == 'S') {
            op.inputs = {x};
            op.outputs = {y, z};
        } else {
            op.inputs = {x, y};
            op.outputs = {z};
        }

        for (int id : op.inputs) {
            ensuref(id == 1 || id >= 2, "invalid input identifier %d at node %d", id, i);
            // CHECK: The statement only says each output identifier is consumed at most once.
            // Treating source identifier 1 the same prevents fanout without an explicit split node.
            ensuref(consumedBy[id] == 0,
                    "identifier %d is used as node input more than once", id);
            consumedBy[id] = i;
        }

        for (int id : op.outputs) {
            ensuref(id >= 2, "output identifier %d at node %d must be at least 2", id, i);
            ensuref(producedBy[id] == 0,
                    "output identifier %d is produced more than once", id);
            producedBy[id] = i;
            producedIds.push_back(id);
        }

        operations.push_back(op);
    }

    int outputCount = static_cast<int>(producedIds.size());
    int maxId = outputCount + 1;
    sort(producedIds.begin(), producedIds.end());
    ensuref(static_cast<int>(producedIds.size()) == outputCount,
            "internal produced output count mismatch");
    for (int expected = 2; expected <= maxId; ++expected) {
        ensuref(producedIds[expected - 2] == expected,
                "output identifiers must be consecutive from 2; expected %d, found %d",
                expected, producedIds[expected - 2]);
    }

    for (int id = 2; id <= maxId; ++id) {
        ensuref(producedBy[id] != 0, "input identifier %d is not produced", id);
    }

    vector<vector<int>> graph(maxId + 1);
    vector<int> indegree(maxId + 1, 0);
    for (const Operation& op : operations) {
        for (int input : op.inputs) {
            ensuref(input <= maxId,
                    "input identifier %d is outside the consecutive identifier range 1..%d",
                    input, maxId);
            for (int output : op.outputs) {
                graph[input].push_back(output);
                ++indegree[output];
            }
        }
    }

    queue<int> ready;
    for (int id = 1; id <= maxId; ++id) {
        if (indegree[id] == 0) {
            ready.push(id);
        }
    }

    int visited = 0;
    while (!ready.empty()) {
        int id = ready.front();
        ready.pop();
        ++visited;
        for (int next : graph[id]) {
            --indegree[next];
            if (indegree[next] == 0) {
                ready.push(next);
            }
        }
    }
    ensuref(visited == maxId, "network dependencies must be acyclic");

    for (int i = 1; i <= q; ++i) {
        int x = inf.readInt(2, 100000, "query_output");
        inf.readSpace();
        long long k = inf.readLong(1LL, 1000000000LL, "query_index");
        inf.readEoln();
        ensuref(x <= maxId && producedBy[x] != 0,
                "query %d references invalid output identifier %d", i, x);
    }

    inf.readEof();
}

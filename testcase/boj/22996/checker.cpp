#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

struct Memory {
    int n;
    int q;
    vector<int> finalPar;
    vector<int> returns;
};

struct DsuProgram {
    vector<int> par;

    explicit DsuProgram(int n) : par(n + 1) {
        for (int i = 1; i <= n; ++i) {
            par[i] = i;
        }
    }

    int find(int v) {
        int root = v;
        while (root != par[root]) {
            root = par[root];
        }
        while (v != root) {
            int next = par[v];
            par[v] = root;
            v = next;
        }
        return root;
    }

    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            par[u] = v;
        }
    }
};

void reject(InStream& stream, TResult verdict, const string& message) {
    stream.quitf(verdict, "%s", message.c_str());
}

void readAndValidateOutput(InStream& stream, TResult invalidVerdict, const Memory& memory) {
    int n = stream.readInt(1, 300000, "N");
    int q = stream.readInt(1, 300000, "Q");
    if (n != memory.n || q != memory.q) {
        reject(stream, invalidVerdict,
               format("first line is %d %d, expected %d %d", n, q, memory.n, memory.q));
    }

    DsuProgram dsu(memory.n);
    int seenReturns = 0;

    for (int i = 1; i <= memory.q; ++i) {
        int type = stream.readInt(1, 2, format("query[%d].type", i).c_str());
        if (type == 1) {
            int u = stream.readInt(1, memory.n, format("query[%d].u", i).c_str());
            int v = stream.readInt(1, memory.n, format("query[%d].v", i).c_str());
            dsu.merge(u, v);
        } else {
            int v = stream.readInt(1, memory.n, format("query[%d].v", i).c_str());
            if (seenReturns == (int)memory.returns.size()) {
                reject(stream, invalidVerdict,
                       format("query %d is an extra type-2 query", i));
            }
            int returned = dsu.find(v);
            int expected = memory.returns[seenReturns];
            if (returned != expected) {
                reject(stream, invalidVerdict,
                       format("query %d returns %d, expected remembered return %d", i, returned, expected));
            }
            ++seenReturns;
        }
    }

    if (seenReturns != (int)memory.returns.size()) {
        reject(stream, invalidVerdict,
               format("output has %d type-2 queries, expected %d",
                      seenReturns, (int)memory.returns.size()));
    }

    for (int i = 1; i <= memory.n; ++i) {
        if (dsu.par[i] != memory.finalPar[i]) {
            reject(stream, invalidVerdict,
                   format("final par[%d] is %d, expected %d", i, dsu.par[i], memory.finalPar[i]));
        }
    }

    if (!stream.seekEof()) {
        reject(stream, invalidVerdict, "extra tokens after the query list");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Memory memory;
    memory.n = inf.readInt();
    memory.q = inf.readInt();
    memory.finalPar.assign(memory.n + 1, 0);
    for (int i = 1; i <= memory.n; ++i) {
        memory.finalPar[i] = inf.readInt();
    }
    int m = inf.readInt();
    memory.returns.resize(m);
    for (int i = 0; i < m; ++i) {
        memory.returns[i] = inf.readInt();
    }

    readAndValidateOutput(ans, _fail, memory);
    readAndValidateOutput(ouf, _wa, memory);

    quitf(_ok, "valid reconstruction");
}

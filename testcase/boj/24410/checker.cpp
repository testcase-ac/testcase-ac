#include "testlib.h"

#include <algorithm>
#include <functional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Node {
    long long raw;
    int prev;
    int next;
    bool alive;
};

struct Answer {
    vector<long long> stack;
};

int n;
vector<long long> target;

Answer readAnswer(InStream& stream) {
    string program = stream.readToken("[1d+]{1,100000}", "program");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after program");
    }

    vector<Node> nodes;
    nodes.reserve(program.size());
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> byRaw;
    long long offset = 0;
    int top = -1;

    auto removeNode = [&](int id) {
        if (!nodes[id].alive) {
            return;
        }
        int before = nodes[id].prev;
        int after = nodes[id].next;
        if (before != -1) {
            nodes[before].next = after;
        }
        if (after != -1) {
            nodes[after].prev = before;
        } else {
            top = before;
        }
        nodes[id].alive = false;
    };

    auto removeExpired = [&]() {
        while (!byRaw.empty() && byRaw.top().first <= offset) {
            int id = byRaw.top().second;
            byRaw.pop();
            if (nodes[id].alive && nodes[id].raw <= offset) {
                removeNode(id);
            }
        }
    };

    auto pushValue = [&](long long value) {
        int id = (int)nodes.size();
        nodes.push_back({value + offset, top, -1, true});
        if (top != -1) {
            nodes[top].next = id;
        }
        top = id;
        byRaw.push({nodes[id].raw, id});
    };

    auto popTop = [&]() -> long long {
        int id = top;
        long long value = nodes[id].raw - offset;
        removeNode(id);
        return value;
    };

    for (int i = 0; i < (int)program.size(); ++i) {
        char op = program[i];
        if (op == '1') {
            pushValue(1);
        } else if (op == 'd') {
            if (top == -1) {
                stream.quitf(_wa, "instruction %d duplicates an empty stack", i + 1);
            }
            pushValue(nodes[top].raw - offset);
        } else {
            if (top == -1 || nodes[top].prev == -1) {
                stream.quitf(_wa, "instruction %d adds with fewer than two stack entries", i + 1);
            }
            long long a = popTop();
            long long b = popTop();
            ++offset;
            removeExpired();
            pushValue(a + b);
        }
    }

    vector<long long> result;
    for (int id = top; id != -1; id = nodes[id].prev) {
        result.push_back(nodes[id].raw - offset);
    }
    reverse(result.begin(), result.end());
    return {result};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    target.resize(n);
    for (int i = 0; i < n; ++i) {
        target[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans);
    if (jury.stack != target) {
        quitf(_fail, "jury program produces stack of size %d instead of target size %d",
              (int)jury.stack.size(), n);
    }

    Answer participant = readAnswer(ouf);
    if (participant.stack != jury.stack) {
        quitf(_wa, "participant stack does not match jury stack");
    }

    quitf(_ok, "valid program produces target stack of size %d", n);
}

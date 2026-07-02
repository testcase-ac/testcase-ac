#include "testlib.h"

#include <algorithm>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

int n, mLimit, pLimit, words;

struct Claim {
    int nodeCount;
    int edgeCount;
};

[[noreturn]] void invalid(InStream& stream, bool juryOutput, const char* fmt, ...) {
    static char message[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);
    stream.quitf(juryOutput ? _fail : _wa, "%s", message);
}

bool intersects(const vector<uint64_t>& bits, int a, int b) {
    size_t offsetA = static_cast<size_t>(a) * words;
    size_t offsetB = static_cast<size_t>(b) * words;
    for (int i = 0; i < words; ++i) {
        if ((bits[offsetA + i] & bits[offsetB + i]) != 0) {
            return true;
        }
    }
    return false;
}

void mergeBits(vector<uint64_t>& bits, int to, int from) {
    size_t offsetTo = static_cast<size_t>(to) * words;
    size_t offsetFrom = static_cast<size_t>(from) * words;
    for (int i = 0; i < words; ++i) {
        bits[offsetTo + i] |= bits[offsetFrom + i];
    }
}

int countBits(const vector<uint64_t>& bits, int node) {
    size_t offset = static_cast<size_t>(node) * words;
    int total = 0;
    for (int i = 0; i < words; ++i) {
        total += __builtin_popcountll(bits[offset + i]);
    }
    return total;
}

bool hasEveryEndpoint(const vector<uint64_t>& bits, int node) {
    size_t offset = static_cast<size_t>(node) * words;
    for (int i = 0; i < words; ++i) {
        uint64_t expected = ~0ULL;
        if (i == words - 1 && n % 64 != 0) {
            expected = (1ULL << (n % 64)) - 1;
        }
        if (bits[offset + i] != expected) {
            return false;
        }
    }
    return true;
}

void validateUniquePathsFromBranches(InStream& stream, bool juryOutput, const vector<vector<int>>& graph) {
    int nodeCount = static_cast<int>(graph.size()) - 1;
    vector<int> seen(nodeCount + 1, 0);
    vector<int> stack;
    int token = 0;

    for (int start = 1; start <= nodeCount; ++start) {
        if (graph[start].size() <= 1) {
            continue;
        }
        if (++token == numeric_limits<int>::max()) {
            fill(seen.begin(), seen.end(), 0);
            token = 1;
        }

        for (int child : graph[start]) {
            stack.push_back(child);
            while (!stack.empty()) {
                int node = stack.back();
                stack.pop_back();
                if (seen[node] == token) {
                    invalid(stream, juryOutput, "there is more than one path from node %d to node %d", start, node);
                }
                seen[node] = token;
                for (int next : graph[node]) {
                    stack.push_back(next);
                }
            }
        }
    }
}

void validateUniquePathsFromJoins(InStream& stream, bool juryOutput, const vector<vector<int>>& reverseGraph) {
    int nodeCount = static_cast<int>(reverseGraph.size()) - 1;
    vector<int> seen(nodeCount + 1, 0);
    vector<int> stack;
    int token = 0;

    for (int finish = 1; finish <= nodeCount; ++finish) {
        if (reverseGraph[finish].size() <= 1) {
            continue;
        }
        if (++token == numeric_limits<int>::max()) {
            fill(seen.begin(), seen.end(), 0);
            token = 1;
        }

        for (int parent : reverseGraph[finish]) {
            stack.push_back(parent);
            while (!stack.empty()) {
                int node = stack.back();
                stack.pop_back();
                if (seen[node] == token) {
                    invalid(stream, juryOutput, "there is more than one path from node %d to node %d", node, finish);
                }
                seen[node] = token;
                for (int prev : reverseGraph[node]) {
                    stack.push_back(prev);
                }
            }
        }
    }
}

void validateUniquePaths(
    InStream& stream,
    bool juryOutput,
    const vector<vector<int>>& graph,
    const vector<vector<int>>& reverseGraph
) {
    int branchCount = 0;
    int joinCount = 0;
    int nodeCount = static_cast<int>(graph.size()) - 1;
    for (int node = 1; node <= nodeCount; ++node) {
        if (graph[node].size() > 1) {
            ++branchCount;
        }
        if (reverseGraph[node].size() > 1) {
            ++joinCount;
        }
    }

    if (branchCount <= joinCount) {
        validateUniquePathsFromBranches(stream, juryOutput, graph);
    } else {
        validateUniquePathsFromJoins(stream, juryOutput, reverseGraph);
    }
}

Claim readClaim(InStream& stream, bool juryOutput) {
    int nodeCount = stream.readInt(2 * n, 500000, "N_tot");
    int edgeCount = stream.readInt(0, mLimit, "M");

    vector<vector<int>> graph(nodeCount + 1), reverseGraph(nodeCount + 1);
    vector<int> indegree(nodeCount + 1, 0);
    unordered_set<long long> seenEdges;
    seenEdges.reserve(static_cast<size_t>(edgeCount) * 2 + 1);

    for (int i = 0; i < edgeCount; ++i) {
        int from = stream.readInt(1, nodeCount, format("edge[%d].from", i + 1).c_str());
        int to = stream.readInt(1, nodeCount, format("edge[%d].to", i + 1).c_str());
        if (from == to) {
            invalid(stream, juryOutput, "edge %d is a self-loop on node %d", i + 1, from);
        }
        if (to <= n) {
            invalid(stream, juryOutput, "input node %d has an incoming edge", to);
        }
        if (from > n && from <= 2 * n) {
            invalid(stream, juryOutput, "output node %d has an outgoing edge", from);
        }

        long long key = (static_cast<long long>(from) << 20) ^ to;
        if (!seenEdges.insert(key).second) {
            invalid(stream, juryOutput, "edge %d duplicates direct connection %d -> %d", i + 1, from, to);
        }

        graph[from].push_back(to);
        reverseGraph[to].push_back(from);
        ++indegree[to];
    }
    if (!stream.seekEof()) {
        invalid(stream, juryOutput, "extra output after the declared edge list");
    }

    queue<int> q;
    for (int node = 1; node <= nodeCount; ++node) {
        if (indegree[node] == 0) {
            q.push(node);
        }
    }

    vector<int> topological;
    topological.reserve(nodeCount);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topological.push_back(node);
        for (int next : graph[node]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    if (static_cast<int>(topological.size()) != nodeCount) {
        invalid(stream, juryOutput, "the submitted graph contains a directed cycle");
    }

    validateUniquePaths(stream, juryOutput, graph, reverseGraph);

    vector<int> inputReachCount(nodeCount + 1), outputReachCount(nodeCount + 1);
    vector<uint64_t> endpointBits(static_cast<size_t>(nodeCount + 1) * words, 0);

    for (int input = 1; input <= n; ++input) {
        endpointBits[static_cast<size_t>(input) * words + (input - 1) / 64] |= 1ULL << ((input - 1) % 64);
    }
    for (int node : topological) {
        for (int next : graph[node]) {
            if (intersects(endpointBits, next, node)) {
                invalid(stream, juryOutput, "there is more than one path from some input to node %d", next);
            }
            mergeBits(endpointBits, next, node);
        }
    }
    for (int node = 1; node <= nodeCount; ++node) {
        inputReachCount[node] = countBits(endpointBits, node);
    }
    for (int output = n + 1; output <= 2 * n; ++output) {
        if (!hasEveryEndpoint(endpointBits, output)) {
            invalid(stream, juryOutput, "output node %d is not reachable from every input node", output);
        }
    }

    fill(endpointBits.begin(), endpointBits.end(), 0);
    for (int output = n + 1; output <= 2 * n; ++output) {
        endpointBits[static_cast<size_t>(output) * words + (output - n - 1) / 64] |=
            1ULL << ((output - n - 1) % 64);
    }
    for (auto it = topological.rbegin(); it != topological.rend(); ++it) {
        int node = *it;
        for (int prev : reverseGraph[node]) {
            if (intersects(endpointBits, prev, node)) {
                invalid(stream, juryOutput, "there is more than one path from node %d to some output", prev);
            }
            mergeBits(endpointBits, prev, node);
        }
    }
    for (int node = 1; node <= nodeCount; ++node) {
        outputReachCount[node] = countBits(endpointBits, node);
    }
    for (int input = 1; input <= n; ++input) {
        if (!hasEveryEndpoint(endpointBits, input)) {
            invalid(stream, juryOutput, "input node %d cannot reach every output node", input);
        }
    }

    for (int node = 1; node <= nodeCount; ++node) {
        long long power = 1LL * inputReachCount[node] * outputReachCount[node];
        if (power > pLimit) {
            invalid(stream, juryOutput, "node %d uses power %lld, exceeding limit %d", node, power, pLimit);
        }
    }

    return {nodeCount, edgeCount};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    mLimit = inf.readInt();
    pLimit = inf.readInt();
    words = (n + 63) / 64;

    Claim jury = readClaim(ans, true);
    Claim participant = readClaim(ouf, false);

    quitf(_ok,
          "valid router: jury=(nodes=%d edges=%d), participant=(nodes=%d edges=%d)",
          jury.nodeCount,
          jury.edgeCount,
          participant.nodeCount,
          participant.edgeCount);
}

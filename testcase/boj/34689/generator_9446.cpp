#include "testlib.h"
using namespace std;

struct Op {
    char type; // 'Q' or 'U'
    int i;
    int j;     // for Q
    char col;  // for U
};

pair<int,int> genQueryRange(int N, int varietyType) {
    if (N == 1) return {1, 1};
    int l, r;
    int t = rnd.next(0, 99);
    if (varietyType == 3) { // emphasize short ranges
        if (t < 50) {
            l = rnd.next(1, N);
            r = l;
        } else if (t < 80) {
            l = rnd.next(1, N - 1);
            r = l + 1;
        } else {
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
    } else {
        if (t < 20) { // whole range
            l = 1; r = N;
        } else if (t < 40) { // single point
            l = rnd.next(1, N);
            r = l;
        } else { // random subrange
            l = rnd.next(1, N);
            r = rnd.next(l, N);
        }
    }
    return {l, r};
}

char randomColor() {
    string nonWhite = "KRGBYCP";
    if (rnd.next(0, 3) == 0) return 'W'; // 25% white
    return nonWhite[rnd.next(0, (int)nonWhite.size() - 1)];
}

void generateRandomScenario(int N, int K, int varietyType, vector<Op>& ops) {
    vector<char> arr(N + 1, 'W');
    ops.clear();
    ops.reserve(K);

    for (int step = 0; step < K; ++step) {
        bool makeQ;
        int coin = rnd.next(0, 99);
        if (varietyType == 0) {
            makeQ = (coin < 40);
        } else if (varietyType == 1) {
            makeQ = (coin < 50);
        } else { // varietyType == 3 or others
            makeQ = (coin < 65);
        }

        if (makeQ) {
            auto pr = genQueryRange(N, varietyType);
            Op op;
            op.type = 'Q';
            op.i = pr.first;
            op.j = pr.second;
            op.col = 0;
            ops.push_back(op);
        } else {
            int pos = rnd.next(1, N);
            char c = randomColor();
            arr[pos] = c;
            Op op;
            op.type = 'U';
            op.i = pos;
            op.j = 0;
            op.col = c;
            ops.push_back(op);
        }
    }

    bool hasQ = false;
    for (auto &op : ops) if (op.type == 'Q') { hasQ = true; break; }
    if (!hasQ) {
        // Force last op to be a query over full range
        Op &op = ops.back();
        op.type = 'Q';
        op.i = 1;
        op.j = N;
        op.col = 0;
    }
}

void generateStructuredScenario(int N, int K, vector<Op>& ops) {
    // N >= 5, K >= baseOps
    int baseOps = 10;
    ops.clear();
    ops.reserve(K);
    vector<char> arr(N + 1, 'W');

    auto addU = [&](int pos, char c) {
        Op op;
        op.type = 'U';
        op.i = pos;
        op.j = 0;
        op.col = c;
        ops.push_back(op);
        arr[pos] = c;
    };
    auto addQ = [&](int l, int r) {
        Op op;
        op.type = 'Q';
        op.i = l;
        op.j = r;
        op.col = 0;
        ops.push_back(op);
    };

    // Predefined tricky pattern
    addU(1, 'R');      // R
    addU(2, 'G');      // G
    addU(3, 'B');      // B
    addQ(1, 3);        // mixture of R,G,B -> answer should be 2

    addU(4, 'W');      // white
    addQ(1, 4);        // still longest non-white segment length 2

    addU(4, 'K');      // black (all off)
    addQ(3, 4);        // B + K -> length 2
    addQ(4, 4);        // single black -> length 1

    addQ(5, N);        // all whites -> answer 0

    // Fill remaining with random ops
    while ((int)ops.size() < K) {
        int remaining = K - (int)ops.size();
        // Bias a bit towards queries here
        bool makeQ = (rnd.next(0, 99) < 60);
        if (makeQ || remaining == 1) {
            auto pr = genQueryRange(N, 1);
            addQ(pr.first, pr.second);
        } else {
            int pos = rnd.next(1, N);
            char c = randomColor();
            addU(pos, c);
        }
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 3); // 0,1,2,3

    int N, K;
    if (scenario == 0) {
        N = rnd.next(1, 5);
        K = rnd.next(1, 10);
    } else if (scenario == 1) {
        N = rnd.next(5, 15);
        K = rnd.next(5, 30);
    } else if (scenario == 2) {
        N = rnd.next(5, 10); // ensure enough room for structured pattern
        int baseOps = 10;
        K = rnd.next(baseOps, min(baseOps + 10, 30));
    } else { // scenario == 3
        N = rnd.next(2, 10);
        K = rnd.next(5, 25);
    }

    vector<Op> ops;
    if (scenario == 2) {
        generateStructuredScenario(N, K, ops);
    } else {
        int varietyType = (scenario == 3 ? 3 : scenario); // 0,1,3
        generateRandomScenario(N, K, varietyType, ops);
    }

    println(N, K);
    for (const auto &op : ops) {
        if (op.type == 'Q') {
            println("Q", op.i, op.j);
        } else {
            println("U", op.i, op.col);
        }
    }

    return 0;
}

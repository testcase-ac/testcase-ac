#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void appendPair(vector<int>& seq) {
    seq.push_back(0);
    seq.push_back(1);
}

void appendNested(vector<int>& seq, int pairs) {
    for (int i = 0; i < pairs; ++i) {
        seq.push_back(0);
    }
    for (int i = 0; i < pairs; ++i) {
        seq.push_back(1);
    }
}

void appendRandomDyck(vector<int>& seq, int pairs) {
    int opened = 0;
    int closed = 0;
    while (closed < pairs) {
        if (opened == pairs) {
            seq.push_back(1);
            ++closed;
        } else if (opened == closed || rnd.next(2) == 0) {
            seq.push_back(0);
            ++opened;
        } else {
            seq.push_back(1);
            ++closed;
        }
    }
}

void wrapOnce(vector<int>& seq) {
    seq.insert(seq.begin(), 0);
    seq.push_back(1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int pairs = rnd.next(1, 30);
    vector<int> seq;

    if (mode == 0) {
        for (int i = 0; i < pairs; ++i) {
            appendPair(seq);
        }
    } else if (mode == 1) {
        appendNested(seq, pairs);
    } else if (mode == 2) {
        appendRandomDyck(seq, pairs);
    } else if (mode == 3) {
        int remaining = pairs;
        while (remaining > 0) {
            int blockPairs = rnd.next(1, min(remaining, 8));
            if (rnd.next(3) == 0) {
                appendNested(seq, blockPairs);
            } else {
                appendRandomDyck(seq, blockPairs);
            }
            remaining -= blockPairs;
        }
    } else {
        int corePairs = rnd.next(1, pairs);
        appendRandomDyck(seq, corePairs);
        for (int i = 0; i < pairs - corePairs; ++i) {
            if (rnd.next(2) == 0) {
                wrapOnce(seq);
            } else {
                appendPair(seq);
            }
        }
    }

    println(static_cast<int>(seq.size()));
    for (int token : seq) {
        println(token);
    }

    return 0;
}

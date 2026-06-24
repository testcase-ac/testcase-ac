#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int n;

struct Answer {
    vector<int> a;
};

bool isSortedNondecreasing(const vector<int>& a) {
    return is_sorted(a.begin(), a.end());
}

vector<int> runWrongBubbleSort(vector<int> a) {
    for (int i = n - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
    return a;
}

Answer readAnswer(InStream& stream) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = stream.readInt(0, 10000, format("A[%d]", i).c_str());
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the sequence");
    }

    vector<int> sortedByWrongCode = runWrongBubbleSort(a);
    if (isSortedNondecreasing(sortedByWrongCode)) {
        stream.quitf(_wa, "the submitted sequence is sorted correctly by the wrong bubble sort");
    }

    return {a};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(3, 1000, "N");

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid counterexample");
}

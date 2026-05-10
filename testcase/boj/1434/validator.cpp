#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Problem does not mention multiple test cases, so read exactly one.

    int N = inf.readInt(1, 50, "N");
    inf.readSpace();
    int M = inf.readInt(1, 50, "M");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    vector<int> B = inf.readInts(M, 1, 1000, "B_j");
    inf.readEoln();

    // Simulate the packing procedure to ensure that
    // "모든 책을 박스에 넣을 수 있는 경우만 입력으로 주어진다."
    int boxIdx = 0;   // 0-based index for current box
    int bookIdx = 0;  // 0-based index for current book
    int curUsed = 0;  // used capacity in current box

    while (bookIdx < M && boxIdx < N) {
        if (curUsed + B[bookIdx] <= A[boxIdx]) {
            // Step 2: put current book into current box
            curUsed += B[bookIdx];
            ++bookIdx;
        } else {
            // Step 3: seal this box and go to next
            ++boxIdx;
            curUsed = 0;
        }
    }

    // All books must be packed, and we must not exceed number of boxes
    ensuref(bookIdx == M, "Not all books can be packed: packed %d out of %d", bookIdx, M);
    ensuref(boxIdx < N, "Needed more than N boxes to pack all books");

    inf.readEof();
}

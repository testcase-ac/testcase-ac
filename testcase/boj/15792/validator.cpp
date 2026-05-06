#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 입력: 첫째 줄에 A와 B가 주어진다. (0 < A, B ≤ 10,000)
    int A = inf.readInt(1, 10000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 10000, "B");
    inf.readEoln();

    // 추가로 검사할 전역 조건은 없다 (항상 A/B는 정의됨).

    inf.readEof();
}

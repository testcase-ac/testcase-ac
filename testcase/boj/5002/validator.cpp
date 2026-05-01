#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read X: "가장 큰 차이 X<100"
    // X is a non-negative integer, and strictly less than 100.
    int X = inf.readInt(0, 99, "X");
    inf.readEoln();

    // Read queue string: "둘째 줄에는 줄을 서 있는 순서가 주어진다.
    // W는 여성, M은 남성을 나타내며, 길이는 최대 100이다."
    // Length can be 0..100 (empty line allowed), and only 'W' or 'M'.
    string s = inf.readLine("[WM]{0,100}", "queue");

    // No further global constraints given in the statement that must
    // be enforced at validation level. The "answer" is not bounded
    // beyond trivial (<= length), so we do not compute/simulate here.

    inf.readEof();
}

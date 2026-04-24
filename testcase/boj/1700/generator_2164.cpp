#include "testlib.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 5); // 멀티탭 구멍 개수
    int k = rnd.next(1, 10); // 전기 용품 총 사용 횟수

    cout << n << " " << k << endl;

    for (int i = 0; i < k; ++i) {
        cout << rnd.next(1, k);
        if (i < k - 1) {
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}

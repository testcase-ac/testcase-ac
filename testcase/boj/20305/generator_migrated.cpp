//NnaxhO님 제너레이터 코드에서 범위를 수정했습니다.
//대부분의 경우에 testcase.ac에서 짤릴 정도로 긴 테스트케이스를 출력하여 반례 찾기에 도움이 되기 어렵다고 판단했습니다.
#include <iostream>
#include <random>

using namespace std;
using ui = unsigned int;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<ui> distN(1, 50);
uniform_int_distribution<ui> distQ(1, 100);

int main() {
    ios_base::sync_with_stdio(false);

    ui N = distN(gen), Q = distQ(gen);
    cout << N << '\n' << Q << '\n';

    uniform_int_distribution<ui> distL(1, N);
    uniform_int_distribution<ui> distR(1, N);

    while(Q--) {
        ui l = distL(gen);
        distR.param(uniform_int_distribution<ui>::param_type(l, N));
        ui r = distR(gen);
        cout << l << ' ' << r << '\n';
    }

    return 0;
}

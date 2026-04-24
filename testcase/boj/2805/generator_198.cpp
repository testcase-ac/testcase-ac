#include "testlib.h"
#include <vector>
using namespace std;
int LEN_MIN = 1;
int LEN_MAX = 8;
int ELEM_MIN = 0;
int ELEM_MAX = 10;
vector<int> generate_vec() {
    int N = rnd.next(LEN_MIN, LEN_MAX);
    vector<int> v;
    for (int i = 0; i < N; i++) {
        v.push_back(rnd.next(ELEM_MIN, ELEM_MAX));
    }
    return v;
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> a;
    int sum;
    while(true) {
        a = generate_vec();
        sum = 0;
        for (int i = 0; i < a.size(); i++) {
            sum += a[i];
        }
        if(sum) {
            break;
        }
    }
    int M = rnd.next(1, sum);
    println(a.size(), M);
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", a[i]);
        if(i == a.size()-1) {
            printf("\n");
        }
    }
}

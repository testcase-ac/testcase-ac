#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int init = rnd.next(2, 4);
    int n = rnd.next(8, 16);

    vector<int> arr;
    for (int i = 0; i < init; i++) { arr.push_back(rnd.next(0, 2)); }
    while (arr.size() < n) {
        int split = rnd.next(arr.size());
        arr[split]--;
        arr.insert(arr.begin()+split, arr[split]);
    }
    int m = *min_element(arr.begin(), arr.end());

    println(n);
    for (int x : arr) {
        println(x-m+1);
    }

    return 0;
}

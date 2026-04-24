#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int MX = 9;
    if(rnd.next() < 0.5) {
        MX = 100; // larger testcase
    }
    int N = rnd.next(2, MX);
    println(N);
    // First, choose how many kind of number to ever choose from
    vector<int> nums(MX);
    for(int i=0; i<nums.size(); ++i) {
        nums[i] = i+1;
    }
    int cnt = rnd.next(1, N);
    shuffle(nums.begin(), nums.end());
    nums.erase(nums.begin()+cnt, nums.end());
    sort(nums.begin(), nums.end());

    // Then, sample N numbers
    vector<int> res(N);
    for(int i=0; i<N; ++i) {
        res[i] = nums[rnd.next(0, (int)nums.size()-1)];
    }

    // Then, sometimes make it almost sorted
    double p = rnd.next();
    if(p < 0.3) {
        sort(res.begin(), res.end());
    } else if(p < 0.6) {
        sort(res.begin(), res.end(), greater<int>());
    }
    int shuffle_cnt = rnd.next(0, N);
    for(int i=0; i<shuffle_cnt; ++i) {
        swap(res[rnd.next(0, N-1)], res[rnd.next(0, N-1)]);
    }

    println(res);   
}

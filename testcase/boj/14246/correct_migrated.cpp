// 출처: https://velog.io/@publicminsu/C%EB%B0%B1%EC%A4%80-14246-K%EB%B3%B4%EB%8B%A4-%ED%81%B0-%EA%B5%AC%EA%B0%84

#include <iostream>
#include <vector>
using namespace std;
vector<int> nums;
int n, k, l, r;
long long answer, sum;
int main()
{
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> n;
    nums = vector<int>(n);
    for (int &num : nums)
    {
        cin >> num;
    }
    cin >> k;

    while (true)
    {
        if (sum > k) // 합이 k보다 큰 경우
        {
            answer += n - r + 1;
            sum -= nums[l++];
            if (l > n) // 범위를 벗어난 경우
            {
                break;
            }
        }
        else
        {
            sum += nums[r++];
            if (r > n) // 범위를 벗어난 경우
            {
                break;
            }
        }
    }
    cout << answer;
    return 0;
}

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int* sum;
int get_sum(int start, int count){
    return sum[start+count] - sum[start];
}

bool make_weight(int* packs, int n, int start, int count, int weight){
    if(start <= n - count + 1){
        int start_sum = get_sum(start, count);
        if(start_sum > weight)
            return false;
        else if(start_sum == weight)
            return true;

        int end_sum = get_sum(n-count, count);
        if(end_sum < weight)
            return false;
        else if(end_sum == weight)
            return true;
    }
    else
        return false;
    count--;

    if(count == 0){
        for(int i = start; i < n; i++)
            if(packs[i] == weight){
                return true;
            }
        return false;
    }

    for(int i = start; i < n - count; i++){
        if((weight-packs[i]) < 0)
            return false;
        if(make_weight(packs, n, i+1, count, weight-packs[i]))
            return true;
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int w, n;
    cin >> w >> n;
    int* packs = new int[n];
    for(int i = 0; i < n; i++){
        cin >> packs[i];
    }
    sort(packs, packs+n);

    sum = new int[n+1];
    sum[0] = 0;
    for(int i = 1; i <= n; i++){
        sum[i] = sum[i-1] + packs[i-1];
    }

    if(make_weight(packs, n, 0, 4, w))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}

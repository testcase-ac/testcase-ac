// BOJ 8916 이진 검색 트리
#include <bits/stdc++.h>
 
using namespace std;
 
long long comb(int n, int r) { // nCr
    r = n - r > r ? r : n - r;
    long long result = 1;
    for (int i = 0; i < r; i++)
        result *= n - i;
    for (int i = 2; i <= r; i++)
        result /= i;
    return result;
}
 
struct node {
    int value = -1;
    int lcnt = 0; // 좌측 자식 수
    int rcnt = 0; // 우측 자식 수
    int left = -1;// 좌측 자식 인덱스
    int right = -1;// 우측 자식 인덱스
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    int tc;
    cin >> tc;
    while (tc--) {
        int num, input;
        vector<node> tree(1);
        cin >> num;
        while(num--) {
            int idx = 0; // 루트노드 인덱스
            cin >> input;
            while (true) {
                // 빈노드이면 값 추가
                if (tree[idx].value == -1) {
                    tree[idx].value = input;
                    break;
                    // 입력 값이 부모노드보다 작을 경우
                } else if (input < tree[idx].value) {
                    // 자식노드 카운팅
                    tree[idx].lcnt++;
                    // 좌측 자식이 존재하지 않을 경우
                    if (tree[idx].left == -1) {
                        // 자식 추가
                        tree.push_back({});
                        tree[idx].left = tree.size() - 1;
                    }
                    idx = tree[idx].left; // 인덱스 저장
                } else {
                    tree[idx].rcnt++;
                    if (tree[idx].right == -1) {
                        tree.push_back({});
                        tree[idx].right = tree.size() - 1;
                    }
                    idx = tree[idx].right;
                }
            }
        }
        long long result = 1;
        for (node i : tree)
            result = (result * comb(i.lcnt + i.rcnt, i.lcnt)) % 9999991;
        cout << result << '\n';
    }
    return 0;
}

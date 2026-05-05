#include <iostream>
using namespace std;
// 제 코드가 아니며, 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
int s[51][51], arr[5000001];
int main(void){
	cin.tie(0);
	ios::sync_with_stdio(0);

	long long int answer = 0;
	int n; cin >> n;
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
		cin >> s[i][j];
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= n; j++)
		s[i][j] = s[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	

	for (int i = 1; i <= n - 1; i++)
	for (int j = 1; j <= n - 1; j++){
		for (int x = 1; x <= i; x++)
		for (int y = 1; y <= j; y++){
			int sum = s[i][j] - s[i][y - 1] - s[x - 1][j] + s[x - 1][y - 1] + 2500000;
			arr[sum]++;
		}
		for (int x = i + 1; x <= n; x++)
		for (int y = j + 1; y <= n; y++){
			int sum = s[x][y] - s[x][j] - s[i][y] + s[i][j] + 2500000;
			answer += arr[sum];
		}
		for (int x = 1; x <= i; x++)
		for (int y = 1; y <= j; y++){
			int sum = s[i][j] - s[i][y - 1] - s[x - 1][j] + s[x - 1][y - 1] + 2500000;
			arr[sum] = 0;
		}
	}

	for (int i = 1; i <= n - 1; i++)
	for (int j = 2; j <= n; j++){
		for (int x = 1; x <= i; x++)
		for (int y = j; y <= n; y++){
			int sum = s[i][y] - s[i][j - 1] - s[x - 1][y] + s[x - 1][j - 1] + 2500000;
			arr[sum]++;
		}
		for (int x = i + 1; x <= n; x++)
		for (int y = 1; y <= j - 1; y++){
			int sum = s[x][j - 1] - s[x][y - 1] - s[i][j - 1] + s[i][y - 1] + 2500000;
			answer += arr[sum];
		}
		for (int x = 1; x <= i; x++)
		for (int y = j; y <= n; y++){
			int sum = s[i][y] - s[i][j - 1] - s[x - 1][y] + s[x - 1][j - 1] + 2500000;
			arr[sum] = 0;
		}
	}

	cout << answer;
	return 0;
}

#include <iostream>
#include <cmath>
#include <complex>
using namespace std;

#define N 1048576
typedef long long int ll;
typedef complex<double> cd;
bool visit[N];
cd arr[N];
const double PI = acos(-1);
char r[900000];
int p;
inline int f(){
	int answer = 0, x;
	while (1){
		x = r[p++];
		if (x == '\n' || x == ' ') break;
		answer = answer * 10 + (x & 0x0F);
	}
	return answer;
}
int main(void){
	cin.tie(0);
	ios::sync_with_stdio(0);

	auto DFT = [&](bool flag){
		for (int i = 1, j = 0, k; i < N; i++){
			for (k = N / 2; j >= k; k /= 2) j -= k; j += k;
			if (i < j) swap(arr[i], arr[j]);
		}
		for (int dx = 2; dx <= N; dx *= 2){
			cd x(cos(2 * PI / dx), flag ? -sin(2 * PI / dx) : sin(2 * PI / dx));
			for (int i = 0; i < N; i += dx){
				cd k = 1;
				for (int j = 0; j < dx / 2; j++, k *= x){
					cd w1 = arr[i + j], w2 = arr[i + j + dx / 2];
					arr[i + j] = w1 + w2 * k, arr[i + j + dx / 2] = w1 - w2 * k;
				}
			}
		}
	};
	for (int i = 2; i * i < N; i++)
	if (!visit[i])
	for (int j = i * i; j < N; j += i)
		visit[j] = true;
	for (int i = 3; i < N; i += 2) if (!visit[i]) arr[i / 2] = 1;
	DFT(false);
	for (int i = 0; i < N; i++) arr[i] *= arr[i];
	DFT(true);
	for (int i = 0; i < N; i++) arr[i] /= N;

	fread(r, 1, 900000, stdin);
	int testcase = f();
	while (testcase--){
		int n = f();
		if (n == 4) cout << "1\n";
		else {
			ll answer = round(arr[(n - 2) / 2].real());
			if (!visit[n / 2]){
				cout << (answer - 1) / 2 + 1 << '\n';
			}
			else{
				cout << answer / 2 << '\n';
			}
		}
	}
	return 0;
}

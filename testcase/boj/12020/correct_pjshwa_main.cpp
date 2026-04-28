#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<queue>
#include<deque>
#include<set>
#include<map>
#include<math.h>
#include<algorithm>
#include<assert.h>
using namespace std;

#define INF 1234567890
#define ll long long
#define mat vector<vector<double> >

mat mul(mat a, mat b)
{
	mat c(a.size(), vector<double>(b[0].size()));
	for (int i = 0; i < a.size(); i++)
		for (int j = 0; j < b[0].size(); j++)
			for (int k = 0; k < b.size(); k++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}

mat InputMatrix() {
	int N;
	cin >> N;
	mat ret(N, vector<double>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
        {
            int tmp;
            cin >> tmp;
            ret[i][j] = tmp;
        }
	return ret;
}

void MakeLU() {
	mat A = InputMatrix(), PA = A;
	int N = A.size();
	mat L(N, vector<double>(N));
	for (int i = 0; i < N; i++)
		L[i][i] = 1;

	// 가우스 소거법
	for (int i = 0; i < N; i++) {
		// 행 교환 연산
		if (abs(A[i][i]) < 1e-9) {
			for (int j = i + 1; j < N; j++) {
				if (abs(A[j][i]) >= 1e-9) {
					for (int k = 0; k < N; k++)
						swap(A[i][k], A[j][k]);
					for (int k = 0; k < i; k++)
						swap(L[i][k], L[j][k]); //
					break;
				}
			}
		}
		if (abs(A[i][i]) < 1e-9)
		{
			printf("-1");
			return;
		}

		for (int j = i + 1; j < N; j++) {
			double cnt = -A[j][i] / A[i][i];
			for (int k = 0; k < N; k++)
				A[j][k] += A[i][k] * cnt;
			A[j][i] = 0;
			L[j][i] = -cnt;
		}
	}
	mat U = A;

	mat LU = mul(L, U);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (abs(PA[i][j] - LU[i][j]) > 0.99)
			{
				printf("-1");
				return;
			}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			printf("%.3f%c", L[i][j], " \n"[j + 1 == N]);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			printf("%.3f%c", U[i][j], " \n"[j + 1 == N]);
}

int main()
{
	MakeLU();
	return 0;
}

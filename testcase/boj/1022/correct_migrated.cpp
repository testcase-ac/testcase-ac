#include <stdio.h>
#include <math.h>
// 제 코드가 아니며, 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ABS(a) (((a) > 0) ? (a) : (-a))

int getNumber(int x, int y) {
	int curMaxIndex = -MAX(ABS(x), ABS(y));
	int curMaxNumber = pow(2 * ABS(curMaxIndex) + 1, 2) - 4 * ABS(curMaxIndex);
	return curMaxNumber + ((x - curMaxIndex) < (y - curMaxIndex) ? -1 : 1) * ((x - curMaxIndex) + (y - curMaxIndex));
}

int main() {
	int r1, c1, r2, c2;
	scanf("%d %d %d %d", &r1, &c1, &r2, &c2);

	int maxIndex = -MAX(ABS(r1), MAX(ABS(c1), MAX(ABS(r2), ABS(c2))));
	int maxNumber = MAX(getNumber(r1, c1), MAX(getNumber(r1, c2), MAX(getNumber(r2, c1), getNumber(r2, c2))));
	int temp = maxNumber, maxIntSize = 0, result, x, y;
	while (temp != 0) {
		temp /= 10;
		maxIntSize++;
	}

	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			int result = getNumber(i, j), wordSize = 0;
			temp = result;
			while (temp != 0) {
				temp /= 10;
				wordSize++;
			}
			for (int k = 0; k < maxIntSize - wordSize; k++) printf(" ");
			printf("%d ", result);
		}
		printf("\n");
	}

	return 0;
}

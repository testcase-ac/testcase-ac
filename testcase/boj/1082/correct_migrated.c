#include <stdio.h>
int main() {
		
		int countN = 0;		//n 숫자 카운트
		int minCost = 50;	//최소금액 
		int tempCost = 50;	//최소금액 
		int output[50];		//출력문 배열
		int roomCost[50];	//방 가격 배열
		int balance;		//잔고 
		int tempbalance;     
		int i;				//for문 통제
		int room;			//방 가격
		int check = 0;		//구매한 방 숫자 
		int minPoint =0;		//최소금액 위치
		int tempPoint =0;		//최소금액 위치가 0일경우 두번째 최소금액위치
		
		
		//방개수 입력			
        scanf("%d",&countN);
		for (i = 0; i < countN; i++) {
			scanf("%d",&room);
			roomCost[i] = room;
			if (minCost >= room) {
				minCost = room;
				minPoint = i;
			}

			if (i >= 1) {
				if (tempCost >= room) {
					tempCost = room;
					tempPoint = i;
				}
			}
		}//방 가격 입력

		//금액입력
		scanf("%d",&balance);			
		tempbalance = balance;

		//최대 자리수 설정
		while(tempbalance >= minCost) {
            if (minPoint == 0 && check == 0 && tempbalance < tempCost) {
				tempbalance = 0;
                output[check] = 0;
                check = 1;
			}
            else if (minPoint == 0 && check == 0 && tempbalance >= tempCost) {
				output[check] = tempPoint;
				tempbalance = tempbalance - tempCost;
				check++;
			}
			else {
				output[check] = minPoint;
				tempbalance = tempbalance - minCost;
				check++;
			}
		}
		
		i = 0;
		int a = check-1;
        //계산
		while (i < check && balance >= minCost*(a-i)) {
			if (balance >= ( minCost*(a-i) +roomCost[countN - 1] ) ) {
				output[i] = countN - 1;
				i = i +1;
				balance = balance - roomCost[countN-1];
			}
			else {
				countN = countN -1;
			}
		}

       
            for (i = 0; i < check; i++) {
			printf("%d",output[i]);
		    }
            printf("\n");
     return 0;
	}

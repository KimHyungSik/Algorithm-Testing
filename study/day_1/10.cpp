//10. 성적처리
//1) 정답지 배열
//dap[10] = { 1,1,2,3, };
//2) 학생답지배열
//stdap[10] = {};
//3) 채점 학생 별로 점수 저장
//1개 * 10점
//4) 출력형식
//학번	답안 채점 ox결과  점수
//5) 조건
//2차원 배열
#include <stdio.h>

int main() {
	int dap[] = { 1,2,3,4,5,1,2,3,4,5 }, cnt=0;
	int student[4];
	int stdap[5][10] = {
		{1,4,2,3,5,3,4,3,1,3},
		{1,},
		{1,4,2,3,5,1,4,3,1,3},
		{ 1,2,3,4,5,1,2,3,4,5 },
		{2,4,2,3,2,2,4,1,2,3},
	};

	for (int i = 0; i < 5; i++) {
		cnt = 0;
		printf("학번: %d 채점: ", i + 1);
		for (int j = 0; j < 10; j++) {
			if (stdap[i][j] == dap[j]) {
				cnt++;
				printf("O ");
			}
			else {
				printf("X ");
			}
		}
		printf("채점 결과 : %d\n", 10 * cnt);
	}
}

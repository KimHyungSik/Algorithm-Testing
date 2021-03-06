#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define box '\x25a0'

void textcolor(int color_number){ //콘솔창 출력색상을 나타내는 함수
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

// 커서좌표이동
void gotoxy(unsigned int x, unsigned int y){
	COORD xy = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}


// 색상변경
void set_color(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

//현재 커서 좌표 추출
COORD get_cursor(){
	COORD cur;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cur.X = curInfo.dwCursorPosition.X;
	cur.Y = curInfo.dwCursorPosition.Y;
	return cur;
}

//커서숨기기/보이기
void cursor_view(char s) {      // 0넣으면숨기기, 1넣으면보이기
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = s;
	ConsoleCursor.dwSize = 2;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void keyDown(int (*printing)[100],int* color) {
	int key;
	COORD position = get_cursor();
	int x = position.X;
	int y = position.Y;
	while (1) {

		if (_kbhit())
		{
			key = _getch();
			if (key == 224 || key == 0){
				key = _getch();
				switch (key)
				{
				case 72:
					if (y == 1) 
						break;
					gotoxy(x, y-1);
					break;
				case 75:
					if (x == 0)
						break;
					gotoxy(x -1, y);
					break;
				case 77:
					if (x == 99)
						break;
					gotoxy(x + 1, y);
					break;
				case 80:
					if (y == 99)
						break;
					gotoxy(x, y+1);
					break;
				default:
					break;
				}
			}
			else {
				if (key == 13) {
					printing[x][y] = *color;
				}
				else if (key == 32) {
					*color = *color + 1;
				}
			}
		return;
		}
	}
}

int main() {
	COORD position;
	int tempX, tempY, color =1;
	int printing[50][100] = { 0, };

	//consol 창  크기
    system("mode con cols=100 lines=50");
	gotoxy(0, 1);
	while (1){
		keyDown(printing, &color);
		position = get_cursor();
		tempX = position.X;
		tempY = position.Y;
		cursor_view(0);
		gotoxy(0, 0);
		set_color(color, 0);
		printf("O <- 스페이스로 색을 변경하여 엔터로 그림음 그립니다.");
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 50; j++) {
				if (printing[j][i]) {
					set_color(printing[j][i], 0);
					gotoxy(j, i);
					printf("O");
				}

			}
		}
		cursor_view(1);
		gotoxy(tempX, tempY);
	}
       // 콘 솔창 전체 내용 지우기

        
    // SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {X좌표, Y좌표});
    // STD_OUTPUT_HANDLE ===> 출력  콘솔 창을 의미함
    COORD cur = get_cursor();

    printf("cursor x = %d  y = %d",cur.X, cur.Y);
}

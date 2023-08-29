#include <stdio.h>
#include <graphics.h>
#include "tools.h"
#define WIN_WIDTH 1000
#define WIN_HEIGHT 600
enum { WAN_DOU, XING_RI_KIU, JIAN_GUO , PATATOMINE, THREE_WAN_DOU,ZHIWU_COUNT };
IMAGE imgbg;
IMAGE imgbar;
IMAGE imgcards[ZHIWU_COUNT];
IMAGE imgmove[ZHIWU_COUNT];

int curX, curY, curZhiWu;//当前移动的植物的坐标
void gameinit() {
	loadimage(&imgbg, "res/res/Map/map0.jpg");
	loadimage(&imgbar, "res/res/Screen/bar0(1).png");
	char name1[64];
	char name2[64];
	for (int i = 0; i < ZHIWU_COUNT; i++) {
		sprintf_s(name1, sizeof(name1), "res/res/Cards/card_%d.png", i + 1);
		loadimage(&imgcards[i], name1);
		sprintf_s(name2, sizeof(name2), "img/move/zhiwu/%d.png", i + 1);
		loadimage(&imgmove[i], name2);
		}
	curZhiWu = 0;

	initgraph(WIN_WIDTH, WIN_HEIGHT, 1);

}
void userClick() {
	ExMessage msg;
	static int status = 0;
	if (peekmessage(&msg)) {
		if ((msg.message) == WM_LBUTTONDOWN) {
			if ((msg.x >= 492 && msg.x <= 988 ) && msg.y <= 90) {
				int index = (msg.x - 492) / 62;
				curZhiWu = index + 1;
				status = 1;
				printf("%d", curZhiWu);
			}
		}
		else if ((msg.message) == WM_MOUSEMOVE && status == 1) {
			curX = msg.x;
			curY = msg.y;



		}
		else if ((msg.message) == WM_LBUTTONUP) {

		}
	}
}
void updateWindow() {
	BeginBatchDraw();//双缓冲
	putimage(0, 0, &imgbg);
	putimagePNG(400, 0, &imgbar);
	for (int i = 0; i < ZHIWU_COUNT; i++) {
		putimagePNG(492 + i * 62, 5, &imgcards[i]);
		if (curZhiWu > 0) {
			putimagePNG(curX, curY, &imgmove[curZhiWu - 1]);
		}
	}
	EndBatchDraw();//结束缓冲打印图片
}

int main(void) {
	gameinit();
	while (1) {
		userClick();
		updateWindow();
	}

	system("pause");
	return 0;
}

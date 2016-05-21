#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320


#define RIGHT_ARROW 0x68
#define LEFT_ARROW 0x6B

int player_x = 0;
int player_speed = 10;
clock_t currentTime = clock();
clock_t nextTime;
int fpsCounter = 0;
int frameAccumulator = 0;
int fps(){
	nextTime = clock();
	double result = ((float)(nextTime - currentTime) / CLOCKS_PER_SEC) * 1000;
	if(result >= 1000.0){
		currentTime = nextTime;
		fpsCounter = frameAccumulator;
		frameAccumulator = 0;
	}
	frameAccumulator += 1;
	return fpsCounter;
}


void buffer(int page){
	setvisualpage(page);
	while((inp(0x3DA) & 0X08));
	while(!(inp(0X3DA) & 0X08));
	setactivepage(!page);
	clearviewport();
}

void update(int key){
	if(key == LEFT_ARROW)
		player_x += player_speed;
	else if(key == RIGHT_ARROW)
		player_x -= player_speed;
}
void render(){
	circle(player_x, 10, 10);
	char fps_buffer[10];
	sprintf(fps_buffer, "FPS: %d", fps());

	outtextxy(10, 10, fps_buffer);
}


void main() {
	int gd=EGA, gm=EGAHI;
	setgraphbufsize(1000);
	initgraph(&gd, &gm , "c:/tc/bgi");

	int page = 0;
	while(1) {
		int key = 0;
		if(kbhit()){
			key = getch();
		}
		buffer(page);
		page = !page;
		update(key);
		render();

		if(key == 27){
			break;
		}

	}
	closegraph();
	restorecrtmode();
}
#include <graphics.h>
#include <conio.h>
#include <dos.h>

void main() {
	int gd=EGA, gm=EGAHI;
	//setgraphbufsize(1000);
	initgraph(&gd, &gm , "c:/tc/bgi");

	int offsetx = 0;
	int page = 0;
	while(!kbhit()) {
		setvisualpage(page);

		while((inp(0x3DA) & 0X08));
		while(!(inp(0X3DA) & 0X08));
		setactivepage(!page);

		clearviewport();
		circle(30 + offsetx, 180, 100);
		offsetx += 1;
		//delay(10);

		page = !page;
	}
	getch();
	closegraph();
	restorecrtmode();
}
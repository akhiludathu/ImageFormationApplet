using namespace std;
#include<iostream>
#include<math.h>
#include "graphics.h"
#include<fstream>
#include "base.h"

//1.PROTOTYPES AND GLOGAL VARIABLE DECLARATIONS
void disp(base b);
extern void swindow(int);
//END OF 1

struct saveb{
       int k;
       float x, y;
       bool operator==(saveb &t){if(k==t.k && x==t.x && y==t.y) return 1;}
};

//3.THE CHAIN INITIATORS!!
void nwindow(){
	int c;
        cout << "1.Lens\n2.Mirror\n";
		cin >> c;
		base b(c - 1);
		cout << "\nInitial conditions created";
		cout << "\nDrawing...";
		x = initwindow(1360, 650, "Draw");
		b.draw();
		disp(b);
		closegraph(x);
}

void swindow(int k){
     fstream f;
     int xy;
     if(k)f.open("mirr.dat", ios::in | ios::binary);
     else  f.open("lens.dat", ios::in | ios::binary);
     
     saveb s;
     
     while(f.read((char*)&s, sizeof(s))) cout<<endl<<s.k<<"\t"<<s.x<<"\t"<<s.y;
     cout<<"\nEnter number:";
     cin>>xy;
     f.seekg(sizeof(s)*(xy-1), ios::beg);
     cout<<s.x<<s.y;
     base b(k, s.k, s.x, s.y);
     f.close();
     x = initwindow(1360, 650, "Draw");
     b.draw();
     disp(b);
     closegraph(x);
}

int main(){
    int c;
    do{
        cin>>c;
        switch(c){
                  case 1:nwindow();break;
                  case 2:swindow(1);break;//MIRR      
                  case 3:swindow(0);break;//LENS
        }
    }while(c);
}
//END OF 3

//4.FUNCTIONS FOR DISPLAY
void drawbox(bool c){
     //Object dist
	rectangle(65, 600, 90, 625);
	outtextxy(75, 605, "-");
	outtextxy(95, 605, "obj dis");
	rectangle(140, 600, 165, 625);
	outtextxy(150, 605, "+");
	
	//Focal Length
	rectangle(200, 600, 225, 625);
	outtextxy(210, 605, "-");
	outtextxy(230, 605, "focal l");
	rectangle(275, 600, 300, 625);
	outtextxy(285, 605, "+");
	
	//Object height
	rectangle(335, 600, 360, 625);
	outtextxy(345, 605, "-");
	outtextxy(365, 605, "obj h");
	rectangle(410, 600, 435, 625);
	outtextxy(420, 605, "+");
	
	//Save
	if(c)outtextxy(1096, 602, "D");
	rectangle(1060,600,1109,625);
	outtextxy(1063, 602, "SAVE");
	
	//EXIT
	rectangle(1130, 600, 1175, 625);
	outtextxy(1135, 602, "EXIT");
}

void disp(base b){
	int mx, my;
	drawbox(b.save);
	while (!kbhit()){
		if (ismouseclick(WM_LBUTTONUP)){
			getmouseclick(WM_LBUTTONUP, mx, my);
			if (my > 600 && my < 625){
				if (mx < 90 && mx>65) b.shob(0);
				else if (mx > 140 && mx < 165) b.shob(1);
				else if (mx > 200 && mx < 225) b.shof(0);
				else if (mx > 275 && mx < 300) b.shof(1);
				else if (mx > 335 && mx < 360) b.inob(0);
				else if (mx > 410 && mx < 435) b.inob(1);
				else if (mx > 1130 && mx < 1175){ b.close(); return;}
				else if (!b.save) if (mx > 1060 && mx < 1105)b.saveb();
				drawbox(b.save);
			}
		}
	}
}

using namespace std;
#include<iostream>
#include<math.h>
#include "graphics.h"
#include<fstream>
#include "base.h"

void disp(base b);
extern void swindow(int);
extern void reset();

struct saveb{
       int k;
       float x, y;
       bool operator==(saveb &t){if(k==t.k && x==t.x && y==t.y) return 1;}
};

void nwindow(){
	int c;
        cout << "1.Lens\n2.Mirror\n";
		cin >> c;
		base b(c - 1);
		x = initwindow(1360, 650, "Draw");
		b.draw();
		disp(b);
		closegraph(x);
}

void swindow(int k){
     fstream fkey;
     int num[2];
     saveb b;    
    
	 fkey.open("key.dat", ios::in|ios::binary);
     fkey.read((char*)num, sizeof(num));
     fkey.close();
     
     if(!num[k]){cout<<"\nNo Records Found\n"; system("pause");
                  return;}
     
     ifstream f;
     if(k)f.open("mirr.dat", ios::binary|ios::in);
     else  f.open("lens.dat", ios::in|ios::binary);
     
     cout<<"Slno\t";
     if(k)cout<<"Radius\t";
     else cout<<"Focal l\t";
     cout<<"Obj Dist\tObj Ht";
     
     for(int i=0; i<num[k]; i++){
             f.read((char*)&b,sizeof(b));
             cout<<endl<<i+1<<"\t"<<b.k<<"\t"<<b.x<<"\t\t"<<b.y;
     }
     
     cout<<"\nEnter Number:";
     int x; cin>>x;
     
     f.seekg((x-1)*sizeof(b), ios::cur);
     f.read((char*)&b, sizeof(b));
     
     base s(k, b.k, b.x, b.y);

     x = initwindow(1360, 650, "Draw");
     s.draw();
     disp(s);
     closegraph(x);
}

int main(){
    int c;
    do{
        system("cls");
        cout<<"1.Create new\n2.Open saved mirror\n3.Open saved lens\n4.Reset saved data\n0.Exit\nEnter Choice:";
        cin>>c;
        switch(c){
                  case 1:nwindow();break;
                  case 2:swindow(1);break;//MIRR      
                  case 3:swindow(0);break;//LENS
                  case 4:reset();
        }
    }while(c);
}
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

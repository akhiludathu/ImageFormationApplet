using namespace std;
#include<iostream>
#include<math.h>
#include "graphics.h"

//CONVERT FLOAT TO CHAR
char ch(int a){ switch (a){ case 1:return '1'; case 2:return '2'; case 3:return '3';
                            case 4:return '4'; case 5:return '5'; case 6:return '6';
                            case 7:return '7'; case 8:return '8'; case 9:return '9'; 
                            case 0:return '0'; } }

char* conv(float b){
	char st[6];
	int a=b*100;
	st[0]= a>=0? '+' : '-';
	if(a<0)a=-1*a;
	st[1]=ch(a/1000); a=a%1000;
	st[2]=ch(a/100); a=a%100;
	st[3]='.';
	st[4]=ch(a/10); a=a%10;
	st[5]=ch(a);
	st[6]='\0';
	return st;
}
//END OF FUNCTION

int xelem = 680, ypa = 325, s=15;
struct point { float x, y; };
int x;
class base;

extern int savebase(int, int, float, float);

class elem{
      public:
	virtual void draw() = 0;
	virtual point form(point) = 0;
	friend class base;
	virtual int retf()=0;
	virtual void shof(bool)=0;
};

class mirr : public elem{
	int r;
	friend class base;
public:
       mirr(int rad){
		r = rad;
	}
	mirr(){cout<<"in mirror";}
	
	point form(point o){
		point i;
		i.x = (r*o.x) / ((2 * o.x) - r);
		i.y = -1.0*(o.y*i.x) / o.x;
				if(o.x<0 && i.x<0)xelem=1300;
				else xelem=680;
		return i;
	}
	void draw(){
		cout << "\nDrawing mirr!! "<<r<<endl;
		line(r*15+xelem,ypa-2,r*15+xelem,ypa+2);
		outtextxy(r*15+xelem,ypa+5,"R");
		line((r/2)*15+xelem,ypa-2,(r/2)*15+xelem,ypa+2);
		outtextxy((r/2)*15+xelem,ypa+5,"F");
		ellipse(xelem+r*13/fabs(r),ypa,-87,87,13, 160);
	}
	
	void shof(bool ty){
                      if(ty) r++;
                      else r--;
                      }
	
	int retf(){return r;}
};

class lens : public elem{	
      int f;
public:
	lens(int foc){
		f = foc;
	}
	lens(){cout<<"in lens";}
	
	point form(point o){
		point i;
		i.x = (f*o.x) / (o.x + f);
		i.y = (o.y*i.x) / o.x;
		if(o.x<0 && i.x<0)xelem=1300;
		else xelem=680;
		return i;
	}
	void draw(){
		cout << "\nDrawing lens "<<f<<endl;
		line(f*15+xelem,ypa-2,f*15+xelem,ypa+2);
		outtextxy(xelem+f*15,ypa+5,"F");
		outtextxy(xelem-f*15,ypa+5,"F");
		line(2*f*15+xelem,ypa-2,2*f*15+xelem,ypa+2);
		outtextxy(xelem+2*f*15,ypa+5,"2F");
		outtextxy(xelem-2*f*15,ypa+5,"2F");
		if(f>0)ellipse(xelem, ypa, 0, 360, 8 - 0.2*f, 160);
		else{
			ellipse(xelem - 16, ypa, -87, 87, 13, 160);
			ellipse(xelem + 16, ypa, 87, -87, 13, 160);
			line(xelem - 16, ypa - 160, xelem + 16, ypa - 160);
			line(xelem - 16, ypa + 160, xelem + 16, ypa + 160);
		}
	}
	
		void shof(bool ty){
                      if(ty) f++;
                      else f--;
                      }
	
	int retf(){return f;}
};

class ray{
	point o, i;
public:
	void get(point ob, point im){
		o = ob;
		i = im;
		cout << "\ninit ray";
	}
	void draw(){
		cout << "\nDrawing ray";
		        setcolor(YELLOW);
                setlinestyle(DOTTED_LINE,0,1);  
		    	line(15*o.x+xelem,-15*o.y+ypa,xelem,ypa);//primary
		        line(15*i.x+xelem,-15*i.y+ypa,xelem,ypa);//primary
		        line(15*o.x+xelem,-15*o.y+ypa,xelem-2,-15*o.y+ypa);//secondary
		        line(15*i.x+xelem,-15*i.y+ypa,xelem-2,-15*o.y+ypa);//secondary
		        setcolor(WHITE);
		        setlinestyle(SOLID_LINE,0,1);
	}
};

class base{
	int ch;//for lens/mir;
	elem *e;
	point ob, im;
	ray r1, r2;
public:
      	bool save;
      	
      	base (int c, int k, float x, float y){
             ch=c;
             if(c)e=new mirr(k);
             else e=new lens(k);
             ob.x=x;
             ob.y=y;
             save = TRUE;
             cout<<"\nInitializing from saved data..."<<c<<" "<<k<<" "<<x<<" "<<y<<endl;
       }
       
	base(int c){
                save = FALSE;
		if (!c){
			int f;
			cout << "Enter focal length:";
			cin >> f;
			e = new lens(f);
			ch=0;                //FOR LENS 0
		}
		else{
			int r;
			cout << "Enter radius:";
			cin >> r;
			e = new mirr(r);
			ch=1;                //FOR MIRROR 1
		}

		cout << "Enter object dimensions:";
		cin >> ob.x >> ob.y;
	}

	void close(){//place destructor to remove whole setup; delete elem, img, obj
		cout << "\nDeleting element";
		delete e;
		cout << "\nClosing window";
	}
	
	~base(){close();}
	
	void draw(){
		im = e->form(ob);
                 {
                  char *di=conv(e->retf());
//                  outtextxy(1300, 350, di);
                    cout<<di<<endl;
                  di=conv(ob.x);
//                  outtextxy(95, 612, di);
                    cout<<di<<endl;
                  di=conv(ob.y);
//                  outtextxy(1300, 450, di);
                    cout<<di<<endl;
        } 
		r1.get(ob, im);
		cout << "\nLine";
		line(0,325,1360,325);
		e->draw();
		cout << "Drawing object" << ob.x << " " << ob.y;
		setcolor(GREEN);
		setlinestyle(SOLID_LINE,0,2);
		circle(15 * ob.x + xelem, -15 * ob.y + ypa,3);
		line(15 * ob.x + xelem, -15 * ob.y + ypa, 15 * ob.x + xelem, ypa);
		cout << "Drawing image" << im.x << " " << im.y;
		setcolor(RED);
		circle(15 * im.x + xelem, -15 * im.y + ypa,3);
		line(15 * im.x + xelem, -15 * im.y + ypa, 15 * im.x + xelem, ypa);
		setlinestyle(SOLID_LINE,0,1);

		r1.draw();
   	}

	void shob(bool ty){
		if(ty)ob.x += 0.5;
		else ob.x -= 0.5;
		cleardevice();
		draw();
		save=FALSE;
	}
	
	void inob(bool ty){
		if(ty){
               if(ob.y<9.5)ob.y += 0.25;
               else { outtextxy(359, 570, "MAX HEIGHT!"); return;}
               }
		else ob.y -= 0.25;
		cleardevice();
		draw();
		save=FALSE;
	}
	
	void shof(bool ty){
                      e->shof(ty);
                      cleardevice();
                      draw();
                      save=FALSE;
 }
  void saveb(){savebase(ch, e->retf(), ob.x, ob.y); save=TRUE; draw();}
};

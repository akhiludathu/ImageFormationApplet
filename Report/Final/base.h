using namespace std;
#include<iostream>
#include<math.h>
#include "graphics.h"

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
	mirr(){}
	
	point form(point o){
		point i;
		if(o.x==r/2){i.x=i.y=0; return i;}
		i.x = (r*o.x) / ((2 * o.x) - r);
		i.y = -1.0*(o.y*i.x) / o.x;
		return i;
	}
	void draw(){
		line(r*15+xelem,ypa-2,r*15+xelem,ypa+2);
		outtextxy(r*15+xelem,ypa+5,"R");
		line((r/2)*15+xelem,ypa-2,(r/2)*15+xelem,ypa+2);
		outtextxy((r/2)*15+xelem,ypa+5,"F");
		if(r<0)
		ellipse(xelem+r*13/fabs(r),ypa,-87,87,13, 160);
		else
		ellipse(xelem+r*13/fabs(r),ypa,87,-87,13, 160);
	}
	
	void shof(bool ty){
                      if(ty) r++;
                      else r--;
                      if(!r)if(ty) r++;
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
	lens(){}
	
	point form(point o){
		point i;
		if(o.x==f){i.x=i.y=0; return i;}
		i.x = (f*o.x) / (o.x + f);
		i.y = (o.y*i.x) / o.x;
		return i;
	}
	void draw(){
		line(f*15+xelem,ypa-2,f*15+xelem,ypa+2);
		line(-1*f*15+xelem,ypa-2,-1*f*15+xelem,ypa+2);
		outtextxy(xelem+f*15,ypa+5,"F");
		outtextxy(xelem-f*15,ypa+5,"F");
		line(2*f*15+xelem,ypa-2,2*f*15+xelem,ypa+2);
		line(-2*f*15+xelem,ypa-2,-2*f*15+xelem,ypa+2);
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
                      if(!f)if(ty) f++;
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
	}
	void draw(){
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
			cout << "Enter radius(less than 25):";
			cin >> r;
			e = new mirr(r);
			ch=1;                //FOR MIRROR 1
		}

		cout << "Enter object distance(preferably negative value; less than 25):";
		cin >> ob.x;
		cout << "Enter object height(less than 9):";
        cin >> ob.y;
	}

	void close(){
		delete e;
	}
	
	~base(){close();}
	
	void draw(){
		im = e->form(ob); 
		r1.get(ob, im);
		line(0,325,1360,325);
		e->draw();
		setcolor(GREEN);
		setlinestyle(SOLID_LINE,0,2);
		circle(15 * ob.x + xelem, -15 * ob.y + ypa,3);
		line(15 * ob.x + xelem, -15 * ob.y + ypa, 15 * ob.x + xelem, ypa);
		setcolor(RED);
		circle(15 * im.x + xelem, -15 * im.y + ypa,3);
		line(15 * im.x + xelem, -15 * im.y + ypa, 15 * im.x + xelem, ypa);
		setlinestyle(SOLID_LINE,0,1);

		r1.draw();
   	}

	void shob(bool ty){
        if(ty)ob.x += 0.5;
		else ob.x -= 0.5;
		if(!ob.x)if(ty)ob.x += 0.5;
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
  void saveb(){if(savebase(ch, e->retf(), ob.x, ob.y)) save=TRUE; draw();}
};

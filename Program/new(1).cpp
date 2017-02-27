#include<iostream>
using namespace std;
//1245
char ch(int a){ switch (a){ case 1:return '1'; case 2:return '2'; case 3:return '3'; case 4:return '4'; case 5:return '5'; case 6:return '6'; case 7:return '7'; case 8:return '8'; case 9:return '9'; case 0:return '0'; } }

char* conv(float b){
	char st[6];
	int a=b*100;
	st[0]=ch(a/1000); a=a%1000;
	st[1]=ch(a/100); a=a%100;
	st[2]='.';
	st[3]=ch(a/10); a=a%10;
	st[4]=ch(a);
	st[5]='\0';
	return st;
}

int main(){
	cout<<conv(67.54);
}

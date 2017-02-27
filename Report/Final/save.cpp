#include<iostream>
#include<fstream>
using namespace std;

struct saveb{
       int k;
       float x, y;
       bool operator==(saveb &t){if(k==t.k && x==t.x && y==t.y) return 1; else return 0;}
};

int savebase(int ch, int k, float x, float y){
    fstream fkey;
    int num[2];
    saveb b = {k, x, y};    
    
	fkey.open("key.dat", ios::in|ios::binary);
    fkey.read((char*)num, sizeof(num));
    fkey.close();
    cout<<num[0]<<" "<<num[1]<<endl;
    
    ofstream f;
    if(ch)f.open("mirr.dat", ios::binary|ios::app);
    else  f.open("lens.dat", ios::app|ios::binary);
	
	if(f)cout<<"YA!\n";
		
	f.write((char*)&b, sizeof(b));
	if(f.good())num[ch]++;
	cout<<f.fail();
	f.close();
	
    cout<<endl<<num[0]<<" "<<num[1]<<endl;
	fkey.open("key.dat", ios::binary|ios::out);
    fkey.write((char*)num, sizeof(num));
    fkey.close();
}

void reset(){
	int num[2];
	fstream fkey;
    fstream f;
    
	f.open("mirr.dat", ios::binary|ios::out);
    f.close();
    f.open("lens.dat", ios::binary|ios::out);	
    f.close();

    num[0]=num[1]=0;
	fkey.open("key.dat", ios::binary|ios::out);
    fkey.write((char*)num, sizeof(num));
    fkey.close();
    cout<<"\nReset successfully!\n";
    system("pause");
}


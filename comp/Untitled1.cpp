#include<iostream>
#include<fstream>
using namespace std;

int main(){
    fstream f;
    f.open("mirr.dat", ios::out | ios::binary);
    f.close();
    f.open("lens.dat", ios::out | ios::binary);
    f.close();
}

#include<iostream>
#include<fstream>
using namespace std;

struct saveb{
       int k;
       float x, y;
       bool operator==(saveb &t){if(k==t.k && x==t.x && y==t.y) return 1; else return 0;}
};

int savebase(int ch, int k, float x, float y){
    fstream f;
    saveb s={k, x, y}, t;
    if(ch)f.open("mirr.dat", ios::in | ios::binary);
    else  f.open("lens.dat", ios::in | ios::binary);
    if(f.good()) cout<<"\nopened";
    for (int i=0; i<4; i++){
        f.read((char*)&t, sizeof(t));
           if(s==t){f.close(); cout<<"\nNOT SAVed";return 0;}
   }
  // f.seekg(0);
    
   if(f.bad()) cout<<"\nBAD\n";
    else if(f.fail())cout<<"\nFAIL\n";
    
  //  f.seekg(0, ios::end);  
//    f.seekp(0, ios::end);
  //  cout<<endl<<f.tellp()<<" "<<sizeof(s)<<endl;
  f.clear();
  f.close();
  cout<<ch;
  ofstream f1;
  //if(ch)f.open("mirr.dat",  ios::binary|ios::ate);
 //   else  f.open("lens.dat",  ios::app );
  //  if(!f)cout<<"not opening";
  //    if(f.bad()) cout<<"\nBAD here\n";
   // else if(f.fail())cout<<"\nFAIL here\n";
   f1.open("mirr.dat",  ios::binary|ios::app);
   if(f1) cout<<"opened again";
    f1.write((char*)&s, sizeof(s));
    if(f1.good()) cout<<"\nSAVING...";
    else if(f1.bad()) cout<<"\nBAD\n";
    else if(f1.fail())cout<<"\nFAIL\n";
    f1.close();
    return 1;
}

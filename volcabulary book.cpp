#include <cstdlib>
#include <iostream>
#include <fstream> 
using namespace std;


int main(int argc, char *argv[])
{
    ofstream cout("out.txt");
    char b,a[100];
    int m=0,n[100];
    while(cin>>b&&b!='p')
    {
       cin>>b;
       a[m]=b;
       m++;
    }
    for(int i=m;i>=0;i=i-1)
    {
       cout<<a[i];
    }
    system("PAUSE");
    return EXIT_SUCCESS;
}

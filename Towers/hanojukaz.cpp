//---------------------------------------------------------------------------
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Disk.cpp"
//---------------------------------------------------------------------------
using namespace std;
MyClsDisk *a[3][count];
int main(int argc, char* argv[])
{
MyClsDisk *p; 
MyClsDisk Disk[count];

for (int i=0; i<count; i++)
        {
			{
			p=&Disk[i];
			}
        (*p).Weight=i;
        (*p).purposeX =0;
        (*p).purposeY = i;
        (*p).currentX = 0;
        (*p).currentY = i;
        }

for(int iy =0; iy<count; iy++)
        {
        a[0][iy]=&Disk[iy];
		a[1][iy]=NULL;
		a[2][iy]=NULL;
		}

a[0][0]=NULL;
for (int i=0;i<3;i++)
	{ cout<< endl;
	for(int j=0; j<count; j++) 
		{ 
		if (a[i][j] == NULL) cout<<0<<" ";
		else { cout<<(*a[i][j]).Weight<<" ";}
		} 
	}
for(int ix=count-1;ix>0;ix--)
        {
			{
			p=&Disk[ix];
			}
		(*p).ShowPins(a);
		(*p).FindPlace(2,Disk[ix].Weight);
        (*p).SetDiskOnPurpose(a,3,count);

_getch();
}

cout<<endl<<CountWays;
return 0;


}


//--------------------------------------------------------------------------
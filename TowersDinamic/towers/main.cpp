//---------------------------------------------------------------------------
#include "Untitled1.cpp"
//---------------------------------------------------------------------------
using namespace std;

int main(int argc, char* argv[])
{
int count=0;
cout<<"Enter count of disk>";
cin>>count;
cout<<endl<<"for step, PRESS ENTER";
count+=1;
int m=3;
MyClsDisk ***a = new MyClsDisk**[m];
for (int i=0; i<m; i++) a[i]= new MyClsDisk*[count];
MyClsDisk *p;

MyClsDisk *Disk= new MyClsDisk[count];
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
for(int ix=count-1;ix>0;ix--)
        {
            {
			p=&Disk[ix];
			}
		(*p).ShowPins(a, count);
		(*p).FindPlace(2,Disk[ix].Weight);
        (*p).SetDiskOnPurpose(a,3,count);
        }
getch();
return 0;
}
}


//--------------------------------------------------------------------------

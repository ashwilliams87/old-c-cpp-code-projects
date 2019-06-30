#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;
class MyClsDisk {
public:
void SetDiskOnPurpose(MyClsDisk ***AA,int x, int y)
{
int FlagEmpty=3;
while (FlagEmpty != 0)
	{
		FlagEmpty=(*this).CheckStatus(AA);
		if (FlagEmpty==1)
			{
			(*AA[(*this).currentX][(*this).currentY-1]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);
			(*AA[(*this).currentX][(*this).currentY-1]).SetDiskOnPurpose(AA, x, y);
			}

		if (FlagEmpty==2)
			{
			(*AA[(*this).purposeX][(*this).purposeY]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);
			(*AA[(*this).purposeX][(*this).purposeY]).SetDiskOnPurpose(AA, x, y);
			}
	}
AA[(*this).purposeX][(*this).purposeY]=AA[(*this).currentX][(*this).currentY];
AA[(*this).currentX][(*this).currentY]=NULL;
(*this).currentX=(*this).purposeX;
(*this).currentY=(*this).purposeY;
(*this).ShowPins(AA, y);
}

void FindPlace(int TpurposeX, int TpurposeY)
	{
	(*this).purposeX=TpurposeX;
	(*this).purposeY=TpurposeY;
	}

void FindPlace(MyClsDisk ***AA, int x, int y,int TCurrentX, int TPurposeX)
{
	for (int i=0; i<x;i++)
	{
		if ((TCurrentX!=i)&&(TPurposeX!=i)) (*this).purposeX=i;

	}
		for (int j=y-1;j>0;j--)
		{
			if ((AA[(*this).purposeX][j]) == NULL)
			{
				(*this).purposeY=j;
				break;
			}
		}
}
int CheckStatus(MyClsDisk ***AA)
	{
		if (AA[(*this).currentX][(*this).currentY-1] != NULL) return 1;
		if (AA[(*this).purposeX][(*this).purposeY] != NULL) return 2;
		if ((AA[(*this).currentX][(*this).currentY-1] == NULL) && (AA[(*this).purposeX][(*this).purposeY] == NULL)) return 0;
	}


int Weight;
int purposeX,purposeY;
int currentX,currentY;


void ShowPins(MyClsDisk ***AA, int count)const
{
system("cls");
for(int j=0; j<count; j++)
	{
    cout<< endl;
    for (int i=0;i<3;i++)
		{
		if (AA[i][j] == NULL) cout<<0<<" ";
		else { cout<<(*AA[i][j]).Weight<<" ";}
		}
	}
getch();
}


};



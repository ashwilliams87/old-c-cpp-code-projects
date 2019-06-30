using namespace std;

class MyClsDisk {
public:
	//функци€ постановки диска на целевую позицию PurposeX, PurposeY
void SetDiskOnPurpose(MyClsDisk ***AA,int x, int y, int ***GlobalTower)
{
int FlagEmpty=3;
while (FlagEmpty != 0)
	{	//функци€ CheckStatus возвращает состо€ние текущего диска 1-на диске стоит меньший диск 2-целева€ позици€ зан€та
		FlagEmpty=(*this).CheckStatus(AA);
		if (FlagEmpty==1) 
			{
			(*AA[(*this).currentY-1][(*this).currentX]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);// ищет новую позицию дл€ младшего диска
			(*AA[(*this).currentY-1][(*this).currentX]).SetDiskOnPurpose(AA, x, y,GlobalTower);
			}
		
		if (FlagEmpty==2) 
			{
			(*AA[(*this).purposeY][(*this).purposeX]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);//ищет новую свободную позицию дл€ диска занимающего целевую позицию текущего
			(*AA[(*this).purposeY][(*this).purposeX]).SetDiskOnPurpose(AA, x, y,GlobalTower);
			}
	}
AA[(*this).purposeY][(*this).purposeX]=AA[(*this).currentY][(*this).currentX];
AA[(*this).currentY][(*this).currentX]=NULL;
(*this).currentX=(*this).purposeX;
(*this).currentY=(*this).purposeY;
(*this).Step(AA, y, GlobalTower);
CountWays+=1;
}

void FindPlace(int TpurposeX, int TpurposeY)
	{
	(*this).purposeX=TpurposeX;
	(*this).purposeY=TpurposeY;
	}
//функци€ ищет дл€ диска свободный пин - Ќ≈текущий и Ќ≈целевой
void FindPlace(MyClsDisk ***AA, int x, int y,int TCurrentX, int TPurposeX)
{
	for (int i=0; i<=x;i++)
	{
		if ((TCurrentX!=i)&&(TPurposeX!=i)) (*this).purposeX=i;

	}
		for (int j=y-1;j>0;j--) 
		{
			if ((AA[j][(*this).purposeX]) == NULL) 
			{
				(*this).purposeY=j;
				break;
			}
		}
}

//статус 0 означает, что этот диск может двигатьс€, т.е его не перекрывает сверху диск, и целева€ позици€ не зан€та
int CheckStatus(MyClsDisk ***AA)
	{
		if (AA[(*this).currentY-1][(*this).currentX] != NULL) return 1;
		if (AA[(*this).purposeY][(*this).purposeX] != NULL) return 2;
		if ((AA[(*this).currentY-1][(*this).currentX] == NULL) && (AA[(*this).purposeY][(*this).purposeX] == NULL)) return 0;
	}


int Weight;
int purposeX,purposeY;
int currentX,currentY;

//запись хода в 3хмерный массив[шаг][позици€Y][позици€X]

void Step(MyClsDisk ***AA, int count,int ***GlobalTower)const {
system("cls");
for (int i=0; i<count; i++)
	{
	for (int j=0;j<3;j++)	 
		{ 
		if (AA[i][j] == NULL) { GlobalTower[CountWays][i][j] = 0;}
		else {GlobalTower[CountWays][i][j] = (*AA[i][j]).Weight; }
		} 
	}
}


};



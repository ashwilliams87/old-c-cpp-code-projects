using namespace std;

class MyClsDisk {
public:
	//������� ���������� ����� �� ������� ������� PurposeX, PurposeY
void SetDiskOnPurpose(MyClsDisk ***AA,int x, int y, int ***GlobalTower)
{
int FlagEmpty=3;
while (FlagEmpty != 0)
	{	//������� CheckStatus ���������� ��������� �������� ����� 1-�� ����� ����� ������� ���� 2-������� ������� ������
		FlagEmpty=(*this).CheckStatus(AA);
		if (FlagEmpty==1) 
			{
			(*AA[(*this).currentY-1][(*this).currentX]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);// ���� ����� ������� ��� �������� �����
			(*AA[(*this).currentY-1][(*this).currentX]).SetDiskOnPurpose(AA, x, y,GlobalTower);
			}
		
		if (FlagEmpty==2) 
			{
			(*AA[(*this).purposeY][(*this).purposeX]).FindPlace(AA,x,y,(*this).currentX,(*this).purposeX);//���� ����� ��������� ������� ��� ����� ����������� ������� ������� ��������
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
//������� ���� ��� ����� ��������� ��� - ��������� � ���������
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

//������ 0 ��������, ��� ���� ���� ����� ���������, �.� ��� �� ����������� ������ ����, � ������� ������� �� ������
int CheckStatus(MyClsDisk ***AA)
	{
		if (AA[(*this).currentY-1][(*this).currentX] != NULL) return 1;
		if (AA[(*this).purposeY][(*this).purposeX] != NULL) return 2;
		if ((AA[(*this).currentY-1][(*this).currentX] == NULL) && (AA[(*this).purposeY][(*this).purposeX] == NULL)) return 0;
	}


int Weight;
int purposeX,purposeY;
int currentX,currentY;

//������ ���� � 3������� ������[���][�������Y][�������X]

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



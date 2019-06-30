const int count = 3;
class MyClsDisk
        {
         public:
         void SetDiskOnPurpose(MyClsDisk *AA[][count],int x, int y);
         void FindPlace(int, int);
		 void FindPlace(MyClsDisk *AA[][count]);
		 int CheckStatus(MyClsDisk *AA[][count], int , int,int,int);
         int Weight;
         int purposeX,purposeY;
         int currentX,currentY;
        };

void ShowPins(MyClsDisk *AA[][count]);
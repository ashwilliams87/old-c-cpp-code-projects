//---------------------------------------------------------------------------
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "Disk.h"
#include "Disk.cpp"
#include <GL/glut.h>
//---------------------------------------------------------------------------
using namespace std;

int ***pGlobalTower;
int *pCount;
int *pSteps;
int *pM;
int *pStep;
int Step=0;

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
int x1,x2,y1,y2, Size, baseSize= 15;
int PinX[3]={175,375,575};
glBegin(GL_QUADS);
{
	for (int i=0; i<(*pCount); i++ )
		for(int j=0; j<3; j++)
		{
		if ((*pStep)<((*pSteps)-1))
		if (pGlobalTower[(*pStep)][i][j]!=0) 
			{
			x1=PinX[j]-baseSize*pGlobalTower[(*pStep)][i][j];
			x2=PinX[j]+baseSize*pGlobalTower[(*pStep)][i][j];
			y1=300 + (baseSize*i-5);
			y2=300 + (baseSize*i+5) ;
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(x1,y1); // 1 
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(x1, y2); //2
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(x2, y2); //3
			glColor3f(1.0, 1.0, 1.0);
			glVertex2i(x2, y1); //4
			}
		}
}
glEnd();
glutSwapBuffers();
(*pStep)++;
}

void reshape(int w, int h)
{
        glViewport(0, 0, w, h);
       
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, 0, h);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}


void timer(int = 0)
{
glutPostRedisplay();
glutTimerFunc(600, timer, 0);
}

int main(int argc, char* argv[])
{
int count=0;
cout<<"Enter count of disk>";
cin>>count;
cout<<endl<<"for step, PRESS ENTER";
Steps=pow(2.0,(count))-1;
count+=1;
int m=3; 
MyClsDisk ***a = new MyClsDisk**[count];
for (int i=0; i<count; i++) a[i]= new MyClsDisk*[m];
MyClsDisk *p; 
MyClsDisk *Disk= new MyClsDisk[count];

//Заполняем объекты-диски значениями
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

//заполянем массив-пины объектами или пустыми значениями
for(int iy =0; iy<count; iy++)
        {
        a[iy][0]=&Disk[iy];
		a[iy][1]=NULL;
		a[iy][2]=NULL;
		}

a[0][0]=NULL;

//определяем массив для хранения шагов, с него будет осуществляться визуализация

static int ***GlobalTower=new int **[Steps];
    for (int i=0;i<Steps;i++)
    {
        GlobalTower[i]=new int *[count];
        for (int j=0;j<count;j++)
            GlobalTower[i][j]=new int [m];
    }
//вывод на экран
for (int ii=0; ii<1; ii++)
for (int i=0;i<count;i++)
	{
	for(int j=0; j<m; j++) 
		{ 
		if (a[i][j] == NULL) 
			{
			GlobalTower[ii][i][j]=0;;
			}
		else 
			{ 
			GlobalTower[ii][i][j]=(*a[i][j]).Weight;}
			} 
	}   

//запуск алгоритма перестановок дисков
for(int ix=count-1;ix>0;ix--)
    {

			{
			p=&Disk[ix];
			}
	   (*p).FindPlace(2,Disk[ix].Weight);
       (*p).SetDiskOnPurpose(a,2,count,GlobalTower);
	}

//передаем по указателю массив с ходами башен
pGlobalTower = GlobalTower;
pM=&m;
pCount=&count;
pSteps=&Steps;
pStep = &Step;
//визуализация
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(800, 600);
glutInitWindowPosition(0, 86);
glutCreateWindow("Tower");
glClearColor(0, 0, 0, 1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, 800, 600, 0, -1, 1);
glutDisplayFunc(display);
timer();
glutMainLoop();
 
return 0;
}

//--------------------------------------------------------------------------
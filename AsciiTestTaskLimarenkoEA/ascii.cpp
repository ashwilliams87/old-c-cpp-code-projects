#include "asciiStringClass.h"
#include <stdlib.h>
using namespace Navmii::ProgrammingTest;
//--------------------------------------------------------------
int my_Cstrlen(const char *s) 
	{
    const char* cur = s;
	int i=0;
    while (*(cur++)) i++;
    return i+1;
	}//функция аналог strlen
//----------------------------------------------------------------------------  
AsciiString::AsciiString()
	{ 
	count=1;
	AsciiChar *newlink = new AsciiChar;
	newlink->character = '\0';
	newlink->next=NULL;
	newlink->prev=NULL;
	head=newlink;
	tail=newlink;
	}// Объект содержит в себе указатели на динамический 
//двухсвязный список head-голова списка, tail- хвост, next и prev указатели на следующую и предыдущую структуру, count- количество узлов в списке
//----------------------------------------------------------------------------  
AsciiString::AsciiString(int Tcount, AsciiChar *Thead, AsciiChar *Ttail):count(Tcount), head(Thead), tail(Ttail)
{}
//---------------------------------------------------------------------------- 
int AsciiString::GetLength() const
	{
	return (*this).count;
	}
//----------------------------------------------------------------------------  
void AsciiString::SetChar(int index, char character)
	{
	AsciiChar *temp;
	temp=(*this).head;
	for(int i=0; !(i==index); i++) 
		{
		temp=(*temp).next; 
		}
	(*temp).character=character;
	}
//----------------------------------------------------------------------------  
char AsciiString::GetChar(int index) const
	{
	AsciiChar *temp;
	temp=(*this).head;
	for(int i=0; i!=index; i++)
		{
		if ((*temp).next!=NULL) temp=(*temp).next;
		}
	return (*temp).character;
	}
//----------------------------------------------------------------------------  
char AsciiString::operator [] (int index) const
	{
	AsciiChar *temp;
	temp=(*this).head;
	for(int i=0; i!=index; i++)
		{
		if ((*temp).next!=NULL) temp=(*temp).next;
		}
	return (*temp).character;
	}
//----------------------------------------------------------------------------  
void AsciiString::Append(char character)
	{
	AsciiChar *newlink = new AsciiChar;
	(*newlink).character = character;
	if (count==1)
		{
		head=newlink;
		(*newlink).prev=NULL;
		(*newlink).next=tail;
		tail->prev=newlink;
		}
	else
		{
		tail->prev->next=newlink;
		(*newlink).next=tail;
		(*newlink).prev=(*tail).prev;	
		tail->prev=newlink;	
		}
	count+=1;
	}
//----------------------------------------------------------------------------      
void AsciiString::Append(const AsciiString &other)
	{
	AsciiChar *temp=other.head;
	for (int i=0;i<(other.GetLength()-1);i++) //may while(temp!=other.tail)
		{
		AsciiChar *newlink = new AsciiChar;
		(*newlink).character = temp->character;
		tail->prev->next=newlink;
		(*newlink).next=tail;
		(*newlink).prev=(*tail).prev;	
		tail->prev=newlink;	
		temp=temp->next;
		(*this).count+=1;
		}
	}
//----------------------------------------------------------------------------  
AsciiString& AsciiString::operator += (const AsciiString& other)
	{//
	AsciiChar *temp=other.head;
	for (int i=0;i<(other.GetLength()-1);i++) 
		{
		AsciiChar *newlink = new AsciiChar;
		(*newlink).character = temp->character;
		if (count==1)
			{
			head=newlink;
			(*newlink).prev=NULL;
			(*newlink).next=tail;
			tail->prev=newlink;
			}
		else
			{
			tail->prev->next=newlink;
			(*newlink).next=tail;
			(*newlink).prev=(*tail).prev;	
			tail->prev=newlink;	
			}
		temp=temp->next;
		(*this).count+=1;
		}
	return AsciiString(count, head, tail);
	}
//----------------------------------------------------------------------------  
AsciiString AsciiString::operator + (const AsciiString& other) const
	{
	AsciiString Temp;
	Temp+=(*this);
	Temp+=other;
	return Temp;
	}
//----------------------------------------------------------------------------  
void AsciiString::Insert(const AsciiString& other, int index)
	{	
	AsciiChar *rightLink=NULL;
	AsciiChar *leftLink=(*this).head;
	AsciiChar *temp=other.head;
	if (leftLink->character=='\0')// для случая с пустой строкой
		{
		AsciiChar *newlink = new AsciiChar;
		(*newlink).character=(*temp).character;temp=temp->next;
		(*newlink).next=(*this).head;
		(*this).head=newlink;
		newlink->next->prev=newlink;
		newlink->prev=NULL;
		leftLink=newlink;
		rightLink=newlink->next;
		count+=1;
		}
	else 
		{
		for (int i=0;i!=index; i++)
					{
					leftLink=leftLink->next;
					}
		if (leftLink->prev!=NULL) leftLink=leftLink->prev; //для случая со строкой с одним символом
		if (leftLink->next!=NULL) rightLink=leftLink->next;
		}
	while (temp->character!='\0')
		{
		AsciiChar *newlink = new AsciiChar;
		(*newlink).character=(*temp).character;
		(*newlink).prev=leftLink;
		leftLink->next=newlink;
		leftLink=newlink;
		temp=temp->next;
		count+=1;
		}
	leftLink->next=rightLink;
	rightLink->prev=leftLink;
	}
//----------------------------------------------------------------------------  
		//в примере приведен метод, которая принимает, как параметр символ, 
		//а в объявлении функция принимает ссылку на объект, соответственно, можно перегрузить этот метод, для вставки одного символа
void AsciiString::Remove(int startingIndex, int removedCharactersCount)
	{// ДОПИЛИТЬ деструктор объекта можно еще для стартингИндекс==0&&removedCharactersCount==this.count
	AsciiChar *marker=(*this).head;
	AsciiChar *temp=NULL;
	for (int i=0; i<startingIndex; i++)
		{
		marker=marker->next; //найти началальный узел
		}
	for (int i=0; i<removedCharactersCount; i++)
		{
		temp=marker->next;
		if (i<=removedCharactersCount)
			{
			if (marker->prev !=NULL)   //элемент не первый
				{
				marker->prev->next=marker->next;
				if (marker->next!=NULL) //элемент не послендний
					{
					marker->next->prev=marker->prev;
					}
				else 
					{
					tail=marker->prev;
					}
				}
		else 
			{
			if (marker->next!=NULL) 
				{
				marker->next->prev=NULL;
				head = marker->next;
				}
			else 
				{
				head=tail=NULL; //список пустой
				}
			}
		delete marker;
			count--;
			}
		marker=temp;
		}
	}
//----------------------------------------------------------------------------
bool AsciiString::Equals(const AsciiString& other) const
	{
	if ((*this).count!=other.count) return false;
	AsciiChar *temp1=(*this).head;
	AsciiChar *temp2=other.head;
	for (int i=0;i<(*this).count;i++)
		{
		if (temp1->character==temp2->character) 
			{
			temp1=temp1->next;
			temp2=temp2->next;
			}
		else return false;
		}
	return true;
	}
//----------------------------------------------------------------------------
bool AsciiString::operator == (const AsciiString& other) const
	{
	if ((*this).count!=other.count) return false;
	AsciiChar *temp1=(*this).head;
	AsciiChar *temp2=other.head;
	for (int i=0;i<(*this).count;i++)
		{
		if (temp1->character==temp2->character) 
			{
			temp1=temp1->next;
			temp2=temp2->next;
			}
		else return false;
		}
	return true;
	}
//----------------------------------------------------------------------------
bool AsciiString::operator != (const AsciiString& other) const
	{
	if ((*this).count!=other.count) return true;
	AsciiChar *temp1=(*this).head;
	AsciiChar *temp2=other.head;
	for (int i=0;i<(*this).count;i++)
		{
		if (temp1->character==temp2->character) 
			{
			temp1=temp1->next;
			temp2=temp2->next;
			}
			else return true;
		}
		return false;
	}
//----------------------------------------------------------------------------
bool AsciiString::Find(char character, /*out*/int& foundIndex) const
	{//прямой поиск
	AsciiChar *temp=(*this).head;
	for (int i=0; i<(*this).count;i++)
		{
		if ((temp->character)==character) 
			{
			foundIndex=i;
			return 1;
			}
		temp=temp->next;
		}
	return 0;
	} 
//----------------------------------------------------------------------------
bool AsciiString::Find(const AsciiString& substring, /*out*/int& foundIndex) const
	{//взял готовый алгоритм КМП
	int i, j, N, M; 
	N = (*this).count-1;
    M = substring.count-1;
	char *s=new char[N];
	char *p=new char[M];
	for (int i=0; i!=N;i++)
		{
		s[i]=(*this).GetChar(i);
		}
	for (int i=0; i!=M;i++)
		{
		p[i]=substring.GetChar(i);
		}
    int *d =new int[M]; /* динамический массив длины М*/ 
    /* Вычисление префикс-функции */ 
    d[0]=0;
    for(i=1,j=0;i<M;i++)
		{
		while(j>0 && p[j]!=p[i])  j = d[j-1];
        if(p[j]==p[i]) j++;
		d[i]=j;
		}
    /* поиск */
    for(i=0,j=0;i<N; i++)
		{
        while(j>0 && p[j]!=s[i]) j=d[j-1];
		if(p[j]==s[i]) j++;
        if (j==M)
			{
            delete []d;
			delete []s;
			delete []p;/* освобождение памяти массива d */ 
            foundIndex =i-j+1;
			return 1;
            }
        }
        delete []d;
		delete []s;
		delete []p; /* освобождение памяти массива d */ 
	return 0;
	}
//----------------------------------------------------------------------------
AsciiString::AsciiString(const char* source)
	{
	count=1;
	AsciiChar *newlink = new AsciiChar;
	newlink->character = '\0';
	newlink->next=NULL;
	newlink->prev=NULL;
	head=newlink;
	tail=newlink;
	int length=my_Cstrlen(source);
	 //предполагаем, что строка всегда содержит символ конца строки '0\'
	for (int i=0; i<(length-1);i++)
		{
		(*this).Append(source[i]); 
		}
	}
//----------------------------------------------------------------------------
void AsciiString::Assign(const char* source)
	{
	int length=my_Cstrlen(source);
	for (int i=0; i<(length-1);i++)
		{
		if ((*this).GetChar(i)=='\0') (*this).Append(source[i]); 
		else (*this).SetChar(i,source[i]);
		}
	if ((length-1) != ((this->count)-1)) 
		{
		int a=((*this).count-1)-(length-1); 
		this->Remove((length-1),a);
		}
	}
//----------------------------------------------------------------------------
AsciiString& AsciiString::operator = (const char* source)
	{
	int length=my_Cstrlen(source);
	for (int i=0; i<(length-1);i++)
		{
		if ((*this).GetChar(i)=='\0') (*this).Append(source[i]); 
		else (*this).SetChar(i,source[i]);
		}
	if ((length-1) != ((this->count)-1)) 
		{
		int a=((*this).count-1)-(length-1); 
		this->Remove((length-1),a);
		}
	return AsciiString(count, head, tail);
	}
//----------------------------------------------------------------------------
void AsciiString::ToPlainString(/*out*/char* outputBuffer, int maxOutputBufferSize) const
	{
	AsciiChar *temp=(*this).head;
	if (count==maxOutputBufferSize) 
		{
		for (int i=0; i<maxOutputBufferSize; i++)
			{
			outputBuffer[i]=temp->character;
			if ((temp->next)!=NULL) temp=temp->next;
			}
		}
	else 
		if (count>maxOutputBufferSize)
			{
			for (int i=0; i<maxOutputBufferSize; i++)
				{
				outputBuffer[i]=temp->character;
				if ((temp->next)!=NULL) temp=temp->next;
				}
			outputBuffer[maxOutputBufferSize-1]='\0';
			} 
		else 
			{
			for (int i=0; i<count; i++)
				{
				outputBuffer[i]=temp->character;
				if ((temp->next)!=NULL) temp=temp->next;
				}
			} 
		
	}
//----------------------------------------------------------------------------

    



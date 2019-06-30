//---------------------------------------------------------------------------
#include <stdlib.h>
#include "asciiStringClass.h"
#include "gtest/gtest.h"
using namespace Navmii::ProgrammingTest;
//---------------------------------------------------------------------------
int PullInMyLibrary() { return 0; }

class AsciiStringTest : public ::testing::Test {
};

TEST(AsciiStringTest, CheckLength) 
{

    AsciiString Strk; 
	ASSERT_EQ(1,Strk.GetLength());
}

TEST(AsciiStringTest, CheckAppendAndGetChar) 
{
	AsciiString Strk2;
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk2.Append('4');
	Strk2.Append('5');
	Strk2.Append('6');
	Strk2.Append('7');
	char s[8]={'1','2','3','4','5','6','7','\0'};
	ASSERT_EQ(8,Strk2.GetLength());
	for (int i=0; i<Strk2.GetLength(); i++) ASSERT_EQ(s[i],Strk2.GetChar(i));
}

TEST(AsciiStringTest, TestSetCharGetChar) 
{
	AsciiString Strk2;
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk2.SetChar(0,'s');
	ASSERT_EQ('s',Strk2.GetChar(0));
}

TEST(AsciiStringTest, TestOpetatorIndex) 
{
	AsciiString Strk2;
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	char s[8]={'1','2','3','4','5','6','7','\0'};
	ASSERT_EQ('1',Strk2[0]);
}

TEST(AsciiStringTest, TestAppendAsciiStringObject) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk.Append(Strk2);
	char s[7]={'a','b','c','1','2','3','\0'};
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestOperatorPlusEq) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk+=Strk2;
	char s[7]={'a','b','c','1','2','3','\0'};
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestOperatorPlus) 
{
	AsciiString Strk,Strk2,Strk3;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk3=Strk+Strk2;
	char s[7]={'a','b','c','1','2','3','\0'};
	for (int i=0; i<Strk3.GetLength(); i++) ASSERT_EQ(s[i],Strk3.GetChar(i));
}

TEST(AsciiStringTest, TestOperatorInsert) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('1');
	Strk2.Append('2');
	Strk2.Append('3');
	Strk.Insert(Strk2,1);
	char s[7]={'a','1','2','3','b','c','\0'};
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestRemove) 
{
	AsciiString Strk;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk.Remove(0,3);
	ASSERT_EQ('\0',Strk.GetChar(0));
}

TEST(AsciiStringTest, TestEquals) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('a');
	Strk2.Append('b');
	Strk2.Append('c');
	ASSERT_EQ(1,Strk.Equals(Strk2));
}

TEST(AsciiStringTest, TestOperatorEqual) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('a');
	Strk2.Append('b');
	Strk2.Append('c');
	ASSERT_TRUE(Strk==Strk2);
}

TEST(AsciiStringTest, TestOperatorNotEqual) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk2.Append('a');
	Strk2.Append('b');
	Strk2.Append('c');
	ASSERT_FALSE(Strk!=Strk2);
}

TEST(AsciiStringTest, TestFindChar) 
{
	AsciiString Strk;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	int i;
	Strk.Find('b',i);
	ASSERT_EQ(1,i);
}

TEST(AsciiStringTest, TestFindSubString) 
{
	AsciiString Strk,Strk2;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk.Append('d');
	Strk.Append('e');
	Strk.Append('f');
	Strk2.Append('c');
	Strk2.Append('d');
	Strk2.Append('e');
	int i;
	Strk.Find(Strk2,i);
	ASSERT_EQ(2,i);
}

TEST(AsciiStringTest, TestConstruction) 
{
	char s[7]={'a','b','c','d','e','f','\0'};
	AsciiString Strk(s);
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestAssign) 
{
	char s[4]={'d','e','f','\0'};
	AsciiString Strk;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk.Assign(s);
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestOperatorAssign) 
{
	char s[4]={'d','e','f','\0'};
	AsciiString Strk;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk=s;
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

TEST(AsciiStringTest, TestToPlainString) 
{
	char s[4];
	AsciiString Strk;
	Strk.Append('a');
	Strk.Append('b');
	Strk.Append('c');
	Strk.ToPlainString(s,4);
	for (int i=0; i<Strk.GetLength(); i++) ASSERT_EQ(s[i],Strk.GetChar(i));
}

int main(int argc, char* argv[])
{
int PullInMyLibrary();
static int dummy = PullInMyLibrary();

::testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
return 0;
}

//--------------------------------------------------------------------------
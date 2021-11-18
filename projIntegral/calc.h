//---------------------------------------------------------------------------

#ifndef calcH
#define calcH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
	long double argl[100];
	int f1;
	int i;
	int f1s;
	int f2s[100];
	long double SUMF;
	long double arg;
	float q;
	long double argls[100][100];
//---------------------------------------------------------------------------
	long double IntegDO(String formF1, long double x);
	long double formFu(String formF1, long double x);
	long double formCh(String formF1, long double n);
	long double formFs(String formF1, long double x, int f1s);
//---------------------------------------------------------------------------
	UnicodeString CalcStrSq(String str, long double up, long double down, long double delta);
	UnicodeString CalcStrTrap(String str, long double up, long double down, long double delta);
//---------------------------------------------------------------------------
#endif

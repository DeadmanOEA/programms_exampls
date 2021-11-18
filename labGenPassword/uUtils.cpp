//---------------------------------------------------------------------------

#pragma hdrstop

#include "uUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
UnicodeString RandomStr(int aLength, bool aLower, bool aUpper,
bool aNumbr, bool aSpecl, bool aEng, bool aRus) {
	const char *c1 = "abcdefghijklmnopqrstuvwxyz";
	const char *c2 = "0123456789";
	const char *c3 = "[]{}<>,.:;-+#";
	const char *c4 = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
	//
	UnicodeString x = "";
	UnicodeString xResult = "";

	if (aLower) {
		if (aEng) x += c1;
		if (aRus) x += c4;
	}
	if (aUpper) {
		if (aEng) x += UpperCase(c1);
		if (aRus) x += UpperCase(c4);
	}
	if (aNumbr) x += c2;
	if (aSpecl) x += c3;

	if (x.IsEmpty()) x = c1;

	while (xResult.Length() < aLength) {
		xResult += x.SubString(Random(x.Length() + 1), 1);
    }

	return xResult;

}
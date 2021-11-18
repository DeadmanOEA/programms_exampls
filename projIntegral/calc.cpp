//---------------------------------------------------------------------------

#pragma hdrstop

#include "calc.h"
#include "math.h"
#include "fmu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#define PI 3.14159265

UnicodeString CalcStrSq(String str, long double up, long double down, long double delta){
	long double sum;
	long double Sum = 0;
	UnicodeString xRes = "";
	for (long double start(down); start <= up; start += delta)
	{
		sum = 0;
		sum = delta*IntegDO(str, start);
		Sum += sum;
	}
	xRes += FloatToStr(Sum);

	return xRes;
}

UnicodeString CalcStrTrap(String str, long double up, long double down, long double delta){
	long double sum;
	long double Sum = 0;
	UnicodeString xRes = "";
	for (long double start(down); start < up; start += delta)
	{
		sum = 0;
		sum = delta*(IntegDO(str, start + delta) + IntegDO(str, start)) / 2;
		Sum += sum;
	}
	xRes += FloatToStr(Sum);

	return xRes;
}

long double IntegDO(String formF1, long double x){
	for (int j = 0; j < 100; j++)
		argl[j] = 0;
	for (int j = 0; j < 100; j++)
		for (int k = 0; k < 100; k++)
			argls[j][k] = 0;
	for (int j = 0; j < 100; j++)
		f2s[j] = 0;
	SUMF = 0;
	i = 1;
	f1 = 0;
	f1s = 0;
	while (i <= formF1.Length())
	{
		if (formF1[i] == '(')
		{
			i++;
			f1s++;
			argl[f1] = formFs(formF1, x, f1s);

		}
		else
			if (formF1[i] == '+')
			{
				i++;
				f1++;
				argl[f1] = formFu(formF1, x);
			}else
				if (formF1[i] == '-')
				{
					i++;
					f1++;
					argl[f1] = -formFu(formF1, x);

				}else
					if (formF1[i] == '*')
					{
						f1++;
						i++;
						argl[f1] = formFu(formF1, x);
						argl[f1 - 1] = argl[f1 - 1]*argl[f1];
						argl[f1] = 0;
						f1--;

					}else
						if (formF1[i] == '/')
						{
							f1++;
							i++;
							argl[f1] = formFu(formF1, x);
							argl[f1 - 1] = argl[f1 - 1]/argl[f1];
							argl[f1] = 0;
							f1--;

						}else
							if (formF1[i] == '^')
							{
								i++;
								argl[f1] = pow(argl[f1], formFu(formF1, x));
							}
							else
							{
							argl[f1]= formFu(formF1, x);

							}
	}
	for (int j = 0; j < 100; j++)
		SUMF += argl[j];
	return (SUMF);
}

long double formFs(String formF1, long double x, int f1s)
{
	while (formF1[i] != ')')
	{
		if (formF1[i] == '+') {
			i++;
			f2s[f1s]++;
			argls[f1s][f2s[f1s]] = formFu(formF1, x);
		} else {
			if (formF1[i] == '-') {
					i++;
					f2s[f1s]++;
					argls[f1s][f2s[f1s]] = -formFu(formF1, x);
			} else {
				if (formF1[i] == '*') {
					i++;
					f2s[f1s]++;
					argls[f1s][f2s[f1s]] = formFu(formF1, x);
					argls[f1s][f2s[f1s] - 1] = argls[f1s][f2s[f1s] - 1] * argls[f1s][f2s[f1s]];
					argls[f1s][f2s[f1s]] = 0;
					f2s[f1s]--;
				} else {
					if (formF1[i] == '/') {
						i++;
						f2s[f1s]++;
						argls[f1s][f2s[f1s]] = formFu(formF1, x);
						argls[f1s][f2s[f1s] - 1] = argls[f1s][f2s[f1s] - 1] / argls[f1s][f2s[f1s]];
						argls[f1s][f2s[f1s]] = 0;
						f2s[f1s]--;
					} else {
						if (formF1[i] == '^') {
							i++;
							argls[f1s][f2s[f1s]] = pow(argls[f1s][f2s[f1s]], formFu(formF1, x));
						} else {
							argls[f1s][f2s[f1s]] = formFu(formF1, x);

						}
					}
				}
			}
		}
	}
	i++;
	for (int j = 1; j < 100; j++)
	{
		argls[f1s][0] += argls[f1s][j];

	}
		return(argls[f1s][0]);

}

long double formFu(String formF1, long double x)
{
	arg = 0;
	while (i <= formF1.Length())
	{

		if (formF1[i] >= '0' && formF1[i] <= '9')
		{
			arg = formCh(formF1, 0);
			break;
		}
		else
			if (formF1[i] == 's')
			{
				i++;
				if (formF1[i] == 'q')
				{
					i += 4;
					f1s++;
					arg = sqrt(formFs(formF1, x, f1s));
					break;
				}
				else
				{
					i += 3;
					f1s++;
					arg = sin(formFs(formF1, x, f1s) * PI / 180);
					break;
				}

			}
			else
				if (formF1[i] == 'a')
				{
					i += 3;
					if (formF1[i] == 's')
					{
						i += 4;
						f1s++;
						arg = asin(formFs(formF1, x, f1s));
						break;

					}
					else
					{
						if (formF1[i] == 't')
						{
							i += 3;
							f1s++;
							arg = atan(formFs(formF1, x, f1s));
							break;

						}
						else
						{
							i++;
							if (formF1[i] == 't')
							{
								i += 3;
								f1s++;
								arg = PI / 2 - atan(formFs(formF1, x, f1s));
								break;

							}
							else
							{
								i += 3;
								f1s++;
								arg = acos(formFs(formF1, x, f1s));
								break;
							}


						}

					}
				}
				else
					if (formF1[i] == 't')
					{
						i += 3;
						f1s++;
						arg = tan(formFs(formF1, x, f1s) * PI / 180);
						break;

					}
					else
						if (formF1[i] == 'c')
						{
							i++;
							if (formF1[i] == 'o')
							{
								i += 3;
								f1s++;
								arg = cos(formFs(formF1, x, f1s)* PI / 180);
								break;
							}
							else {
								i += 3;
								f1s++;
								arg = 1 / tan(formFs(formF1, x, f1s) * PI / 180);
								break;
							}

						}
						else
							if (formF1[i] == 'l')
							{
								i += 3;
								f1s++;
								arg = log(formFs(formF1, x, f1s));
								break;
							}
							else
							{
								if (formF1[i] == 'x') {
									arg = x;
									i++;
									break;
								}
								else {
									if (formF1[i] == '(')
									{
										i++;
										f1s++;
										argl[f1] = formFs(formF1, x, f1s);
										break;

									}
								}
							}
	}
	return(arg);
}
long double formCh(String formF1, long double n)
{
	n = 0;
	int j = 0;
	q = 10;

		while (formF1[i] >= '0' && formF1[i] <= '9' || formF1[i] == '.')
		{
			if (formF1[i] == '0')
			{
				n = n*pow(q, j);
				j++;
				i++;
			}
			else
				if (formF1[i] == '1')
				{
					n = n*pow(q, j) + 1;
					j++;
					i++;
				}
				else
					if (formF1[i] == '2')
					{
						n = n*pow(q, j) + 2;
						j++;
						i++;
					}
					else
						if (formF1[i] == '3')
						{
							n = n*pow(q, j) + 3;
							j++;
							i++;
						}
						else
							if (formF1[i] == '4')
							{
								n = n*pow(q, j) + 4;
								j++;
								i++;
							}
							else
								if (formF1[i] == '5')
								{
									n = n*pow(q, j) + 5;
									j++;
									i++;
								}
								else
									if (formF1[i] == '6')
									{
										n = n*pow(q, j) + 6;
										j++;
										i++;
									}
									else
										if (formF1[i] == '7')
										{
											n = n*pow(q, j) + 7;
											j++;
											i++;
										}
										else
											if (formF1[i] == '8')
											{
												n = n*pow(q, j) + 8;
												j++;
												i++;
											}
											else
												if (formF1[i] == '9')
												{
													n = n*pow(q, j) + 9;
													j++;
													i++;
												}
												else
													if (formF1[i] == '.')
													{
														q = 0.1;
														j = 1;
														i++;
													}

	}
	return (n);
}

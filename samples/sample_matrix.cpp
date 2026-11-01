// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  TDynamicMatrix<int> a(5), b(5), c(5), d(5), e(3);
  int i, j;

  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
  d = b-a;
  cout << "Matrix d = b-a" << endl << d << endl;
  a[2][4] = 999;
  cout << "a[2][1] = 999" << endl <<"a: " <<endl << a << endl;

  e[0][0] = 1; e[0][1] = 3; e[0][2] = 4;
  e[1][0] = 0; e[1][1] = 4; e[1][2] = 2;
  e[2][0] = 0; e[2][1] = 0; e[2][2] = 5;

  cout << "Matrix e " << endl << e << endl;
  TDynamicMatrix<int> res = a * 2;
  //cout << res[1][4];
  //cout << "a*2" << endl << a * 2 << endl;
  TDynamicVector<int> vec(3);
  vec[0] = 2; vec[1] = 3; vec[2] = 0;
  cout << "vec " << vec << endl;
  cout << "e*vec" << endl << e * vec << endl;
  
}
//---------------------------------------------------------------------------

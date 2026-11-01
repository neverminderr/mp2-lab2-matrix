// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz,si;
  T* pMem;
  mutable T nothing{}; //для возврата 0 при чтении ниже диагонали
public:
  TDynamicVector(size_t size = 1, size_t _si = 0) : sz(size), si(_si)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE) throw sz;
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s, size_t _si=0) : sz(s), si(_si)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      si = v.si;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      si = v.si;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              T* tmp = new T[v.sz];
              delete []pMem;
              sz = v.sz;
              
              pMem = tmp;
          }
          si = v.si;
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          si = v.si;
          pMem = v.pMem;
          v.pMem = nullptr;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }
  size_t s_index() const noexcept { return si; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind < si) {
          nothing = T{};
          return nothing;
      }
      return pMem[ind-si];
  }
  const T& operator[](size_t ind) const
  {
      if (ind < si) {
          nothing = T{};
          return nothing;
      }
      return pMem[ind-si];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= si+sz) throw sz;
      if (ind < si) {
          nothing = T{};
          return nothing;
      }
      return pMem[ind-si];
  }
  const T& at(size_t ind) const
  {

      if (ind < 0 || ind >= si+sz) throw sz;
      if (ind < si) {
          nothing = T{};
          return nothing;
      }
      return pMem[ind-si];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz||si != v.si) {
          return false;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz || si != v.si) {
          return true;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) {
              return true;
          }
      }
      return false;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz,si);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz,si);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz, si);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz || si!=v.si) throw sz;
      TDynamicVector tmp(sz, si);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      }
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz || si != v.si) throw sz;
      TDynamicVector tmp(sz, si);
      for (int i = 0; i < sz; i++) {
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      }
      return tmp;
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz != v.sz || si != v.si) {
          throw sz;
      }
      T sum{};
      for (int i = 0; i < sz; i++) {
          sum = sum + pMem[i] * v.pMem[i];
      }
      return sum;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.si, rhs.si);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz+v.si; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
      for (int k = 0; k < v.si; k++) {
          ostr << T{} << ' ';
      }
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw s;
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz-i,i);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  //using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }


  TDynamicMatrix<T>& operator=(const TDynamicMatrix<T>& m) {
      if (this != &m) {
          if (sz != m.sz) {
              delete[] pMem; 
              sz = m.sz;
              pMem = new TDynamicVector<T>[sz];
          }
          for (int i = 0; i < sz; i++) {
              pMem[i] = m.pMem[i];
          }
      }
      return *this;
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции 
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) throw sz;
      
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          T sum{};
          for (int j = i; j < sz; j++) {
              sum = sum + pMem[i][j] * v[j];
          }
          res[i] = sum;
          //res.pMem[i] = pMem[i] * v;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz != sz) throw sz;
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz != sz) throw sz;
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw sz;
      TDynamicMatrix<T> res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  res.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz-i; j++) {
              istr >> v.pMem[i].pMem[j];
          }
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              if (j < i)
                  ostr << std::setw(4) <<T{} << " ";
              else {
                  ostr << std::setw(4) << v.pMem[i][j] << " ";
              }
          }
          ostr << std::endl;
      }
      return ostr;
  }
};

#endif

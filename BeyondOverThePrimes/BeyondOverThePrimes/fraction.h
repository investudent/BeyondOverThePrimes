#pragma once
#include<iostream>

/*
???????????N???X
???g??int,double???????Z?q?????`?????????
*/
class Fraction {
private:
	/*
	???q????{?l
	???q??????l????????`????\???????D
	*/
	static const signed int INITIAL_MOLECULE = 0;
	/*
	????????{?l
	????????l????????`????\???????D
	*/
	static const unsigned int INITIAL_DENOMINATER = 1;
private:
	signed int molecule_;//???q
	unsigned int denominator_;//????
public:
	Fraction();
	Fraction(int initializer);
	Fraction(double initializer);
	Fraction(int _molecule, int _denominator);
	Fraction(const Fraction& initializer);
	~Fraction() = default;

	void Subdivide();//????
	void ReduceWith(const Fraction& f);//????????????????????????
	friend void Reduce(Fraction& f1, Fraction& f2);//2???????????????

	Fraction& operator=(const Fraction& rhs);

	const Fraction operator-()const;

	Fraction& operator+=(const Fraction& rhs);
	Fraction& operator-=(const Fraction& rhs);
	Fraction& operator*=(const Fraction& rhs);
	Fraction& operator/=(const Fraction& rhs);

	Fraction& operator+=(int rhs);
	Fraction& operator-=(int rhs);
	Fraction& operator*=(int rhs);
	Fraction& operator/=(int rhs);

	Fraction& operator+=(double rhs);
	Fraction& operator-=(double rhs);
	Fraction& operator*=(double rhs);
	Fraction& operator/=(double rhs);

	bool operator==(const Fraction& rhs)const;
	bool operator!=(const Fraction& rhs)const;
	bool operator<(const Fraction& rhs)const;
	bool operator>(const Fraction& rhs)const;
	bool operator<=(const Fraction& rhs)const;
	bool operator>=(const Fraction& rhs)const;

	operator double()const;

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);//?W???o??????I?[?o?[???[?h
};

const Fraction operator+(const Fraction& lhs, const Fraction& rhs);
const Fraction operator-(const Fraction& lhs, const Fraction& rhs);
const Fraction operator*(const Fraction& lhs, const Fraction& rhs);
const Fraction operator/(const Fraction& lhs, const Fraction& rhs);

const Fraction operator+(const Fraction& lhs, int rhs);
const Fraction operator-(const Fraction& lhs, int rhs);
const Fraction operator*(const Fraction& lhs, int rhs);
const Fraction operator/(const Fraction& lhs, int rhs);
const Fraction operator+(int lhs, const Fraction& rhs);
const Fraction operator-(int lhs, const Fraction& rhs);
const Fraction operator*(int lhs, const Fraction& rhs);
const Fraction operator/(int lhs, const Fraction& rhs);

const Fraction operator+(const Fraction& lhs, double rhs);
const Fraction operator-(const Fraction& lhs, double rhs);
const Fraction operator*(const Fraction& lhs, double rhs);
const Fraction operator/(const Fraction& lhs, double rhs);
const Fraction operator+(double lhs, const Fraction& rhs);
const Fraction operator-(double lhs, const Fraction& rhs);
const Fraction operator*(double lhs, const Fraction& rhs);
const Fraction operator/(double lhs, const Fraction& rhs);

bool operator==(const Fraction& lhs, int rhs);
bool operator!=(const Fraction& lhs, int rhs);
bool operator<(const Fraction& lhs, int rhs);
bool operator>(const Fraction& lhs, int rhs);
bool operator<=(const Fraction& lhs, int rhs);
bool operator>=(const Fraction& lhs, int rhs);
bool operator==(int lhs, const Fraction& rhs);
bool operator!=(int lhs, const Fraction& rhs);
bool operator<(int lhs, const Fraction& rhs);
bool operator>(int lhs, const Fraction& rhs);
bool operator<=(int lhs, const Fraction& rhs);
bool operator>=(int lhs, const Fraction& rhs);

bool operator==(const Fraction& lhs, double rhs);
bool operator!=(const Fraction& lhs, double rhs);
bool operator<(const Fraction& lhs, double rhs);
bool operator>(const Fraction& lhs, double rhs);
bool operator<=(const Fraction& lhs, double rhs);
bool operator>=(const Fraction& lhs, double rhs);
bool operator==(double lhs, const Fraction& rhs);
bool operator!=(double lhs, const Fraction& rhs);
bool operator<(double lhs, const Fraction& rhs);
bool operator>(double lhs, const Fraction& rhs);
bool operator<=(double lhs, const Fraction& rhs);
bool operator>=(double lhs, const Fraction& rhs);

int Gcd(int first, int second);//??????????????

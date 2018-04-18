#include <stdio.h>
#include <math.h>
#include "fraction.h"

Fraction::Fraction() : molecule_(INITIAL_MOLECULE), denominator_(INITIAL_DENOMINATER) {
}
Fraction::Fraction(int initializer) : molecule_(initializer), denominator_(1) {
}
Fraction::Fraction(double initializer) {
	/*
	std::ostringstream sout;
	sout << initializer;
	size_t point = sout.str().find('.');
	if (point == std::string::npos) {
	denominator_ = INITIAL_DENOMINATER;
	molecule_ = stoi(sout.str());
	}
	else {
	unsigned int digit = sout.str().size() - point - 1;//�Y�����̒����łP����
	denominator_ = pow(10, digit);//���グ
	molecule_ = stoi(sout.str().erase(point, 1));//�����_�̂P������������������
	}
	*/
	char buf[256], sbuf[256];
	int i = 0, p_pos = 0, e_pos = 0;
	bool ebuf = true;
	sprintf_s(buf, 256, "%f", initializer);
	for (; buf[i] != '\0'; i++) {
		sbuf[i] = buf[i];
		e_pos = i;
		if (!ebuf) {
			sbuf[i - 1] = sbuf[i];
		}
		if (buf[i] == '.') {
			p_pos = i;
			ebuf = false;
		}
	}
	sbuf[i - 1] = '\0';
	if (ebuf) {
		denominator_ = INITIAL_DENOMINATER;
		sscanf_s(sbuf, "%d", &molecule_);
	}
	else {
		unsigned int digit = e_pos - p_pos;
		denominator_ = pow(10, digit);
		sscanf_s(sbuf, "%d", &molecule_);
	}
	Subdivide();
}
Fraction::Fraction(int _molecule, int _denominator) :molecule_(_molecule), denominator_(_denominator) {
}
Fraction::Fraction(const Fraction& initializer) {
	this->molecule_ = initializer.molecule_;
	this->denominator_ = initializer.denominator_;
}

void Fraction::Subdivide() {
	int gcd = Gcd(molecule_, denominator_);
	molecule_ /= gcd;
	denominator_ /= gcd;
}

void Fraction::ReduceWith(const Fraction& f) {
	int gcd = Gcd(this->denominator_, f.denominator_);
	int scale = f.denominator_ / gcd;
	this->molecule_ *= scale;
	this->denominator_ *= scale;
}

void Reduce(Fraction& f1, Fraction& f2) {
	f1.ReduceWith(f2);
	f2.ReduceWith(f1);
}

Fraction& Fraction::operator=(const Fraction& rhs) {
	if (*this != rhs) {
		this->molecule_ = rhs.molecule_;
		this->denominator_ = rhs.denominator_;
	}
	return *this;
}

const Fraction Fraction::operator-()const {
	Fraction tmp(*this);
	tmp.molecule_ = -this->molecule_;
	return tmp;
}

Fraction& Fraction::operator+=(const Fraction& rhs) {
	Fraction tmp(rhs);
	Reduce(*this, tmp);
	this->molecule_ += tmp.molecule_;
	Subdivide();
	return *this;
}
Fraction& Fraction::operator-=(const Fraction& rhs) {
	return *this += -rhs;
}
Fraction& Fraction::operator*=(const Fraction& rhs) {
	this->molecule_ *= rhs.molecule_;
	this->denominator_ *= rhs.denominator_;
	Subdivide();
	return *this;
}
Fraction& Fraction::operator/=(const Fraction& rhs) {
	int sign = rhs.molecule_ / abs(rhs.molecule_);
	this->molecule_ *= sign*rhs.denominator_;
	this->denominator_ *= abs(rhs.molecule_);
	Subdivide();
	return *this;
}

Fraction& Fraction::operator+=(int rhs) {
	return *this += Fraction(rhs);
}
Fraction& Fraction::operator-=(int rhs) {
	return *this -= Fraction(rhs);
}
Fraction& Fraction::operator*=(int rhs) {
	return *this *= Fraction(rhs);
}
Fraction& Fraction::operator/=(int rhs) {
	return *this /= Fraction(rhs);
}

Fraction& Fraction::operator+=(double rhs) {
	return *this += Fraction(rhs);
}
Fraction& Fraction::operator-=(double rhs) {
	return *this -= Fraction(rhs);
}
Fraction& Fraction::operator*=(double rhs) {
	return *this *= Fraction(rhs);
}
Fraction& Fraction::operator/=(double rhs) {
	return *this /= Fraction(rhs);
}

bool Fraction::operator==(const Fraction& rhs)const {
	return (*this <= rhs) && (*this >= rhs);
}
bool Fraction::operator!=(const Fraction& rhs)const {
	return !(*this == rhs);
}
bool Fraction::operator<(const Fraction& rhs)const {
	Fraction tmp1(*this), tmp2(rhs);
	Reduce(tmp1, tmp2);
	return tmp1.molecule_ < tmp2.molecule_;
}
bool Fraction::operator>(const Fraction& rhs)const {
	Fraction tmp1(*this), tmp2(rhs);
	Reduce(tmp1, tmp2);
	return tmp1.molecule_ > tmp2.molecule_;
}
bool Fraction::operator<=(const Fraction& rhs)const {
	return !(*this > rhs);
}
bool Fraction::operator>=(const Fraction& rhs)const {
	return !(*this < rhs);
}

Fraction::operator double()const {
	return (double)molecule_ / denominator_;
}

const Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
	return Fraction(lhs) += rhs;
}
const Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
	return Fraction(lhs) -= rhs;
}
const Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
	return Fraction(lhs) *= rhs;
}
const Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
	return Fraction(lhs) /= rhs;
}

const Fraction operator+(const Fraction& lhs, int rhs) {
	return Fraction(lhs) += rhs;
}
const Fraction operator-(const Fraction& lhs, int rhs) {
	return Fraction(lhs) -= rhs;
}
const Fraction operator*(const Fraction& lhs, int rhs) {
	return Fraction(lhs) *= rhs;
}
const Fraction operator/(const Fraction& lhs, int rhs) {
	return Fraction(lhs) /= rhs;
}
const Fraction operator+(int lhs, const Fraction& rhs) {
	return Fraction(lhs) += rhs;
}
const Fraction operator-(int lhs, const Fraction& rhs) {
	return Fraction(lhs) -= rhs;
}
const Fraction operator*(int lhs, const Fraction& rhs) {
	return Fraction(lhs) *= rhs;
}
const Fraction operator/(int lhs, const Fraction& rhs) {
	return Fraction(lhs) /= rhs;
}

const Fraction operator+(const Fraction& lhs, double rhs) {
	return Fraction(lhs) += rhs;
}
const Fraction operator-(const Fraction& lhs, double rhs) {
	return Fraction(lhs) -= rhs;
}
const Fraction operator*(const Fraction& lhs, double rhs) {
	return Fraction(lhs) *= rhs;
}
const Fraction operator/(const Fraction& lhs, double rhs) {
	return Fraction(lhs) /= rhs;
}
const Fraction operator+(double lhs, const Fraction& rhs) {
	return Fraction(lhs) += rhs;
}
const Fraction operator-(double lhs, const Fraction& rhs) {
	return Fraction(lhs) -= rhs;
}
const Fraction operator*(double lhs, const Fraction& rhs) {
	return Fraction(lhs) *= rhs;
}
const Fraction operator/(double lhs, const Fraction& rhs) {
	return Fraction(lhs) /= rhs;
}

bool operator==(const Fraction& lhs, int rhs) {
	return lhs == Fraction(rhs);
}
bool operator!=(const Fraction& lhs, int rhs) {
	return lhs != Fraction(rhs);
}
bool operator<(const Fraction& lhs, int rhs) {
	return lhs < Fraction(rhs);
}
bool operator>(const Fraction& lhs, int rhs) {
	return lhs > Fraction(rhs);
}
bool operator<=(const Fraction& lhs, int rhs) {
	return lhs <= Fraction(rhs);
}
bool operator>=(const Fraction& lhs, int rhs) {
	return lhs >= Fraction(rhs);
}
bool operator==(int lhs, const Fraction& rhs) {
	return Fraction(lhs) == rhs;
}
bool operator!=(int lhs, const Fraction& rhs) {
	return Fraction(lhs) != rhs;
}
bool operator<(int lhs, const Fraction& rhs) {
	return Fraction(lhs) < rhs;
}
bool operator>(int lhs, const Fraction& rhs) {
	return Fraction(lhs) > rhs;
}
bool operator<=(int lhs, const Fraction& rhs) {
	return Fraction(lhs) <= rhs;
}
bool operator>=(int lhs, const Fraction& rhs) {
	return Fraction(lhs) >= rhs;
}

bool operator==(const Fraction& lhs, double rhs) {
	return lhs == Fraction(rhs);
}
bool operator!=(const Fraction& lhs, double rhs) {
	return lhs != Fraction(rhs);
}
bool operator<(const Fraction& lhs, double rhs) {
	return lhs < Fraction(rhs);
}
bool operator>(const Fraction& lhs, double rhs) {
	return lhs > Fraction(rhs);
}
bool operator<=(const Fraction& lhs, double rhs) {
	return lhs <= Fraction(rhs);
}
bool operator>=(const Fraction& lhs, double rhs) {
	return lhs >= Fraction(rhs);
}
bool operator==(double lhs, const Fraction& rhs) {
	return Fraction(lhs) == rhs;
}
bool operator!=(double lhs, const Fraction& rhs) {
	return Fraction(lhs) != rhs;
}
bool operator<(double lhs, const Fraction& rhs) {
	return Fraction(lhs) < rhs;
}
bool operator>(double lhs, const Fraction& rhs) {
	return Fraction(lhs) > rhs;
}
bool operator<=(double lhs, const Fraction& rhs) {
	return Fraction(lhs) <= rhs;
}
bool operator>=(double lhs, const Fraction& rhs) {
	return Fraction(lhs) >= rhs;
}

int Gcd(int first, int second) {
	return first == 0 ? second : Gcd(abs(second) % abs(first), abs(first));
}

std::ostream& operator<<(std::ostream& os, const Fraction & f) {
	os << f.molecule_;
	if (f.denominator_ != f.INITIAL_DENOMINATER || f.molecule_ == f.INITIAL_MOLECULE) {
		os << '/' << f.denominator_;
	}
	return os;
}
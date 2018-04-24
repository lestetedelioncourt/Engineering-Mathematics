#include <iostream>
#include <string>
#include "ComplexNumber.h"

using namespace std;

ComplexNumber::ComplexNumber() {
	realpart = 0;
	imagpart = 0;
}

ComplexNumber::ComplexNumber(double real, double imaginary) {
	realpart = real;
	imagpart = imaginary;
}

ComplexNumber::ComplexNumber(const ComplexNumber &rhs) {
	realpart = rhs.realpart;
	imagpart = rhs.imagpart;
}

ComplexNumber ComplexNumber::operator+(const ComplexNumber &rhs) const {
	ComplexNumber temp;
	temp.realpart = realpart + rhs.realpart;
	temp.imagpart = imagpart + rhs.imagpart;
	return temp;
}

ComplexNumber ComplexNumber::operator-(const ComplexNumber &rhs) const {
	ComplexNumber temp;
	temp.realpart = realpart - rhs.realpart;
	temp.imagpart = imagpart - rhs.imagpart;
	return temp;
}

ComplexNumber ComplexNumber::operator*(const ComplexNumber &rhs) const  {
	ComplexNumber temp;
	temp.realpart = (realpart*rhs.realpart) - (imagpart*rhs.imagpart);
	temp.imagpart = (realpart*rhs.imagpart) + (rhs.realpart*imagpart);
	return temp;
}

ComplexNumber ComplexNumber::operator/(const ComplexNumber &rhs) const {
	ComplexNumber compconj[3];
	compconj[0] = ComplexNumber(rhs.realpart, -rhs.imagpart);
	compconj[1] = *this * compconj[0];
	compconj[2] = rhs * compconj[0];

	ComplexNumber temp;
	double a = (compconj[1].realpart / compconj[2].realpart);
	double b = (compconj[1].imagpart / compconj[2].imagpart);
	double c = (compconj[1].imagpart / compconj[2].realpart);
	double d = -(compconj[1].realpart / compconj[2].imagpart);

	if (compconj[1].realpart == 0) {
		a = 0; d = 0;
	}
	if (compconj[1].imagpart == 0) {
		b = 0; c = 0;
	}
	if (compconj[2].realpart == 0) {
		a = 0; c = 0;
	}
	if (compconj[2].imagpart == 0) {
		b = 0; d = 0;
	}

	temp.realpart = a + b;
	temp.imagpart = c + d;

	return temp;
}

const ComplexNumber& ComplexNumber::operator=(const ComplexNumber &rhs) {
	realpart = rhs.realpart;
	imagpart = rhs.imagpart;
	return *this;
}

bool ComplexNumber::operator==(const ComplexNumber &rhs) {
	if ((realpart == rhs.realpart) && (imagpart == rhs.imagpart)) {
		return true;
	}
	else {
		return false;
	}
}

bool ComplexNumber::operator!=(const ComplexNumber &rhs) {
	if ((realpart == rhs.realpart) && (imagpart == rhs.imagpart)) {
		return false;
	}
	else {
		return true;
	}
}

bool ComplexNumber::operator<(const ComplexNumber &rhs) {
	if (realpart < rhs.realpart) {
		return true;
	}
	else if ((realpart == rhs.realpart) && (imagpart < rhs.imagpart)) {
		return true;
	}
	else {
		return false;
	}
}

bool ComplexNumber::operator<=(const ComplexNumber &rhs) {
	if (realpart < rhs.realpart) {
		return true;
	}
	else if ((realpart == rhs.realpart) && (imagpart <= rhs.imagpart)) {
		return true;
	}
	else {
		return false;
	}
}

bool ComplexNumber::operator>(const ComplexNumber &rhs) {
	if (realpart > rhs.realpart) {
		return true;
	}
	else if ((realpart == rhs.realpart) && (imagpart > rhs.imagpart)) {
		return true;
	}
	else {
		return false;
	}
}

bool ComplexNumber::operator>=(const ComplexNumber &rhs) {
	if (realpart > rhs.realpart) {
		return true;
	}
	else if ((realpart == rhs.realpart) && (imagpart >= rhs.imagpart)) {
		return true;
	}
	else {
		return false;
	}
}

istream& operator>>(istream &in, ComplexNumber &rhs) {
	in >> rhs.realpart >> rhs.imagpart;
	return in;
}

ostream& operator<<(ostream& out, const ComplexNumber &rhs) {
	out << rhs.realpart << " + " << rhs.imagpart << "i";
	return out;
}

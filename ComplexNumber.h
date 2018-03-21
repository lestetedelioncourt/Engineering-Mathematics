#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>
#include <string>

using namespace std;

class ComplexNumber {
public:
	ComplexNumber();
	ComplexNumber(double, double);
	ComplexNumber(const ComplexNumber&);

	double realpart;
	double imagpart;

	ComplexNumber operator+(const ComplexNumber&) const;
	ComplexNumber operator-(const ComplexNumber&) const;
	ComplexNumber operator*(const ComplexNumber&) const;
	ComplexNumber operator/(const ComplexNumber&) const;
	const ComplexNumber& operator=(const ComplexNumber&);
	bool operator<(const ComplexNumber&);
	bool operator>(const ComplexNumber&);
	bool operator>=(const ComplexNumber&);
	bool operator<=(const ComplexNumber&);
	bool operator==(const ComplexNumber&);
	bool operator!=(const ComplexNumber&);
	friend ostream& operator<<(ostream&, const ComplexNumber&);
	friend istream& operator<<(istream&, const ComplexNumber&);
};

#endif
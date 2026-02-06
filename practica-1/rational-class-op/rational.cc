// Hugo García Sánchez (930108)
// Óscar Grimal Torres (926897)

#include "rational.h"

// Auxiliares, privadas
int Rational::mcd(int a, int b)
{
	return (b == 0 ? a : mcd(b, a % b));
}

void Rational::reduce()
{
	int divisor = mcd(
		(num < 0 ? -num : num),
		(den < 0 ? -den : den));

	num /= divisor;
	den /= divisor;

	if (den < 0)
	{
		num = -num;
		den = -den;
	}
}

//=============== Constructores ===============//

Rational::Rational()
{
	num = 0;
	den = 1;
}

Rational::Rational(int num, int den)
{
	this->num = num;
	this->den = den;
	reduce();
}

//=============== Entrada/salida ===============//

std::ostream &operator<<(std::ostream &os, const Rational &r)
{
	os << r.num << "/" << r.den;
	return os;
}

std::istream &operator>>(std::istream &is, Rational &r)
{
	char slash;
	is >> r.num >> slash >> r.den;
	r.reduce();
	return is;
}

//=============== Operaciones aritmeticas ===============//

Rational Rational::operator+(const Rational &other) const
{
	Rational result;
	result.num = num * other.den + other.num * den;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational Rational::operator-(const Rational &other) const
{
	Rational result;
	result.num = num * other.den - other.num * den;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational operator*(const Rational &left, const Rational &right)
{
	Rational result;
	result.num = left.num * right.num;
	result.den = left.den * right.den;
	result.reduce();
	return result;
}

Rational operator/(const Rational &left, const Rational &right)
{
	Rational result;
	result.num = left.num * right.den;
	result.den = left.den * right.num;
	result.reduce();
	return result;
}

//=============== Operaciones logicas ===============//

bool Rational::operator==(const Rational &other) const
{
	// Al dividir this/other da 1 ==> this == other
	return num * other.den == other.num * den;
}

bool Rational::operator<(const Rational &other) const
{
	// Al dividir this/other da < 1 ==> this < other
	return num * other.den < other.num * den;
}

bool Rational::operator>(const Rational &other) const
{
	// Al dividir this/other da > 1 ==> this > other
	return num * other.den > other.num * den;
}
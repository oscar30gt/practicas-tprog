#include "rational.h"

// Auxiliares, privadas
int Rational::mcd(int a, int b)
{
	return (b == 0 ? a : mcd(b, a % b));
}

void Rational::reduce()
{
	int divisor = mcd(abs(num), abs(den));
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
	if (den == 0)
	{
		std::cerr << "Error: Inicialización con denominador cero." << std::endl;
		return; // No inicializa
	}

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

Rational Rational::operator*(const Rational &other) const
{
	Rational result;
	result.num = num * other.num;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational Rational::operator/(const Rational &other) const
{
	if (other.num == 0)
	{
		std::cerr << "Error: División por cero." << std::endl;
		return Rational(); // Devuelve 0
	}

	Rational result;
	result.num = num * other.den;
	result.den = den * other.num;
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
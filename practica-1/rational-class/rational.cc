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

void Rational::write(std::ostream &os) const
{
	os << num << "/" << den;
}

void Rational::read(std::istream &is)
{
	char slash;
	is >> num >> slash >> den;
	reduce();
}

//=============== Operaciones aritmeticas ===============//

Rational Rational::add(const Rational &other) const
{
	Rational result;
	result.num = num * other.den + other.num * den;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational Rational::sub(const Rational &other) const
{
	Rational result;
	result.num = num * other.den - other.num * den;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational Rational::mul(const Rational &other) const
{
	Rational result;
	result.num = num * other.num;
	result.den = den * other.den;
	result.reduce();
	return result;
}

Rational Rational::div(const Rational &other) const
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

bool Rational::equal(const Rational &other) const
{
	// Al dividir this/other da 1 ==> this == other
	return num * other.den == other.num * den;
}

bool Rational::lesser_than(const Rational &other) const
{
	// Al dividir this/other da < 1 ==> this < other
	return num * other.den < other.num * den;
}

bool Rational::greater_than(const Rational &other) const
{
	// Al dividir this/other da > 1 ==> this > other
	return num * other.den > other.num * den;
}
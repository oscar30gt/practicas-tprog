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

	// Dividimos numerador y denominador por el máximo común divisor
	num /= divisor;
	den /= divisor;

	// Si el denominador es negativo, cambiamos el signo del numerador y del denominador
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
	// Simplificamos el número racional
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
	// Leemos el número racional de la forma num/den
	char slash;
	is >> r.num >> slash >> r.den;
	// Simplificamos el número racional
	r.reduce();
	return is;
}

//=============== Operaciones aritmeticas ===============//

Rational Rational::operator+(const Rational &other) const
{
	// Para sumar dos números racionales, sumamos los numeradores multiplicados por el otro denominador y multiplicamos los denominadores
	Rational result;
	result.num = num * other.den + other.num * den;
	result.den = den * other.den;
	// Simplificamos el número racional
	result.reduce();
	return result;
}

Rational Rational::operator-(const Rational &other) const
{
	// Para restar dos números racionales, restamos los numeradores multiplicados por el otro denominador y multiplicamos los denominadores
	Rational result;
	result.num = num * other.den - other.num * den;
	result.den = den * other.den;
	// Simplificamos el número racional
	result.reduce();
	return result;
}

Rational operator*(const Rational &left, const Rational &right)
{
	// Para multiplicar dos números racionales, multiplicamos los numeradores y los denominadores
	Rational result;
	result.num = left.num * right.num;
	result.den = left.den * right.den;
	// Simplificamos el número racional
	result.reduce();
	return result;
}

Rational operator/(const Rational &left, const Rational &right)
{
	// Para dividir dos números racionales, realizamos el producto cruzado de los numeradores y denominadores
	Rational result;
	result.num = left.num * right.den;
	result.den = left.den * right.num;
	// Simplificamos el número racional
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
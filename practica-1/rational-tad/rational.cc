// Hugo García Sánchez (930108)
// Óscar Grimal Torres (926897)

#include "rational.h"

// Auxiliares, privadas
int mcd(int a, int b)
{
	return (b == 0 ? a : mcd(b, a % b));
}

void reduce(Rational &r)
{
	int divisor = mcd(
		(r.num < 0 ? -r.num : r.num),
		(r.den < 0 ? -r.den : r.den));
	
	r.num /= divisor;
	r.den /= divisor;
	
	if (r.den < 0)
	{
		r.num = -r.num;
		r.den = -r.den;
	}
}

//============ Inicializadores ==============//

void init(Rational &r)
{
	r.num = 0;
	r.den = 1;
}

void init(Rational &r, int num, int den)
{
	r.num = num;
	r.den = den;
	reduce(r);
}

//============ Entrada/salida ==============//

void write(std::ostream &os, const Rational &r)
{
	os << r.num << "/" << r.den;
}

void read(std::istream &is, Rational &r)
{
	char slash;
	is >> r.num >> slash >> r.den;
	reduce(r);
}

//============ Operaciones aritmeticas ==============//

Rational add(const Rational &r1, const Rational &r2)
{
	Rational result;
	result.num = r1.num * r2.den + r2.num * r1.den;
	result.den = r1.den * r2.den;
	reduce(result);
	return result;
}

Rational sub(const Rational &r1, const Rational &r2)
{
	Rational result;
	result.num = r1.num * r2.den - r2.num * r1.den;
	result.den = r1.den * r2.den;
	reduce(result);
	return result;
}

Rational mul(const Rational &r1, const Rational &r2)
{
	Rational result;
	result.num = r1.num * r2.num;
	result.den = r1.den * r2.den;
	reduce(result);
	return result;
}

Rational div(const Rational &r1, const Rational &r2)
{
	Rational result;
	result.num = r1.num * r2.den;
	result.den = r1.den * r2.num;
	reduce(result);
	return result;
}

//============ Operaciones logicas ==============//

bool equal(const Rational &r1, const Rational &r2)
{
	// Al dividir r1/r2 da 1 ==> r1 == r2
	return (r1.num * r2.den == r2.num * r1.den);
}

bool lesser_than(const Rational &r1, const Rational &r2)
{
	// Al dividir r1/r2 da < 1 ==> r1 < r2
	return (r1.num * r2.den < r2.num * r1.den);
}

bool greater_than(const Rational &r1, const Rational &r2)
{
	// Al dividir r1/r2 da > 1 ==> r1 > r2
	return (r1.num * r2.den > r2.num * r1.den);
}
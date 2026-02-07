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
	
	// Dividimos numerador y denominador por el máximo común divisor
	r.num /= divisor;
	r.den /= divisor;
	
	// Si el denominador es negativo, cambiamos el signo del numerador y del denominador
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
	// Simplificamos el número racional
	reduce(r);
}

//============ Entrada/salida ==============//

void write(std::ostream &os, const Rational &r)
{
	os << r.num << "/" << r.den;
}

void read(std::istream &is, Rational &r)
{
	// Leemos el número racional de la forma num/den
	char slash;
	is >> r.num >> slash >> r.den;
	// Simplificamos el número racional
	reduce(r);
}

//============ Operaciones aritmeticas ==============//

Rational add(const Rational &r1, const Rational &r2)
{
	// Para sumar dos números racionales, sumamos los numeradores multiplicados por el otro denominador y multiplicamos los denominadores
	Rational result;
	result.num = r1.num * r2.den + r2.num * r1.den;
	result.den = r1.den * r2.den;
	// Simplificamos el número racional
	reduce(result);
	return result;
}

Rational sub(const Rational &r1, const Rational &r2)
{
	// Para restar dos números racionales, restamos los numeradores multiplicados por el otro denominador y multiplicamos los denominadores
	Rational result;
	result.num = r1.num * r2.den - r2.num * r1.den;
	result.den = r1.den * r2.den;
	// Simplificamos el número racional
	reduce(result);
	return result;
}

Rational mul(const Rational &r1, const Rational &r2)
{
	// Para multiplicar dos números racionales, multiplicamos los numeradores y los denominadores
	Rational result;
	result.num = r1.num * r2.num;
	result.den = r1.den * r2.den;
	// Simplificamos el número racional
	reduce(result);
	return result;
}

Rational div(const Rational &r1, const Rational &r2)
{
	// Para dividir dos números racionales, realizamos el producto cruzado de los numeradores y denominadores
	Rational result;
	result.num = r1.num * r2.den;
	result.den = r1.den * r2.num;
	// Simplificamos el número racional
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
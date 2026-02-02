// Solución del tipo Rational como clase con operadores sobrecargados

#pragma once
#include <iostream>

/**
 * Representa un numero racional o fracción.
 */
class Rational
{
private:
	/** Numerador y denominador de la fraccion */
	int num, den;

	// Auxiliares
	static int mcd(int a, int b);
	void reduce();

public:
	// Constructores
	Rational();
	Rational(int num, int den);

	// Entrada/salida
	friend std::ostream &operator<<(std::ostream &os, const Rational &r);
	friend std::istream &operator>>(std::istream &is, Rational &r);

	// Operadores
	Rational operator+(const Rational &other) const;
	Rational operator-(const Rational &other) const;
	Rational operator*(const Rational &other) const;
	Rational operator/(const Rational &other) const;
	bool operator==(const Rational &other) const;
	bool operator<(const Rational &other) const;
	bool operator>(const Rational &other) const;
};

// Entrada/salida
std::ostream &operator<<(std::ostream &os, const Rational &r);
std::istream &operator>>(std::istream &is, Rational &r);
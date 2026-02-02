// Solución del tipo Rational como clase

#pragma once
#include <iostream>

/**
 * Representa un número racional o fraccion.
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

	// Funciones públicas
	void write(std::ostream& os) const;
	void read(std::istream& is);
	Rational add(const Rational& other) const;
	Rational sub(const Rational& other) const;
	Rational mul(const Rational& other) const;
	Rational div(const Rational& other) const;
	bool equal(const Rational& other) const;
	bool lesser_than(const Rational& other) const;
	bool greater_than(const Rational& other) const;
};

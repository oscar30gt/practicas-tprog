// Solución del tipo Rational como clase
// Hugo García Sánchez (930108)
// Óscar Grimal Torres (926897)

#pragma once
#include <iostream>

/**
 * Representa un número racional o fraccion.
 */
class Rational
{
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
	void write(std::ostream& os) const;
	void read(std::istream& is);
	
	// Aritméticas: operan este racional con otro y devuelven el resultado
	Rational add(const Rational& other) const;
	Rational sub(const Rational& other) const;
	Rational mul(const Rational& other) const;
	Rational div(const Rational& other) const;

	// Lógicas: comparan este racional con otro y devuelven el resultado
	bool equal(const Rational& other) const;
	bool lesser_than(const Rational& other) const;
	bool greater_than(const Rational& other) const;
};
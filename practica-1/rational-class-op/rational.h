// Solución del tipo Rational como clase con operadores sobrecargados
// Hugo García Sánchez (930108)
// Óscar Grimal Torres (926897)

#pragma once
#include <iostream>

/**
 * Representa un numero racional o fracción.
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
	friend std::ostream &operator<<(std::ostream &os, const Rational &r);
	friend std::istream &operator>>(std::istream &is, Rational &r);

	// Operaciones aritmeticas: operan este racional con otro y devuelven el resultado. 
	// Suma y resta se implementan como métodos y multiplicación y división como funciones externas a la clase
	Rational operator+(const Rational &other) const;
	Rational operator-(const Rational &other) const;
	friend Rational operator*(const Rational &left, const Rational &right);
	friend Rational operator/(const Rational &left, const Rational &right);

	// Operaciones logicas: comparan este racional con otro y devuelven el resultado
	bool operator==(const Rational &other) const;
	bool operator<(const Rational &other) const;
	bool operator>(const Rational &other) const;
};

Rational operator*(const Rational &left, const Rational &right);
Rational operator/(const Rational &left, const Rational &right);

/**
 * Escribe el numero racional en el flujo de salida
 * @param os Flujo de salida
 * @param r Numero racional a escribir
 * @returns Flujo de salida dado
 */
std::ostream &operator<<(std::ostream &os, const Rational &r);

/**
 * Lee un numero racional del flujo de entrada
 * @param is Flujo de entrada
 * @param r Numero racional donde almacenar el valor leído
 * @returns Flujo de entrada dado
 */
std::istream &operator>>(std::istream &is, Rational &r);
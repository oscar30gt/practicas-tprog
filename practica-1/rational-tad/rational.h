// Solución del tipo Rational como TAD
// Hugo García Sánchez (930108)
// Óscar Grimal Torres (926897)

#pragma once
#include <iostream>

/**
 * Representa un numero racional o fracción.
 */
struct Rational
{
private:
	/** Numerador y denominador de la fracción */
	int num, den;

	// Auxiliares
	friend void reduce(Rational &r);

public:
	friend void init(Rational &r);
	friend void init(Rational &r, int num, int den);
	friend void write(std::ostream &os, const Rational &r);
	friend void read(std::istream &is, Rational &r);
	friend Rational add(const Rational &r1, const Rational &r2);
	friend Rational sub(const Rational &r1, const Rational &r2);
	friend Rational mul(const Rational &r1, const Rational &r2);
	friend Rational div(const Rational &r1, const Rational &r2);
	friend bool equal(const Rational &r1, const Rational &r2);
	friend bool lesser_than(const Rational &r1, const Rational &r2);
	friend bool greater_than(const Rational &r1, const Rational &r2);
};

// Inicializadores

/**
 * Inicializa el numero racional a 0/1
 * @param r Racional cuyo valor se quiere inicializar
 */
void init(Rational &r);

/**
 * Inicializa el numero racional con el numerador y denominador dados
 * @param r Racional cuyo valor se quiere inicializar
 * @param num Numerador
 * @param den Denominador
 */
void init(Rational &r, int num, int den);

// Entrada/salida

/**
 * Escribe el numero racional en el flujo de salida
 * @param os Flujo de salida
 * @param r Numero racional a escribir
 */
void write(std::ostream &os, const Rational &r);

/**
 * Lee un numero racional del flujo de entrada
 * @param is Flujo de entrada
 * @param r Numero racional donde almacenar el valor leído
 */
void read(std::istream &is, Rational &r);

// Operaciones aritmeticas

/**
 * Suma dos numeros racionales
 * @param r1 Sumando 1
 * @param r2 Sumando 2
 * @returns Resultado de la suma
 */
Rational add(const Rational &r1, const Rational &r2);

/**
 * Resta dos numeros racionales
 * @param r1 Minuendo
 * @param r2 Sustraendo
 * @returns Resultado de la resta
 */
Rational sub(const Rational &r1, const Rational &r2);

/**
 * Multiplica dos numeros racionales
 * @param r1 Factor 1
 * @param r2 Factor 2
 * @returns Resultado de la multiplicación
 */
Rational mul(const Rational &r1, const Rational &r2);

/**
 * Divide dos numeros racionales
 * @param r1 Dividendo
 * @param r2 Divisor
 * @returns Resultado de la división
 */
Rational div(const Rational &r1, const Rational &r2);

// Operaciones logicas

/**
 * Compara dos numeros racionales
 * @param r1 Operando 1
 * @param r2 Operando 2
 * @returns `true` si son iguales, `false` en caso contrario
 */
bool equal(const Rational &r1, const Rational &r2);

/**
 * Compara dos numeros racionales
 * @param r1 Operando 1
 * @param r2 Operando 2
 * @returns `true` si r1 < r2, `false` en caso contrario
 */
bool lesser_than(const Rational &r1, const Rational &r2);

/**
 * Compara dos numeros racionales
 * @param r1 Operando 1
 * @param r2 Operando 2
 * @returns `true` si r1 > r2, `false` en caso contrario
 */
bool greater_than(const Rational &r1, const Rational &r2);

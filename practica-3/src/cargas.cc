#include "cargas.h"
#include "elemento.h"


Carga::Carga(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), _peso(peso) {}

double Carga::peso() const { return _peso; }

Producto::Producto(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

SerVivo::SerVivo(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

Toxico::Toxico(const string &nombre, double volumen, double peso)
    : Elemento(nombre, volumen), Carga(nombre, volumen, peso) {}

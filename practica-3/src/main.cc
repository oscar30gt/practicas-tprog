#include <iostream>
#include "practica3.h"

using namespace std;

int main()
{
    Camion camion(20);

    Producto* patatas = new Producto("Patatas", 0.5, 1);
    Producto* cerveza = new Producto("Cerveza", 0.3, 0.5);
    Producto* coche = new Producto("Coche", 10, 1000);
    Producto* sofa = new Producto("Sofa", 5, 200);
    Producto* nevera = new Producto("Nevera", 3, 150);

    Contenedor* contenedor1 = new Contenedor(10);
    contenedor1->guardar(patatas);
    contenedor1->guardar(cerveza);
    contenedor1->guardar(sofa);

    Contenedor* contenedor2 = new Contenedor(15);
    contenedor2->guardar(coche);
    contenedor2->guardar(nevera);

    camion.guardar(contenedor1);
    camion.guardar(contenedor2);

    cout << camion << endl;
    
    return 0;
}
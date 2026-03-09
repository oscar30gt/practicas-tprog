#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <iomanip>  // Para manipular el formato si fuera necesario
#include "shell.h"

using namespace std;

// Colores para que sea más profesional
const string G = "\033[32m"; // Green
const string R = "\033[31m"; // Red
const string B = "\033[34m"; // Blue
const string X = "\033[0m";  // Reset

void test_result(bool condition, const string& msg) {
    if (condition) {
        cout << "[" << G << "OK" << X << "] " << msg << endl;
    } else {
        cerr << "[" << R << "FAIL" << X << "] " << msg << endl;
        exit(1); 
    }
}

int main() {
    Shell sh;
    
    cout << "\n" << string(15, '*') << " INICIANDO PRUEBAS DEL SISTEMA " << string(15, '*') << "\n" << endl;

    try {
        // --- TEST 1: Restricción de nombres (No '/') ---
        try {
            sh.mkdir("carpeta/con/barra");
            test_result(false, "No debería permitir mkdir con '/'");
        } catch (...) {
            test_result(true, "Restricción '/' en mkdir");
        }

        try {
            sh.vi("fichero/error", 10);
            test_result(false, "No debería permitir vi con '/'");
        } catch (...) {
            test_result(true, "Restricción '/' en vi");
        }

        try {
            sh.ln("/", "enlace/error");
            test_result(false, "No debería permitir ln con '/' en el nombre");
        } catch (...) {
            test_result(true, "Restricción '/' en nombre de ln");
        }

        // --- TEST 2: Navegación y Enlaces ---
        sh.mkdir("home");
        sh.cd("home");
        sh.mkdir("user");
        sh.cd("user");
        sh.vi("info.txt", 500);
        test_result(sh.pwd() == "/home/user", "Navegación profunda: /home/user");

        sh.cd("/");
        sh.ln("/home/user", "link_directo");
        sh.cd("link_directo");
        test_result(sh.pwd() == "/link_directo", "Entrada por enlace simbólico");
        test_result(sh.stat("info.txt") == "500 Bytes", "Acceso a datos tras enlace");

        // --- TEST 3: El Suelo que Desaparece ---
        sh.rm("/home/user");
        
        test_result(sh.pwd() == "/link_directo", "El CWD persiste tras rm (Borrado diferido)");
        test_result(sh.stat("info.txt") == "500 Bytes", "Contenido accesible tras rm (nlinks > 0)");
        
        sh.cd("..");
        test_result(sh.pwd() == "/", "Salida segura de directorio borrado");

        // --- TEST 4: Verificación de Tamaños (du/stat) ---
        sh.mkdir("temp");
        sh.cd("temp");
        sh.vi("a", 100);
        sh.vi("b", 200);
        sh.cd("..");
        test_result(sh.stat("temp") == "300 Bytes", "Tamaño acumulado de directorio");

        cout << "\n" << G << string(17, '*') << " TODOS LOS TESTS PASADOS " << string(17, '*') << X << endl;

    } catch (const exception& e) {
        cerr << "\n" << R << "CRASH INESPERADO" << X << ": " << e.what() << endl;
        return 1;
    }

    return 0;
}
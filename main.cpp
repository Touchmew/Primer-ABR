//hallo
#include <iostream>
#include <string>
// estruct 

struct Persona{
  string  nombre;
  String fechaNacimiento;
  Persona* hijoIzquierdo;
  Persona* hijoDerecho;
  Persona(string _nombre, string _fecha)
        : nombre(_nombre), fechaNacimiento(_fecha),
          padre(NULL), hijoIzquierdo(NULL), hijoDerecho(NULL) {}
};
//Funcion crear persona

Persona* crearPersona(string nombre, string fecha) {
    return new Persona(nombre, fecha);
}
// Insertar, Alvaro
// Buscar , Almir 
//Eliminar, Daniel 

//Main menu , jhul 
int main() {
    int opcion;

    do {
        cout << "\n--- MENU ARBOL BINARIO GENEALOGICO ---\n";
        cout << "1. Crear persona raiz\n";
        cout << "2. Anadir hijo (izquierdo o derecho)\n";
        cout << "3. Buscar persona por nombre\n";
        cout << "4. Eliminar\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                crearRaiz();
                break;
            case 2:
                anadirHijo();
                break;
            case 3:
                buscarPersona();
                break;
            case 4:
                Eliminar();
                break;
          case 5:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 0);
//que se hace en esta cosa?

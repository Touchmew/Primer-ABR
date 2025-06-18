#include <iostream>
#include <string>
using namespace std;
// estruct 

struct Persona{
  string  nombre;
  string fechaNacimiento;
  Persona* padre;
  Persona* hijoIzquierdo;
  Persona* hijoDerecho;
  Persona(string _nombre, string _fecha)
        : nombre(_nombre), fechaNacimiento(_fecha),
          padre(NULL), hijoIzquierdo(NULL), hijoDerecho(NULL) {}
};
//nodo global
Persona* raiz = NULL;
//Funcion crear persona
Persona* crearPersona(string nombre, string fecha) {
    return new Persona(nombre, fecha);
}
//funcion para buscar recurrsiva
Persona* buscarPorNombre(Persona* nodo, const string& nombre) {
    if (nodo == NULL) return NULL;
    if (nodo->nombre == nombre) return nodo;

    Persona* encontrado = buscarPorNombre(nodo->hijoIzquierdo, nombre);
    if (encontrado != NULL) return encontrado;

    return buscarPorNombre(nodo->hijoDerecho, nombre);
}
//arbol de raiz
void crearRaiz() {
    if (raiz != NULL) {
        cout << "Ya existe una raiz.\n";
        return;
    }

    string nombre, fecha;
    cout << "Ingrese el nombre de la persona raiz: ";
    getline(cin, nombre);
    cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
    getline(cin, fecha);

    raiz = crearPersona(nombre, fecha);
    cout << "Raiz creada correctamente.\n";
}
// Insertar, Alvaro
void anadirHijo() {
    if (raiz == NULL) {
        cout << "Primero debes crear la persona raiz.\n";
        return;
    }

    string padreNombre;
    cout << "Ingrese el nombre del padre/madre: ";
    getline(cin, padreNombre);

    Persona* padre = buscarPorNombre(raiz, padreNombre);
    if (padre == NULL) {
        cout << "Padre/madre no encontrado.\n";
        return;
    }

    string hijoNombre, fecha;
    cout << "Ingrese el nombre del hijo: ";
    getline(cin, hijoNombre);
    cout << "Ingrese la fecha de nacimiento: ";
    getline(cin, fecha);

    string direccion;
    cout << "¿Hijo izquierdo o derecho? (i/d): ";
    getline(cin, direccion);

    if (direccion == "i") {
        if (padre->hijoIzquierdo == NULL) {
            padre->hijoIzquierdo = crearPersona(hijoNombre, fecha);
            cout << "Hijo izquierdo agregado correctamente.\n";
        } else {
            cout << "Este padre ya tiene un hijo izquierdo.\n";
        }
    } else if (direccion == "d") {
        if (padre->hijoDerecho == NULL) {
            padre->hijoDerecho = crearPersona(hijoNombre, fecha);
            cout << "Hijo derecho agregado correctamente.\n";
        } else {
            cout << "Este padre ya tiene un hijo derecho.\n";
        }
    } else {
        cout << "Opcion invalida. Usa 'i' para izquierdo o 'd' para derecho.\n";
    }
}
// Buscar , Almir 
void buscarPersona() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre;
    cout << "Nombre a buscar: ";
    getline(cin, nombre);
    Persona* persona = buscarPorNombre(raiz, nombre);

    if (persona != NULL) {
        cout << "Persona encontrada: " << persona->nombre
             << ", Fecha de nacimiento: " << persona->fechaNacimiento << "\n";
    } else {
        cout << "No se encontro a " << nombre << ".\n";
    }
}

//Eliminar, Daniel 
void eliminarPersona() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre;
    cout << "Nombre de la persona a eliminar: ";
    getline(cin, nombre);
    Persona* persona = buscarPorNombre(raiz, nombre);

    if (persona == NULL) {
        cout << "No se encontro a " << nombre << ".\n";
        return;
    }

    // No se permite eliminar si tiene hijos
    if (persona->hijoIzquierdo != NULL || persona->hijoDerecho != NULL) {
        cout << "No se puede eliminar a " << nombre << " porque tiene hijos.\n";
        return;
    }

    // Si es la raiz
    if (persona == raiz) {
        delete raiz;
        raiz = NULL;
        cout << "Raiz eliminada correctamente.\n";
        return;
    }

    // Eliminar desde el padre
    Persona* padre = persona->padre;
    if (padre->hijoIzquierdo == persona) {
        padre->hijoIzquierdo = NULL;
    } else if (padre->hijoDerecho == persona) {
        padre->hijoDerecho = NULL;
    }

    delete persona;
    cout << "Persona eliminada correctamente.\n";
}
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
                eliminarPersona();
                break;
          case 5:
                cout << "Saliendo del programa.\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
  return 0;
}


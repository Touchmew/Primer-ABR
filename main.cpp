#include <iostream>
#include <string>
#include <iomanip> // Para std::setw
#include <clocale> // nesesario para el uso del setlocale
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
void insertarPersona() {
    string nombre, fecha;
    cout << "Ingrese el nombre: ";    // Se solicita al usuario el nombre y la fecha de nacimiento
    getline(cin, nombre);
    cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
    getline(cin, fecha);

    if (fecha.length() < 10 || fecha[4] != '-' || fecha[7] != '-') { // Se valida que la fecha tenga el formato correcto (YYYY-MM-DD)
        cout << "Formato de fecha inv�lido. Use YYYY-MM-DD.\n";
        return; // Sale de la funcion si el formato no es valido
    }
    Persona* nueva = new Persona(nombre, fecha); // Se crea una nueva persona con los datos ingresados
    // Si el arbol esta vacio, se asigna la nueva persona como raiz
    if (raiz == NULL) {
        raiz = nueva;
        cout << "Persona ra�z creada correctamente.\n";
        return;
    }
    Persona* actual = raiz; // Se busca la posicion adecuada en el arbol
    Persona* padre = NULL;

    while (actual != NULL) {
        padre = actual;
        if (fecha < actual->fechaNacimiento) { // Si la fecha es menor, se va al hijo izquierdo
            actual = actual->hijoIzquierdo;
        }
        else if (fecha > actual->fechaNacimiento) {  // Si es mayor, se va al hijo derecho
            actual = actual->hijoDerecho;
        }
        else { // Si ya existe una persona con la misma fecha, se cancela la inserci�n
            cout << "Ya existe una persona con esa fecha de nacimiento.\n";
            delete nueva;
            return;
        }
    }
    nueva->padre = padre;
    if (fecha < padre->fechaNacimiento) {    // Se enlaza la nueva persona al padre correspondiente
        padre->hijoIzquierdo = nueva;
    } else {
        padre->hijoDerecho = nueva;
    }

    cout << "Persona insertada correctamente como "    // Mensaje de confirmacion de insercion
         << ((fecha < padre->fechaNacimiento) ? "hijo izquierdo" : "hijo derecho")
         << " de " << padre->nombre << ".\n";
}

// Buscar ,  
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

//Eliminar,   
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
// Elimina recursivamente todos los descendientes de un nodo (subárbol)
void eliminarSubarbol(Persona* nodo) {
    if (nodo == NULL) return;

    eliminarSubarbol(nodo->hijoIzquierdo);
    eliminarSubarbol(nodo->hijoDerecho);
    delete nodo;
}
//Elimina a una persona y todos sus descendientes
void eliminarFamilia() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre;
    cout << "Nombre de la persona cuya familia desea eliminar: ";
    getline(cin, nombre);
    Persona* persona = buscarPorNombre(raiz, nombre);

    if (persona == NULL) {
        cout << "No se encontro a " << nombre << ".\n";
        return;
    }

    if (persona == raiz) {
        eliminarSubarbol(raiz);
        raiz = NULL;
        cout << "Toda la familia (árbol completo) fue eliminada.\n";
        return;
    }

    Persona* padre = persona->padre;
    if (padre->hijoIzquierdo == persona) {
        padre->hijoIzquierdo = NULL;
    } else if (padre->hijoDerecho == persona) {
        padre->hijoDerecho = NULL;
    }

    eliminarSubarbol(persona);
    cout << "Familia descendiente de " << nombre << " eliminada correctamente.\n";
}

// Funcion de busqueda preorden
void buscarPreorden(Persona* nodo) {
    if (nodo == NULL) return;
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    buscarPreorden(nodo->hijoIzquierdo);
    buscarPreorden(nodo->hijoDerecho);
}

// Función de búsqueda en inorden
void buscarInorden(Persona* nodo) {
    if (nodo == NULL) return;
    buscarInorden(nodo->hijoIzquierdo);
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    buscarInorden(nodo->hijoDerecho);
}

// Función de búsqueda en postorden
void buscarPostorden(Persona* nodo) {
    if (nodo == NULL) return;
    buscarPostorden(nodo->hijoIzquierdo);
    buscarPostorden(nodo->hijoDerecho);
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
}

// Recorre el arbol y muestra a todas las personas que nacieron antes que la persona indicada
void buscarAncestrosPorFecha(Persona* nodo, const string& refFecha) {
    if (nodo == NULL) return;

    buscarAncestrosPorFecha(nodo->hijoIzquierdo, refFecha);

    if (nodo->fechaNacimiento < refFecha) {
        cout << "- " << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    }

    buscarAncestrosPorFecha(nodo->hijoDerecho, refFecha);
}

// Recorre el arbol y muestra a todas las personas que nacieron antes que la persona indicada
void buscarAncestrosPorFecha(Persona* nodo, const string& refFecha, int& contador) {
    if (nodo == NULL) return;

    buscarAncestrosPorFecha(nodo->hijoIzquierdo, refFecha, contador);

    if (nodo->fechaNacimiento < refFecha) {
        cout << "- " << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
        contador++;
    }

    buscarAncestrosPorFecha(nodo->hijoDerecho, refFecha, contador);
}

void mostrarAncestros() {
    if (raiz == NULL) {
        cout << "El �rbol est� vac�o.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la persona: ";
    getline(cin, nombre);

    Persona* ref = buscarPorNombre(raiz, nombre);
    if (ref == NULL) {
        cout << "Persona no encontrada.\n";
        return;
    }

    cout << "\nAncestros de " << ref->nombre << " (por fecha):\n";
    int contador = 0;
    buscarAncestrosPorFecha(raiz, ref->fechaNacimiento, contador);

    if (contador == 0) {
        cout << ref->nombre << " no tiene ancestros.\n";
    }
}
// Recorre el arbol y muestra a todas las personas que nacieron despues que la persona indicada
void buscarDescendientesPorFecha(Persona* nodo, const string& refFecha, int& contador) {
    if (nodo == NULL) return;

    buscarDescendientesPorFecha(nodo->hijoIzquierdo, refFecha, contador);

    if (nodo->fechaNacimiento > refFecha) {
        cout << "- " << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
        contador++;
    }

    buscarDescendientesPorFecha(nodo->hijoDerecho, refFecha, contador);
}

void mostrarDescendientes() {
    if (raiz == NULL) {
        cout << "El �rbol est� vac�o.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la persona: ";
    getline(cin, nombre);

    Persona* ref = buscarPorNombre(raiz, nombre);
    if (ref == NULL) {
        cout << "Persona no encontrada.\n";
        return;
    }
    cout << "\nDescendientes de " << ref->nombre << " (por fecha):\n";
    int contador = 0;
    buscarDescendientesPorFecha(raiz, ref->fechaNacimiento, contador);

    if (contador == 0) {
        cout << ref->nombre << " no tiene descendientes.\n";
    }
}


// Compara la fecha de nacimiento de dos personas para decir si una nacio antes o despues que la otra
void consultarRelacion() {
    string nombreA, nombreB;
    cout << "Ingrese el nombre de la primera persona: ";
    getline(cin, nombreA);
    cout << "Ingrese el nombre de la segunda persona: ";
    getline(cin, nombreB);
    Persona* A = buscarPorNombre(raiz, nombreA);
    Persona* B = buscarPorNombre(raiz, nombreB);
    if (A == NULL || B == NULL) {
        cout << "Una o ambas personas no se encuentran.\n";
        return;
    }
    if (A->fechaNacimiento < B->fechaNacimiento) {
        cout << A->nombre << " es ancestro temporal de " << B->nombre << " (naci� antes).\n";
    } else if (A->fechaNacimiento > B->fechaNacimiento) {
        cout << A->nombre << " es descendiente temporal de " << B->nombre << " (naci� despu�s).\n";
    } else {
        cout << A->nombre << " y " << B->nombre << " nacieron el mismo d�a. No hay diferencia temporal.\n";
    }
}

//------------------------Menus de control----------------------------------------------------
// Submena de recorridos
void submenuRecorridos() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ DE RECORRIDOS ---\n";
        cout << "1. Preorden\n";
        cout << "2. Inorden\n";
        cout << "3. Postorden\n";
        cout << "4. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: cout << "\nRecorrido Preorden:\n"; buscarPreorden(raiz); break;
            case 2: cout << "\nRecorrido Inorden:\n"; buscarInorden(raiz); break;
            case 3: cout << "\nRecorrido Postorden:\n"; buscarPostorden(raiz); break;
            case 4: cout << "Volviendo al menú principal...\n"; break;
            default: cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

// Submenu de consultas genealogicas
void submenuConsultas() {
    int opcion;
    do {
        cout << "\n--- SUBMEN� DE CONSULTAS POR FECHA DE NACIMIENTO ---\n";
        cout << "1. Ver ancestros \n";
        cout << "2. Ver descendientes \n";
        cout << "3. Ver relaci�n entre dos personas\n";
        cout << "4. Volver al men� principal\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: mostrarAncestros(); break;           // Consulta ancestros por fecha
            case 2: mostrarDescendientes(); break;       // Consulta descendientes por fecha
            case 3: consultarRelacion(); break;          // Compara dos personas segun su año
            case 4: cout << "Volviendo al men� principal...\n"; break;
            default: cout << "Opci�n inv�lida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

// Submena de eliminación
void submenuEliminar() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ DE ELIMINACIÓN ---\n";
        cout << "1. Eliminar persona (si no tiene hijos)\n";
        cout << "2. Eliminar familia completa (rama descendiente)\n";
        cout << "3. Volver\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
            case 1: eliminarPersona(); break;
            case 2: eliminarFamilia(); break;
            case 3: cout << "Volviendo al menú principal...\n"; break;
            default: cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

// Funcion para mostrar el arbol
void mostrarArbol(Persona* nodo, int espacio = 0, int nivel = 0) {
    if (nodo == NULL) return;
    espacio += 10; // Aumentar el espacio para cada nivel
    // Mostrar hijo derecho primero
    mostrarArbol(nodo->hijoDerecho, espacio, nivel + 1);
    // Mostrar el nodo actual
    cout << endl;
    cout << setw(espacio) << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    // Mostrar hijo izquierdo
    mostrarArbol(nodo->hijoIzquierdo, espacio, nivel + 1);
}
//Main menu ,  
int main() {
	setlocale(LC_CTYPE, "Spanish");    int opcion;
    do {
        cout << "\n--- MENU ARBOL BINARIO GENEALOGICO ---\n";
		cout << "1. Insertar persona\n";
        cout << "2. Buscar persona por nombre\n";
        cout << "3. Eliminar (persona o familia)\n";
        cout << "4. Recorridos (Preorden, Inorden, Postorden)\n";
        cout << "5. Consultas (ancestros, descendientes, relaciones)\n";
        cout << "6. Mostrar Arbol\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion) {
			case 1: insertarPersona(); break;
            case 2: buscarPersona(); break;
            case 3: submenuEliminar(); break;
            case 4: submenuRecorridos(); break;
            case 5: submenuConsultas(); break;
            case 6: mostrarArbol(raiz); break;
            case 7: cout << "Saliendo del programa.\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 7);
    return 0; 
}

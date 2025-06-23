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

// Insertar, 
void insertarPersona() {
    string nombre, fecha;
    cout << "Ingrese el nombre: ";
    getline(cin, nombre);
    cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
    getline(cin, fecha);

    if (fecha.length() < 10 || fecha[4] != '-' || fecha[7] != '-') {
        cout << "Formato de fecha inválido. Use YYYY-MM-DD.\n";
        return;
    }
    Persona* nueva = new Persona(nombre, fecha);    // Insertar la persona automáticamente en el árbol como ABB
    if (raiz == NULL) {
        raiz = nueva;
        cout << "Persona raíz creada correctamente.\n";
        return;
    }

    Persona* actual = raiz;
    Persona* padre = NULL;

    while (actual != NULL) {
        padre = actual;
        if (fecha < actual->fechaNacimiento) {
            actual = actual->hijoIzquierdo;
        } else if (fecha > actual->fechaNacimiento) {
            actual = actual->hijoDerecho;
        } else {
            cout << "Ya existe una persona con esa fecha de nacimiento.\n";
            delete nueva;
            return;
        }
    }
    nueva->padre = padre;
	
    if (fecha < padre->fechaNacimiento) {
        padre->hijoIzquierdo = nueva;
    } else {
        padre->hijoDerecho = nueva;
    }
    cout << "Persona insertada correctamente como "
         << ((fecha < padre->fechaNacimiento) ? "hijo izquierdo" : "hijo derecho")
         << " de " << padre->nombre << ".\n";
}

// Buscar   
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

// Recorre el árbol y muestra a todas las personas que nacieron después que la persona indicada
void buscarDescendientesPorFecha(Persona* nodo, const string& refFecha, int& contador) {
    if (nodo == NULL) return;  // Caso base: si el nodo es nulo, no hay nada que procesar

    // Recorrido en orden: primero el subárbol izquierdo
    buscarDescendientesPorFecha(nodo->hijoIzquierdo, refFecha, contador);

    // Si la fecha de nacimiento del nodo actual es posterior a la fecha de referencia, se muestra
    if (nodo->fechaNacimiento > refFecha) {
        cout << "- " << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
        contador++;  // Se incrementa el contador de personas encontradas
    }

    // Luego se recorre el subárbol derecho
    buscarDescendientesPorFecha(nodo->hijoDerecho, refFecha, contador);
}

// Función que solicita un nombre al usuario y muestra personas nacidas después que esa persona
void mostrarDescendientes() {
    if (raiz == NULL) {
        // Si el árbol está vacío, se informa y se termina la función
        cout << "El árbol está vacío.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la persona: ";
    getline(cin, nombre);  // Se obtiene el nombre de la persona desde la entrada estándar

    // Se busca la persona por nombre en el árbol
    Persona* ref = buscarPorNombre(raiz, nombre);
    if (ref == NULL) {
        // Si la persona no fue encontrada, se informa y se termina la función
        cout << "Persona no encontrada.\n";
        return;
    }

    // Si se encuentra la persona, se busca y muestran las personas nacidas después
    cout << "\nDescendientes de " << ref->nombre << " (por fecha):\n";
    int contador = 0;  // Inicializa el contador de personas encontradas
    buscarDescendientesPorFecha(raiz, ref->fechaNacimiento, contador);

    // Si no se encontro ninguna persona con fecha posterior, se informa
    if (contador == 0) {
        cout << ref->nombre << " no tiene descendientes.\n";
    }
}

// Función que verifica si 'posibleAncestro' es ancestro de 'persona'
bool esAncestro(Persona* posibleAncestro, Persona* persona) { 
    Persona* actual = persona->padre;   // Comienza desde el padre de la persona actual
    while (actual != NULL) {   // Recorre la línea de ascendencia mientras haya padres
        if (actual == posibleAncestro)       // Si encuentra al posible ancestro, retorna true
            return true;
        actual = actual->padre;    // Avanza al siguiente ancestro (padre del padre)
    }
    return false;     // Si no lo encuentra en la cadena de padres, retorna false
}

// Compara la fecha de nacimiento de dos personas para decir si una nació antes o después que la otra
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
        cout << A->nombre << " es ancestro temporal de " << B->nombre << " (nació antes).\n";
    } else if (A->fechaNacimiento > B->fechaNacimiento) {
        cout << A->nombre << " es descendiente temporal de " << B->nombre << " (nació después).\n";
    } else {
        cout << A->nombre << " y " << B->nombre << " nacieron el mismo día. No hay diferencia temporal.\n";
    }
}
//------------------------Menus de control----------------------------------------------------
// Submenú de recorridos
int submenuRecorridos() {
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
    return opcion;
}


// Submenu de consultas genealogicas
void submenuConsultas() {
    int opcion;
    do {
        cout << "\n--- SUBMENÚ DE CONSULTAS POR FECHA DE NACIMIENTO ---\n";
        cout << "1. Ver ancestros \n";
        cout << "2. Ver descendientes \n";
        cout << "3. Ver relación entre dos personas\n";
        cout << "4. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: mostrarAncestros(); break;           // Consulta ancestros por fecha
            case 2: mostrarDescendientes(); break;       // Consulta descendientes por fecha
            case 3: consultarRelacion(); break;          // Compara dos personas según su año
            case 4: cout << "Volviendo al menú principal...\n"; break;
            default: cout << "Opción inválida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

// Submenú de eliminación
int submenuEliminar() {
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
    return opcion;
}

// Función para mostrar el árbol
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
	setlocale(LC_CTYPE, "Spanish");    
  int opcion;
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
    } while (opcion != 8);
    return 0; 
}

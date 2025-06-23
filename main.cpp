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
  // Constructor que inicializa una persona con nombre y fecha de nacimiento,
  // y establece sus punteros a NULL (sin conexiones inicialmente)
  Persona(string _nombre, string _fecha)
        : nombre(_nombre), fechaNacimiento(_fecha),
          padre(NULL), hijoIzquierdo(NULL), hijoDerecho(NULL) {}
};
// Nodo raíz del árbol genealógico (inicio del árbol), declarado como global
Persona* raiz = NULL;
// Función para crear una nueva persona y devolver su puntero
// Recibe el nombre y la fecha de nacimiento como parámetros
Persona* crearPersona(string nombre, string fecha) {
    return new Persona(nombre, fecha); // Crea una nueva instancia de Persona y la devuelve
}
// Función recursiva para buscar una persona por su nombre en el árbol
Persona* buscarPorNombre(Persona* nodo, const string& nombre) {
    if (nodo == NULL) return NULL; // Caso base: si el nodo es NULL, no se encontró
    if (nodo->nombre == nombre) return nodo; // Si el nombre del nodo actual coincide, se retorna

    // Busca recursivamente en el hijo izquierdo
    Persona* encontrado = buscarPorNombre(nodo->hijoIzquierdo, nombre);
    if (encontrado != NULL) return encontrado;  // Si lo encontró, lo retorna
    // Si no se encontró en el hijo izquierdo, busca en el hijo derecho
    return buscarPorNombre(nodo->hijoDerecho, nombre);
}
void insertarPersona() {
    string nombre, fecha;
    cout << "Ingrese el nombre: ";    // Se solicita al usuario el nombre y la fecha de nacimiento
    getline(cin, nombre);
    cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
    getline(cin, fecha);

    if (fecha.length() < 10 || fecha[4] != '-' || fecha[7] != '-') { // Se valida que la fecha tenga el formato correcto (YYYY-MM-DD)
        cout << "Formato de fecha invalido. Use YYYY-MM-DD.\n";
        return; // Sale de la funcion si el formato no es valido
    }
    Persona* nueva = new Persona(nombre, fecha); // Se crea una nueva persona con los datos ingresados
    // Si el arbol esta vacio, se asigna la nueva persona como raiz
    if (raiz == NULL) {
        raiz = nueva;
        cout << "Persona raiz creada correctamente.\n";
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

// Función para buscar una persona por su nombre e imprimir sus datos si se encuentra 
void buscarPersona() {
    // Verifica si el árbol está vacío
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre; // Variable para almacenar el nombre a buscar
    cout << "Nombre a buscar: ";
    getline(cin, nombre);
    // Llama a la función recursiva para buscar la persona desde la raíz
    Persona* persona = buscarPorNombre(raiz, nombre);
    // Si se encontró a la persona, muestra su nombre y fecha de nacimiento
    if (persona != NULL) {
        cout << "Persona encontrada: " << persona->nombre
             << ", Fecha de nacimiento: " << persona->fechaNacimiento << "\n";
    } else {
        cout << "No se encontro a " << nombre << ".\n";
    }
}

// Función para eliminar una persona del árbol genealógico
void eliminarPersona() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre;
    cout << "Nombre de la persona a eliminar: ";
    getline(cin, nombre); // Solicita el nombre de la persona a eliminar
    Persona* persona = buscarPorNombre(raiz, nombre); // Busca la persona en el árbol
    // Si no se encuentra la persona
    if (persona == NULL) {
        cout << "No se encontro a " << nombre << ".\n";
        return;
    }

    // No se permite eliminar si tiene hijos
    if (persona->hijoIzquierdo != NULL || persona->hijoDerecho != NULL) {
        cout << "No se puede eliminar a " << nombre << " porque tiene hijos.\n";
        return;
    }

    // Si la persona a eliminar es la raíz del árbol
    if (persona == raiz) {
        delete raiz; // Libera la memoria de la raíz
        raiz = NULL; // Actualiza la raíz a NULL
        cout << "Raiz eliminada correctamente.\n";
        return;
    }

    // Obtiene el puntero al padre de la persona
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
// Función para eliminar una persona y todos sus descendientes (subárbol familiar)
void eliminarFamilia() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return; // Si no hay nodos, no hay nada que eliminar
    }

    string nombre;
    cout << "Nombre de la persona cuya familia desea eliminar: ";
    getline(cin, nombre); // Solicita el nombre de la persona base para eliminar su familia
    Persona* persona = buscarPorNombre(raiz, nombre); // Busca la persona

    if (persona == NULL) {
        cout << "No se encontro a " << nombre << ".\n";
        return; // Si no se encuentra, se informa y se cancela la operación
    }

    // Si se quiere eliminar toda la familia desde la raíz
    if (persona == raiz) {
        eliminarSubarbol(raiz);
        raiz = NULL;
        cout << "Toda la familia (árbol completo) fue eliminada.\n";
        return;
    }
    // Si no es la raíz, se desconecta del padre
    Persona* padre = persona->padre;
    if (padre->hijoIzquierdo == persona) {
        padre->hijoIzquierdo = NULL;
    } else if (padre->hijoDerecho == persona) {
        padre->hijoDerecho = NULL;
    }

    eliminarSubarbol(persona); // Elimina la persona y sus descendientes
    cout << "Familia descendiente de " << nombre << " eliminada correctamente.\n";
}

// Recorre el árbol en preorden: nodo → izquierdo → derecho
void buscarPreorden(Persona* nodo) {
    if (nodo == NULL) return;
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    buscarPreorden(nodo->hijoIzquierdo);
    buscarPreorden(nodo->hijoDerecho);
}

// Recorre el árbol en inorden: izquierdo → nodo → derecho
void buscarInorden(Persona* nodo) {
    if (nodo == NULL) return;
    buscarInorden(nodo->hijoIzquierdo);
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
    buscarInorden(nodo->hijoDerecho);
}

// Recorre el árbol en postorden: izquierdo → derecho → nodo
void buscarPostorden(Persona* nodo) {
    if (nodo == NULL) return;
    buscarPostorden(nodo->hijoIzquierdo);
    buscarPostorden(nodo->hijoDerecho);
    cout << nodo->nombre << " (" << nodo->fechaNacimiento << ")\n";
}



// Función que muestra los ancestros de una persona en el árbol genealógico
void mostrarAncestros() {
    // Verificamos si el árbol está vacío
    if (raiz == NULL) {
        cout << "El árbol está vacío.\n"; // Mensaje de árbol vacío
        return; // Salimos de la función
    }

    string nombre;
    cout << "Ingrese el nombre de la persona: "; // Solicita el nombre de la persona
    getline(cin, nombre); // Lee el nombre ingresado

    // Buscar la persona en el árbol
    Persona* persona = buscarPorNombre(raiz, nombre);
    if (persona == NULL) {
        cout << "No se encontró a " << nombre << ".\n"; // Mensaje si no se encuentra la persona
        return; // Salimos de la función
    }

    // Mostrar ancestros desde la persona hacia la raíz
    cout << "\nAncestros de " << persona->nombre << ":\n";
    Persona* actual = persona->padre; // Comenzamos desde el padre de la persona
    if (actual == NULL) {
        cout << "No tiene ancestros (es la raíz).\n"; // Mensaje si la persona es la raíz
        return; // Salimos de la función
    }

    // Recorremos hacia arriba en el árbol para mostrar los ancestros
    while (actual != NULL) {
        cout << actual->nombre << " (" << actual->fechaNacimiento << ")\n"; // Mostramos el nombre y fecha de nacimiento del ancestro
        actual = actual->padre; // Avanzamos al siguiente ancestro
    }
}


// void listarDescendientes(Persona* persona, int& contador);
void listarDescendientes(Persona* persona, int& contador) {
    if (persona == NULL) return;

    // Mostrar el nombre de la persona como descendiente
    cout << "- " << persona->nombre << " (descendiente)\n";
    
    // Incrementar el contador de descendientes
    contador++;
    
    // Llamar recursivamente por el hijo izquierdo (si existe)
    listarDescendientes(persona->hijoIzquierdo, contador);
    
    // Llamar recursivamente por el hijo derecho (si existe)
    listarDescendientes(persona->hijoDerecho, contador);
}

// Modifica la llamada en mostrarDescendientes así:
void mostrarDescendientes() {
    if (raiz == NULL) {
        cout << "El árbol está vacío.\n"; // Mensaje de árbol vacío
        return; // Salimos de la función
    }

    string nombre;
    cout << "Ingrese el nombre de la persona para ver sus descendientes: ";
    getline(cin, nombre); // Lee el nombre ingresado

    Persona* persona = buscarPorNombre(raiz, nombre);

    if (persona == NULL) {
        cout << "Persona no encontrada.\n"; // Mensaje si no se encuentra la persona
        return; // Salimos de la función
    }

    int contador = 0; // Inicializamos el contador de descendientes

    // Iniciamos la búsqueda de descendientes desde los hijos de esta persona
    listarDescendientes(persona->hijoIzquierdo, contador);
    listarDescendientes(persona->hijoDerecho, contador);

    if (contador == 0) {
        cout << persona->nombre << " no tiene descendientes.\n"; // Mensaje si no tiene descendientes
    } else {
        cout << persona->nombre << " tiene " << contador << " descendiente(s).\n"; // Mensaje con el número de descendientes
    }
}


// Función que verifica si 'posibleAncestro' es ancestro de 'persona'
bool esAncestro(Persona* posibleAncestro, Persona* persona) { 
    Persona* actual = persona->padre; // Comienza desde el padre de la persona actual
    while (actual != NULL) { // Recorre la línea de ascendencia mientras haya padres
        if (actual == posibleAncestro) // Si encuentra al posible ancestro, retorna true
            return true;
        actual = actual->padre; // Avanza al siguiente ancestro (padre del padre)
    }
    return false; // Si no lo encuentra en la cadena de padres, retorna false
}

// Compara dos personas para ver si una es ancestro de la otra
void consultarRelacion() {
    string nombreA, nombreB; // Nombres de las personas a consultar
    cout << "Ingrese el nombre de la primera persona: "; getline(cin, nombreA); // Solicita y lee el primer nombre
    cout << "Ingrese el nombre de la segunda persona: "; getline(cin, nombreB); // Solicita y lee el segundo nombre

    // Busca la persona A en el árbol
    Persona* A = buscarPorNombre(raiz, nombreA);
    // Busca la persona B en el árbol
    Persona* B = buscarPorNombre(raiz, nombreB);

    // Si alguna de las personas no fue encontrada
    if (A == NULL || B == NULL) {
        cout << "Una o ambas personas no se encuentran.\n"; return; // Muestra mensaje y termina
    }

    // Verifica si A es ancestro de B
    if (esAncestro(A, B)) {
        cout << A->nombre << " es ancestro de " << B->nombre << ".\n"; // Muestra resultado
    } 
    // Verifica si B es ancestro de A
    else if (esAncestro(B, A)) {
        cout << B->nombre << " es ancestro de " << A->nombre << ".\n"; // Muestra resultado
    } 
    // Si no hay relación directa
    else { 
        cout << A->nombre << " y " << B->nombre << " no tienen relación directa.\n"; // Informa sin relación
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
int submenuConsultas() {
    int opcion;
    do {
        cout << "\n--- SUBMENU DE CONSULTAS ---\n";
        cout << "1. Ver ancestros\n";
        cout << "2. Ver descendientes\n";
        cout << "3. Ver relacion entre dos personas\n";
        cout << "4. Volver\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: mostrarAncestros(); break;
            case 2: mostrarDescendientes(); break;
            case 3: consultarRelacion(); break;
            case 4: cout << "Volviendo al menu principal...\n"; break;
            default: cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
    return opcion;
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
        // Se ejecuta la acción correspondiente a la opción elegida
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

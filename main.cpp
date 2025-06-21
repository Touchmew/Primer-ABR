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
  // Verifica si la raíz del árbol existe
    if (raiz == NULL) {
        cout << "Primero debes crear la persona raiz.\n";
    } else {
        string padreNombre;
        cout << "Ingrese el nombre del padre/madre: ";
        getline(cin, padreNombre);
        // Busca al padre en el árbol
        Persona* padre = buscarPorNombre(raiz, padreNombre);
        if (padre == NULL) {
            cout << "Padre/madre no encontrado.\n";
        } else {
            // Validar que la fecha de nacimiento del padre sea válida
            if (padre->fechaNacimiento.length() < 10 || padre->fechaNacimiento[4] != '-' || padre->fechaNacimiento[7] != '-') {
                cout << "La fecha de nacimiento del padre es invalida. Debe ser en formato YYYY-MM-DD.\n";
            } else {
                string hijoNombre, fecha;
                cout << "Ingrese el nombre del hijo: ";
                getline(cin, hijoNombre);
                cout << "Ingrese la fecha de nacimiento (YYYY-MM-DD): ";
                getline(cin, fecha);

                // Validación del formato de la fecha del hijo
                if (fecha.length() < 10 || fecha[4] != '-' || fecha[7] != '-') {
                    cout << "Formato de fecha invalido. Use YYYY-MM-DD.\n";
                } else {
                    // Comparar los años de nacimiento directamente
                    if (fecha < padre->fechaNacimiento) {
                        if (padre->hijoIzquierdo == NULL) {
                            padre->hijoIzquierdo = crearPersona(hijoNombre, fecha);
                            padre->hijoIzquierdo->padre = padre;
                            cout << "Hijo izquierdo agregado correctamente.\n";
                        } else {
                            cout << "Este padre ya tiene un hijo izquierdo.\n"; // Mensaje si ya se tiene uno a la izquierda
                        }
                    } else if (fecha > padre->fechaNacimiento) {
                        if (padre->hijoDerecho == NULL) {
                            padre->hijoDerecho = crearPersona(hijoNombre, fecha);
                            padre->hijoDerecho->padre = padre;
                            cout << "Hijo derecho agregado correctamente.\n";
                        } else {
                            cout << "Este padre ya tiene un hijo derecho.\n"; // Mensaje si ya se tiene uno a la derecha
                        }
                    } else {
                        cout << "La fecha de nacimiento no puede ser la misma.\n";// Mensaje si las fechas son iguales
                    }
                }
            }
        }
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

// Función que muestra los ancestros
void mostrarAncestros() {
    if (raiz == NULL) {
        cout << "El arbol esta vacio.\n";
        return;
    }

    string nombre;
    cout << "Ingrese el nombre de la persona: ";
    getline(cin, nombre);

    // Buscar la persona en el árbol
    Persona* persona = buscarPorNombre(raiz, nombre);
    if (persona == NULL) {
        cout << "No se encontro a " << nombre << ".\n";
        return;
    }

    // Mostrar ancestros desde la persona hacia la raíz
    cout << "\nAncestros de " << persona->nombre << ":\n";
    Persona* actual = persona->padre;
    if (actual == NULL) {
        cout << "No tiene ancestros (es la raiz).\n";
        return;
    }

    while (actual != NULL) {
        cout << actual->nombre << " (" << actual->fechaNacimiento << ")\n";
        actual = actual->padre;
    }
}
// Función auxiliar recursiva que lista todos los descendientes de una persona.
// Parámetros:
// - persona: el nodo actual que se está evaluando
// - nivel: qué tan lejano es el descendiente (1 = hijo, 2 = nieto, etc.)
// - contador: variable que acumula el número total de descendientes encontrados
void listarDescendientes(Persona* persona, int nivel, int& contador) {
    // Si el nodo está vacío, salimos
    if (persona == NULL) return;

    // Determinar el tipo de relación en función del nivel
    string relacion;
    switch (nivel) {
        case 1: relacion = "Hijo/a"; break;
        case 2: relacion = "Nieto/a"; break;
        case 3: relacion = "Bisnieto/a"; break;
        default:
            // Para niveles mayores, se usa "-Nieto/a", "--Nieto/a", etc.
            relacion = string(nivel - 2, '-') + "Nieto/a";
            break;
    }

    // Mostrar el nombre de la persona y su relación
    cout << "- " << persona->nombre << " (" << relacion << ")\n";

    // Incrementar el contador de descendientes
    contador++;

    // Llamar recursivamente por el hijo izquierdo (si existe)
    listarDescendientes(persona->hijoIzquierdo, nivel + 1, contador);

    // Llamar recursivamente por el hijo derecho (si existe)
    listarDescendientes(persona->hijoDerecho, nivel + 1, contador);
}

// Función principal que permite al usuario ingresar un nombre
// y ver todos los descendientes de esa persona
void mostrarDescendientes() {
    // Verificamos si el árbol está vacío
    if (raiz == NULL) {
        cout << "El árbol está vacío.\n";
        return;
    }

    // Solicitar el nombre de la persona al usuario
    string nombre;
    cout << "Ingrese el nombre de la persona para ver sus descendientes: ";
    getline(cin, nombre);

    // Buscar la persona en el árbol
    Persona* persona = buscarPorNombre(raiz, nombre);

    // Si no se encuentra, informar al usuario
    if (persona == NULL) {
        cout << "Persona no encontrada.\n";
        return;
    }

    // Inicializamos el contador de descendientes
    int contador = 0;

    // Iniciamos la búsqueda de descendientes desde los hijos de esta persona
    listarDescendientes(persona->hijoIzquierdo, 1, contador);
    listarDescendientes(persona->hijoDerecho, 1, contador);

    // Mostrar resultado final
    if (contador == 0) {
        cout << persona->nombre << " no tiene descendientes.\n";
    } else {
        cout << persona->nombre << " tiene " << contador << " descendiente(s).\n";
    }
}


//Main menu , jhul 
int main() {
    int opcion;

    do {
        cout << "\n--- MENU ARBOL BINARIO GENEALOGICO ---\n";
        cout << "1. Crear persona raiz\n";
        cout << "2. Anadir hijo (izquierdo o derecho)\n";
        cout << "3. Buscar persona por nombre\n";
        cout << "4. Eliminar persona (solo si no tiene hijos)\n";
        cout << "5. Buscar en preorden\n";
        cout << "6. Buscar en inorden\n";
        cout << "7. Buscar en postorden\n";
        cout << "8. Eliminar familia completa (rama descendiente)\n";
        cout << "9. Mostrar descendientes de una persona\n";
        cout << "10. Mostrar ancestros de una persona\n";
        cout << "11. Salir\n"; 
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
                cout << "Búsqueda en Preorden:\n";
                buscarPreorden(raiz);
                break;
            case 6:
                cout << "Búsqueda en Inorden:\n";
                buscarInorden(raiz);
                break;
            case 7:
                cout << "Búsqueda en Postorden:\n";
                buscarPostorden(raiz);
                break;
            case 8:
                eliminarFamilia();
                break;
           case 9:
                mostrarDescendientes();
    			      break;
            case 10:
                mostrarAncestros();
                break;
            case 11:
            cout << "Saliendo del programa.\n";
            break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 11);
    
    return 0; 
}


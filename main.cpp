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
int main(){
      Persona* raiz = NULL;
    int opcion;

    do {
        cout << "\n--- MENU ARBOL BINARIO GENEALOGICO ---\n";
        cout << "1. Crear persona raiz\n";
        cout << "2. Anadir hijo (izquierdo o derecho)\n";
        cout << "3. Buscar persona por nombre\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
    switch (opcion){
      case 1:{
        string nombre, fecha;
        cout << "Nombre de la persona raiz: ";
        getline(cin, nombre);
        cout << "Fecha de nacimiento (YYYY-MM-DD): ";
        getline(cin, fecha);
        raiz = crearPersona(nombre, fecha);
        cout << "Raiz creada exitosamente.\n";
        break;
      }
      case 2:{
        if (raiz==NULL){
        cout << "Primera cree la raiz del arbol.\n";
          break;
        }
        string nombrePadre, nombreHijo, fechaHijo, lado;
        cout << "Nombre del padre: ";
        getline(cin, nombrePadre);
        Persona* padre = buscarPorNombre(raiz, nombrePadre);
        if (padre == NULL){
          cout << "No se encontrado a" << nombrePadre << ".\n";
          break;
        }
        cout << "Nombre del hijo: ";
        getline(cin, nombreHijo);
        cout << "Fecha de nacimiento del hijo (YYYY-MM-DD): ";
        getline(cin, fechaHijo);
        cout << "Lado donde agregar al hijo (izquierdo/derecho): ";
        getline(cin, lado);

        Persona* hijo = crearPersona(nombreHijo, fechaHijo);
        anadirHijoBinario(padre, hijo, lado);
        break;
      }
      case 3:{
        string nombre;
        cout << "Nombre a buscar: ";
        getline(cin, nombre);
        Persona* resultado = buscarPorNombre(raiz, nombre);
        if (resultado != NULL) {
            cout << "Persona encontrada: " << resultado->nombre
            << ", nacida el " << resultado->fechaNacimiento << "\n";
        } else {
            cout << "No se encontro a " << nombre << ".\n";
        }
        break;
      }
      case 4: {
        cout << "Saliendo del programa...\n";
        break;
      }
    } while (opcion != 0);
      return 0;
}
//que se hace en esta cosa?

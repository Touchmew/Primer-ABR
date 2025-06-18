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

//que se hace en esta cosa?

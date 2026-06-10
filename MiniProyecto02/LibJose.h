//Materia: Programación I, Paralelo 4
//Grupo: 2
//Autor librería: José Armando Sánchez Velarde
//Fecha creación: 01/06/26
//Encargado de: Opción 1, Opción 3 y Opción 4
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// lista de las funciones que generé con nombres
bool cadenasIguales(const char* cad1, const char* cad2);
void copiarCadena(char* destino, const char* origen);
bool existeEstudiante(const char* ciBuscar);
void adicionarEstudiante();
void reporteConsolidado();
void modificarNota();

struct structEstudiante {
    char ci[10];
    char nombres[30];
    char apellidos[30];
};

struct structNotas {
    char ci[10];
    char materia[30];
    int nota;
};

// Comparación manual de cadenas carácter por carácter
bool cadenasIguales(const char* cad1, const char* cad2) {
    int i = 0;

    while ((cad1[i] != '\0') and (cad2[i] != '\0') and (cad1[i] == cad2[i])) {
        i++;
    }

    return ((cad1[i] == '\0') and (cad2[i] == '\0'));
}

// Copia manual de cadena de un origen a un destino
void copiarCadena(char* destino, const char* origen) {
    int i = 0;

    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }

    destino[i] = '\0';
}

// Validación de existencia de estudiante
bool existeEstudiante(const char* ciBuscar) {
    ifstream archivo;
    archivo.open("Estudiantes.bin", ios::binary);

    if (!archivo.good()) {
        return false;
    }

    structEstudiante est;
    bool encontrado = false;

    while ((archivo.read((char*)&est, sizeof(structEstudiante))) and (!encontrado)) {
        if (cadenasIguales(est.ci, ciBuscar)) {
            encontrado = true;
        }
    }

    archivo.close();
    return encontrado;
}

// 1. ADICIONAR ESTUDIANTE
void adicionarEstudiante() {
    structEstudiante est;
    ofstream archivo;

    cout << "ADICIONAR ESTUDIANTE" << endl;
    cout << "====================" << endl;

    cout << "Ingrese CI: ";
    cin >> est.ci;

    if (existeEstudiante(est.ci)) {
        cout << "Error: El estudiante con este CI ya existe." << endl;
        return;
    }

    cout << "Ingrese Nombres: ";
    cin.ignore();
    cin.getline(est.nombres, 30);

    cout << "Ingrese Apellidos: ";
    cin.getline(est.apellidos, 30);

    archivo.open("Estudiantes.bin", ios::binary | ios::app);
    archivo.write((char*)&est, sizeof(structEstudiante));
    archivo.close();

    cout << "Estudiante registrado de forma correcta." << endl;
}

// 3. REPORTE CONSOLIDADO DE CALIFICACIONES
void reporteConsolidado() {
    ifstream archEst;
    structEstudiante est;

    archEst.open("Estudiantes.bin", ios::binary);

    if (!archEst.good()) {
        cout << "No existen estudiantes registrados en el sistema." << endl;
        return;
    }

    cout << "REPORTE CONSOLIDADO DE NOTAS" << endl;
    cout << "============================" << endl;

    while (archEst.read((char*)&est, sizeof(structEstudiante))) {

        cout << "\nEstudiante: "
             << est.apellidos << ", "
             << est.nombres
             << " [CI: "
             << est.ci
             << "]" << endl;

        cout << "--------------------------------------------" << endl;

        ifstream archNotas;
        structNotas notaReg;
        bool tieneNotas = false;

        archNotas.open("Notas.bin", ios::binary);

        while (archNotas.good() and archNotas.read((char*)&notaReg, sizeof(structNotas))) {

            if (cadenasIguales(notaReg.ci, est.ci)) {
                cout << "\tMateria: "
                     << notaReg.materia
                     << " -> Nota: "
                     << notaReg.nota
                     << endl;

                tieneNotas = true;
            }
        }

        archNotas.close();

        if (!tieneNotas) {
            cout << "\t(No registra calificaciones en el sistema)" << endl;
        }
    }

    archEst.close();
}

// 4. MODIFICACIÓN DE NOTAS
void modificarNota() {
    fstream archivo;
    structNotas notaReg;
    char ciBuscar[10];
    char materiaBuscar[30];
    bool encontrada = false;

    cout << "MODIFICAR NOTA DE ESTUDIANTE" << endl;
    cout << "=============================" << endl;

    cout << "Ingrese CI del estudiante: ";
    cin >> ciBuscar;

    cout << "Ingrese la materia a modificar: ";
    cin.ignore();
    cin.getline(materiaBuscar, 30);

    archivo.open("Notas.bin", ios::in | ios::out | ios::binary);

    if (!archivo.good()) {
        cout << "No existe el archivo de notas." << endl;
        return;
    }

    while ((archivo.read((char*)&notaReg, sizeof(structNotas))) and (!encontrada)) {

        if ((cadenasIguales(notaReg.ci, ciBuscar)) and
            (cadenasIguales(notaReg.materia, materiaBuscar))) {

            cout << "Nota actual: " << notaReg.nota << endl;
            cout << "Ingrese la nueva nota: ";
            cin >> notaReg.nota;

            archivo.seekp(-sizeof(structNotas), ios::cur);
            archivo.write((char*)&notaReg, sizeof(structNotas));

            encontrada = true;
        }
    }

    archivo.close();

    if (encontrada) {
        cout << "La calificación ha sido modificada correctamente." << endl;
    }
    else {
        cout << "Registro de calificación no encontrado en el sistema." << endl;
    }
}
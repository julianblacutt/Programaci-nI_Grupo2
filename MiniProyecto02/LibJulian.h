//Materia: Programación I, Paralelo 4
//Grupo: 2
//Autor librería: Julian Blacutt Troche
//Fecha creación: 01/06/26
//Encargado de: Menú, Opción 2 y Opción 5

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//"Prototipado de funciones"
bool cadIguales(const char* cad1, const char* cad2);
bool tieneRegistrodenotaMateria(const char* ciBuscar, const char* materiaBuscar);
bool exisEstudiante(const char* ciBuscar);
void copiCadena(char* destino, const char* origen);
void RegistrarCalificacion();
void ModificarDatosPersonales();

//Librerias uso universal
bool cadIguales(const char* cad1, const char* cad2) 
{
    int i = 0;
    while (cad1[i] != '\0' && cad2[i] != '\0' && cad1[i] == cad2[i]) {
        i++;
    }
    return cad1[i] == '\0' && cad2[i] == '\0';
}
bool tieneRegistrodenotaMateria(const char* ciBuscar, const char* materiaBuscar)
{
    ifstream archivo;
    archivo.open("Notas.bin", ios::binary);
    structNotas notaRegistrada;
    bool previo=false;
    while (archivo.read((char*)&notaRegistrada, sizeof(structNotas)) && !previo)
    {
        if (cadIguales(notaRegistrada.ci, ciBuscar)&&cadIguales(notaRegistrada.materia, materiaBuscar))
        {
            previo=true;
        }
    }
    archivo.close();
    return previo;
}
bool exisEstudiante(const char* ciBuscar) 
{
    ifstream archivo;
    archivo.open("Estudiantes.bin", ios::binary);
    
    structEstudiante est;
    bool encontrado = false;
    
    while (archivo.read((char*)&est, sizeof(structEstudiante)) && !encontrado) {
        if (cadIguales(est.ci, ciBuscar)) 
        {
            encontrado = true;
        }
    }
    archivo.close();
    return encontrado;
}
void copiCadena(char* destino, const char* origen) 
{
    int i = 0;
    while (origen[i] != '\0') 
    {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}
//Función Opción 2
void RegistrarCalificacion()
{
    structNotas notaRegistrada;
    ofstream archivoEscritura;
    cout<<"2. Registrar Calificación"<<endl;
    cout<<"Ingrese el CI del estudiante: ";
    cin>>notaRegistrada.ci;
    if (!exisEstudiante(notaRegistrada.ci))
    {
        cout<<"Ese CI no se encuentra registrado."<<endl;
        return;
    }
    cin.ignore();
    cout<<"Ingrese materia: ";
    cin.getline(notaRegistrada.materia, 30);
    if (tieneRegistrodenotaMateria(notaRegistrada.ci, notaRegistrada.materia))
    {
        cout<<"El estudiante ya tiene un registro de esta materia."<<endl;
        return;
    }
    cout<<"Ingrese la nota: ";
    cin>>notaRegistrada.nota;
    archivoEscritura.open("Notas.bin",ios::binary|ios::app);
    archivoEscritura.write((char*)&notaRegistrada,sizeof(structNotas));
    archivoEscritura.close();
    cout<<"Calificación registrada exitosamente."<<endl;
}
//Función Opción 5
void ModificarDatosPersonales() 
{
    fstream archivoEstu;
    structEstudiante estudiante;
    char ciBuscar[10];
    bool encontrado = false;
    cout << "5. Modificación de Datos Personales" << endl;
    cout << "Ingrese el CI del estudiante: ";
    cin >> ciBuscar;
    archivoEstu.open("Estudiantes.bin", ios::in | ios::out | ios::binary);

    while (archivoEstu.read((char*)&estudiante, sizeof(structEstudiante)) && !encontrado) 
    {
        if (cadIguales(estudiante.ci, ciBuscar)) 
        {
            structEstudiante estModificado;
            cout << "Ingrese nuevo CI: ";
            cin >> estModificado.ci;
            if (!cadIguales(ciBuscar, estModificado.ci) && exisEstudiante(estModificado.ci)) 
            {
                cout << "El nuevo CI ya está asignado a otro estudiante." << endl;
                archivoEstu.close();
                return;
            }
            cout << "Ingrese los nuevos nombres: ";
            cin.ignore();
            cin.getline(estModificado.nombres, 30);
            cout << "Ingrese los nuevos apellidos: ";
            cin.getline(estModificado.apellidos, 30);

            archivoEstu.seekp(-sizeof(structEstudiante), ios::cur);
            archivoEstu.write((char*)&estModificado, sizeof(structEstudiante));
            encontrado = true;

            if (!cadIguales(ciBuscar, estModificado.ci)) 
            {
                fstream archivoNotas;
                structNotas notaReg;

                archivoNotas.open("Notas.bin", ios::in | ios::out | ios::binary);
                while (archivoNotas.read((char*)&notaReg, sizeof(structNotas))) 
                {
                    if (cadIguales(notaReg.ci, ciBuscar)) 
                    {
                        copiCadena(notaReg.ci, estModificado.ci);
                        archivoNotas.seekp(-sizeof(structNotas), ios::cur);
                        archivoNotas.write((char*)&notaReg, sizeof(structNotas));
                        archivoNotas.seekg(0, ios::cur);
                    }
                }
                archivoNotas.close();
            }
        }
    }
    archivoEstu.close();
    if (encontrado) 
    {
        cout << "Estudiante y registros asociados actualizados con éxito." << endl;
    } 
    else 
    {
        cout << "El estudiante no ha sido encontrado." << endl;
    }
}

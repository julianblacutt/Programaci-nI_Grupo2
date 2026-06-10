//Materia: Programación I, Paralelo 4
//Grupo: 2
//Autores: Julian Blacutt Troche, José Armando Sánchez Velarde
//Fecha creación: 01/06/26
//Nombre del miniproyecto: Ejercicio 1 (Sistema de Registro Académico Consolidado)
#include <iostream>
#include <string>
#include <fstream>
#include "LibJose.h"
#include "LibJulian.h"

using namespace std;

void desplegarMenu(string nombreArchivo);
int main()
{
    system("chcp 65001");
    system("cls");
    string nombreArchivo;
    cout<<"SISTEMA DE REGISTRO ACADÉMICO CONSOLIDADO"<<endl;
    cout<<"========================================="<<endl;
    desplegarMenu(nombreArchivo);
    return 0;
}
void desplegarMenu(string nombreArchivo)
{
    int op=0;
    do
    {
        cout<<"MENÚ DE OPCIONES"<<endl;
        cout<<"1. Adicionar Estudiante"<<endl;
        cout<<"2. Registrar Calificación"<<endl;
        cout<<"3. Reporte Consolidado de Calificaciones"<<endl;
        cout<<"4. Modificación de notas"<<endl;
        cout<<"5. Modificación de Datos Personales"<<endl;
        cout<<"6. Salir del Programa"<<endl;
        cout<<"Ingrese una opción válida por favor: ";
        cin>>op;
        system("cls");
        switch (op)
        {
        case 1:
            cout<<"Usted a eligió: Adicionar Estudiante"<<endl;
            adicionarEstudiante();
            system("pause");
            break;
        case 2:
            cout<<"Usted eligió: Registrar Calificación"<<endl;
            RegistrarCalificacion();
            system("pause");
            break;
        case 3:
            cout<<"Usted eligió: Reporte Consolidado de Calificaciones"<<endl;
            reporteConsolidado();
            system("pause");
            break;
        case 4:
            cout<<"Usted eligió: Modificación de notas"<<endl;
            modificarNota();
            system("pause");
            break;
        case 5:
            cout<<"Usted eligió: Modificación de Datos Personales"<<endl;
            ModificarDatosPersonales();
            system("pause");
            break;
        default:
            if (op<=0||op>6)
            {
                cout<<"Debe ingresar una opción válida."<<endl;
                system("pause");
            }
            break;
        }
    } while (op!=6);
    system("cls");
    cout<<"Usted eligió: Salir del Programa"<<endl;
}
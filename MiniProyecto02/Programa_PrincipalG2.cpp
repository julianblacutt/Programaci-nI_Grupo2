//Materia: Programación I, Paralelo 4
//Grupo: 2
//Autores: Julian Blacutt Troche, José Armando Sánchez Velarde
//Fecha creación: 01/06/26
//Nombre del miniproyecto: Ejercicio 1 (Sistema de Registro Académico Consolidado)
#include <iostream>
#include "LibJulian.h"
#include "LibJose.h"

using namespace std;

void desplegarMenu();
int main()
{
    system("chcp 65001");
    system("cls");
    
    cout<<"SISTEMA DE REGISTRO ACADÉMICO CONSOLIDADO"<<endl;
    cout<<"========================================="<<endl;
    desplegarMenu();
    return 0;
}
void desplegarMenu()
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
            cout<<"Usted a elegido: Adicionar Estudiante"<<endl;
            system("pause");
            break;
        case 2:
            cout<<"Usted a elegido: Registrar Calificación"<<endl;
            system("pause");
            break;
        case 3:
            cout<<"Usted a elegido: Reporte Consolidado de Calificaciones"<<endl;
            system("pause");
            break;
        case 4:
            cout<<"Usted a elegido: Modificación de notas"<<endl;
            system("pause");
            break;
        case 5:
            cout<<"Usted a elegido: Modificación de Datos Personales"<<endl;
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
    cout<<"Usted a elegido: Salir del Programa"<<endl;
}
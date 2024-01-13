// Sergio Eder Cervantes Rincon

#include <iostream>
#include <limits>
#include "lib\paquete.cpp"
#include <windows.h>
using namespace std;

const char* negocio = "assets/infoNeg.txt";
const char* inventario = "assets/inventario.txt";
const char* paquetes = "assets/paquetes.txt";
const char* auxiliar = "assets/auxiliar.txt";
void registrarNuevoPaquete();

int main()
{
    registrarNuevoPaquete();
    return 0;
}

void registrarNuevoPaquete()
{
    ifstream ifile;
    ofstream ofile;
    //sacar el ID siguiente del archivo infoNeg
    ifile.open(negocio);
    ifile.clear();
    ifile.seekg(0);
    if (!ifile)
    {
        cout << endl << "No se pudo abrir el archivo";
        exit(1);
    }    
    ifile.ignore(numeric_limits<streamsize>::max(), '\n');
    int IDprev;
    ifile >> IDprev;
    ifile.close();
    //Capturar todos los datos de el nuevo paquete
    string nombre;
    int numProductos;
    double precio;
    Producto *productos;

    cout << endl << "Dame el nombre del nuevo Paquete: ";
    fflush(stdin);
    getline(cin,nombre);
    fflush(stdin);
    cout << endl << "Dime la cantidad de productos que tendra este paquete: ";
    cin >> numProductos;
    cout << endl << "Dame el precio de compra del paquete: ";
    cin >> precio;

    productos = new Producto[numProductos];
    string nombre2;
    int cant;
    double precioProd;
    for (int i = 0; i < numProductos; i++)
    {
        cout << "Dame el nombre del producto " << i + 1 << ": ";
        fflush(stdin);
        getline(cin,nombre2);
        fflush(stdin);
        productos[i].setNom(nombre2);
        cout << "Dame el numero de este tipo de productos que contiene el paquete: ";
        cin >> cant;
        productos[i].setCant(cant);
        cout << "Dame el precio de compra este producto: ";
        cin >> precioProd;
        productos[i].setPrecioCompra(precioProd);
        cout << "Dame el precio de venta de este producto: ";
        cin >> precioProd;
        productos[i].setPrecioVenta(precioProd);
        
    }

    //crear el nuevo objeto paquete
    Paquete nuevoPaquete(IDprev + 1, nombre, numProductos, precio, productos);
    
    cout << "Este es el nuevo Paquete que quieres ingresar al registro? \nSi la informacion es correcta pulsa 1, si es incorrecta y quiere volver a hacer el registro pulse 2, \nsi quiere cancelar la operacion pulse 3";
    nuevoPaquete.imprimir();
    char opc;
    cin >> opc;
    if (opc == '1')
    {
        nuevoPaquete.guardarEnArch(paquetes);
        //incrementa el numero de paquetes en el archivo de informacion del negocio
        ifile.open(negocio);
        ifile.clear();
        ifile.seekg(0);
        ofile.open(auxiliar);
        getline(ifile,nombre);
        ofile << nombre << endl << IDprev + 1 << endl;
        ifile.close();
        ofile.close();
        system("del assets\\infoNeg.txt");
        system("ren assets\\auxiliar.txt infoNeg.txt");
    }
    if (opc == '2')
        registrarNuevoPaquete();
    if (opc == '3')
        return;

}
#include "paquete.h"
#include "producto.cpp"
#include <iostream>
#include <fstream>

using namespace std;

Paquete ::Paquete () : paquete_id(0), nombre(""), numProductos(0),precioCompra(0), productos(NULL){}

Paquete ::Paquete (int ID, string nom, int num, double pr, Producto* prod) : paquete_id(ID), nombre(nom), numProductos(num),precioCompra(pr), productos(prod){}

void  Paquete ::setNombre(string a)
{
    this->nombre = a;
}

void  Paquete ::setNumProductos(int a)
{
    this->numProductos = a;
}

void  Paquete ::setPrecioCompra(double a)
{
    this->precioCompra = a;
}

void  Paquete ::setProductos(Producto * a)
{
    this->productos = a;
}

string  Paquete ::getNombre()
{
    return this->nombre;
}

int  Paquete ::getNumProductos()
{
    return this->numProductos;
}

double  Paquete ::getPrecioCompra()
{
    return this->precioCompra;
}

Paquete ::~Paquete ()
{
    delete []productos;
}

void Paquete ::imprimir()
{
    cout << endl << "ID del paquete: " << this->paquete_id;
    cout << endl << "Nombre: " << this->nombre;
    cout << endl << "Numero de productos: " << this->numProductos;
    cout << endl << "Precio del paquete: " << this->precioCompra;
    cout << endl << "Productos que lo conforman: ";
    for (int i = 0; i < this->numProductos; i++)
    {
        cout << endl << productos[i].getNombre() << " " << productos[i].getCant() << " $" << productos[i].getPrecioCompra() << " $" << productos[i].getPrecioVenta();
    }
    cout << endl;
}

void Paquete ::guardarEnArch(const char * nomArch) const
{
    ofstream ofile(nomArch, ios::app);
    if (!ofile)
    {
        cout << endl << "No se pudo abrir el archivo";
        exit(1);
    }
    
    ofile << "ID " << this->paquete_id << endl << this->nombre << endl << this->numProductos << " " << this->precioCompra << endl;
    for (int i = 0; i < this->numProductos; i++)
        ofile << productos[i].getNombre() << " " << productos[i].getCant() << " " << productos[i].getPrecioCompra() << " " << productos[i].getPrecioVenta() << endl; 
    ofile << endl;
    ofile.close();
}

void Paquete ::cargarPaquete(const string  ID,const char * paquetes)
{
    //Armamos la linea que se va a buscar en el archivo
    string ID_ABuscar = "ID " + ID, line;
    ifstream ifile(paquetes);
    while(getline(ifile,line))
    {

        if (line == ID_ABuscar) //Evalua si se encontro el paquete, en ese caso se copia todo lo de el
        {
            this->paquete_id = stoi(ID);
            getline(ifile,line);
            this->nombre = line;
            ifile >> this->numProductos >> this->precioCompra;
            string Pnom;
            int Pcant;
            double PpC, PpV;
            productos = new Producto[numProductos];
            for (int i = 0; i < numProductos; i++)
            {
                ifile >> Pnom >> Pcant >> PpC >> PpV;
                this->productos[i].setNom(Pnom);
                this->productos[i].setCant(Pcant);
                this->productos[i].setPrecioCompra(PpC);
                this->productos[i].setPrecioVenta(PpV);
            }
            break;            
        }
    }
    ifile.close();
}

bool validarNom(const Paquete& obj, const string nom)
{

    
}

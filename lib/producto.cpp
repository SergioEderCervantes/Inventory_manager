#include "producto.h"

Producto ::Producto() : nomProd(""), cantidad(0), precioCompra(0.0), precioVenta(0.0) {}

Producto ::Producto(string nom, int cant, double pC, double pV)
{    
    //Reemplazamos los guiones bajos por espacios en blanco
    unsigned int pos = nom.find('_');
    while (pos != string::npos)
    {
        nom.replace(pos, 1, " ");
        pos = nom.find('_', pos + 1);
    }
    
    //Asignamos los valores de los parametros a los atributos del objeto

    nomProd = nom;
    cantidad = cant;
    precioCompra = pC;
    precioVenta = pV;
}

void Producto ::setNom(string a)
{
    this->nomProd = a;
}

void Producto ::setCant(int a)
{
    this->cantidad = a;
}

void Producto ::setPrecioCompra(double a)
{
    this->precioCompra = a;
}

void Producto ::setPrecioVenta(double a)
{
    this->precioVenta = a;
}

string Producto ::getNombre() const
{
    return this->nomProd;
}

int Producto ::getCant() const
{
    return this->cantidad;
}

double Producto ::getPrecioCompra() const
{
    return this->precioCompra;
}

double Producto ::getPrecioVenta() const
{
    return this->precioVenta;
}

string Producto ::procesarCadena() const
{
    string aux = this->nomProd;
    //Reemplazamos los espacios en blanco por guiones bajos 
    unsigned int pos = aux.find(' ');
    while (pos != string::npos)
    {
        aux.replace(pos, 1, "_");
        pos = aux.find('_', pos + 1);
    }
    aux = aux + " " + to_string(this->cantidad) + " " + to_string(this->precioCompra) + " " + to_string(this->precioVenta);
    return aux;
}

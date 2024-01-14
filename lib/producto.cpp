#include "producto.h"

Producto ::Producto() : nomProd(""), cantidad(0), precioCompra(0.0), precioVenta(0.0) {}

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

string Producto ::getNombre()
{
    return this->nomProd;
}

int Producto ::getCant()
{
    return this->cantidad;
}

double Producto ::getPrecioCompra()
{
    return this->precioCompra;
}

double Producto ::getPrecioVenta()
{
    return this->precioVenta;
}

Producto Producto::stringToProducto(string line)
{

    //Simplificar todo esto simplemente mandando como parametro todos los elementos sacados 
    //Campo por campo del archivo, buscar la funcion en string que reemplaze los _
    //Limpiamos todo lo que tenga el objeto
    nomProd = "";
    cantidad = 0;
    precioCompra = precioVenta = 0.0;
    //copiamos los valores de la string en el objeto
    int pos = 0;
    string aux;
    while (line[pos] != ' ')
    {
        if (line[pos] == '_')
        {
            nomProd += ' ';
        }
        else
        {
            nomProd += line[pos];
        }
        pos ++;
    }
    pos++;
    while (line[pos] != ' ')
    {
        aux += line[pos];
        pos++;
    }
    cantidad = stoi(aux);
    pos++;
    aux = "";
    while (line[pos] != ' ')
    {
        aux += line[pos];
        pos++;
    }
    precioCompra = stoi(aux);
    pos++;
    aux = "";

}

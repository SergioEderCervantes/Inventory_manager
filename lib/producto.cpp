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

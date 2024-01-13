#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <string>

using namespace std;
class Producto 
{ 
private: 
    string nomProd;
    int cantidad;
    double precioCompra;
    double precioVenta;
public: 
    Producto(); 
    void setNom(string);
    void setCant(int);
    void setPrecioCompra(double);
    void setPrecioVenta(double);
    string getNombre();
    int getCant();
    double getPrecioCompra();
    double getPrecioVenta();

    ~Producto(){} 
}; 


#endif
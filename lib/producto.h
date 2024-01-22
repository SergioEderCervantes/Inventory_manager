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
    Producto(string,int,double,double); 
    void setNom(string);
    void setCant(int);
    void setPrecioCompra(double);
    void setPrecioVenta(double);
    string getNombre() const;
    int getCant() const;
    double getPrecioCompra() const;
    double getPrecioVenta() const;
    string procesarCadena() const;
    friend string ponerGuiones( string);
    friend string quitarGuiones( string);
    ~Producto(){} 
}; 


#endif
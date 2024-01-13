#ifndef PAQUETE_H
#define PAQUETE_H
#include "producto.h"

class Paquete 
{ 
private: 
    int paquete_id;
    string nombre;
    int numProductos;
    double precioCompra;
    Producto *productos;
public: 
    Paquete(); 
    Paquete(int, string, int, double, Producto*);
    void setNombre(string);
    void setNumProductos(int);
    void setPrecioCompra(double);
    void setProductos(Producto*);
    string getNombre();
    int getNumProductos();
    double getPrecioCompra();
    Producto* getProductos();
    void imprimir();
    void guardarEnArch(char const*) const;
    ~Paquete();
}; 

#endif
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
public: 
    Producto *productos;
    Paquete(); 
    Paquete(int, string, int, double, Producto*);
    void setNombre(string);
    void setNumProductos(int);
    void setPrecioCompra(double);
    void setProductos(Producto*);
    string getNombre();
    int getNumProductos();
    double getPrecioCompra();

    void imprimir();
    void guardarEnArch(const char *) const;
    void cargarPaquete(const string , const char *);
    friend bool validarNom(const Paquete&, const string );
    ~Paquete();
}; 

#endif
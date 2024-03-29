// Sergio Eder Cervantes Rincon

#include <iostream>
#include <limits>
#include <windows.h>
#include <vector>
#include <cctype>
#include <cstring>
#include "lib\paquete.cpp"
using namespace std;

const char* negocio = "assets/infoNeg.txt";
const char* inventario = "assets/inventario.txt";
const char* paquetes = "assets/paquetes.txt";
const char* auxiliar = "assets/auxiliar.txt";

char menu();

//funciones para inventario
void menuInventario();
void mostrarInventario();
vector<Producto> modificarInventarioEntrada(vector<Producto>);
vector<Producto> modificarInventarioSalida(vector<Producto>);
vector<Producto> cargarInventario();
void guardarInventario(vector<Producto>);
void reporteVentas(vector<Producto>);

//Funciones para paquetes
void menuPaquetes();
void registrarNuevoPaquete();
void eliminarPaquete();
void verBaseDePaquetes();

//Main y menu principal
int main()
{
    //Bienvenida
    char opc;

    do
    {
        opc = menu();
        switch (opc)
        {
        case '1':
            menuPaquetes();
            break;
        case '2':
            menuInventario();
            break;
        case '3':
            mostrarInventario();
            break;
        case '0':
            cout << endl << "Vuelva pronto";
            break;
        default:
            cout << endl << "Opcion incorrecta, intente de nuevo";
            break;
        }
    } while (opc != '0');
    
    return 0;
}

char menu()
{
    char opcion;
    cout << "Menu principal:" << endl;
    cout << "1. Modificar base de paquetes" << endl;
    cout << "2. Modificar inventario" << endl;
    cout << "3. Revisar inventario" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    return opcion;
}

//funciones de paquetes
void menuPaquetes()
{
    char opcion;

    do {
        system("cls");
        cout << "\nMenu de paquetes:" << endl;
        cout << "1. Agregar Paquete" << endl;
        cout << "2. Eliminar Paquete" << endl;
        cout << "3. Ver Base de Paquetes" << endl;
        cout << "0. Salir al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                registrarNuevoPaquete();
                break;
            case '2':
                eliminarPaquete();
                break;
            case '3':
                verBaseDePaquetes();
                break;
            case '0':
                cout << "Volviendo al menu principal" << endl;
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
        }
        system("pause");
    } while (opcion != '0');
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

void eliminarPaquete()
{
    int ID;

    cout << endl << "Dime el ID del paquete que deseas eliminar: ";
    cin >> ID;
    ofstream ofile(auxiliar);
    ifstream ifile(paquetes);
    if (!ofile || !ifile)
    {
        cout << endl << "El archivo no se pudo abrir";
        exit(1);
    }
    string line;
    string ID_ABuscar = "ID " + to_string(ID);
    bool band = true;
    while (getline(ifile,line))
    {
        if (line == ID_ABuscar)
            band = false;

        if(band)
            ofile << line << endl;

        if (line.length() == 0)
            band = true;
    }
    ifile.close();
    ofile.close();
    system("del assets\\paquetes.txt");
    system("ren assets\\auxiliar.txt paquetes.txt");
    
}

void verBaseDePaquetes()
{
    ifstream ifile(paquetes);
    string line;

    cout << endl << "Los paquetes disponibles son: ";
    while (getline(ifile,line))
    {
        cout << endl << line;   //Saldran con Guiones, puedes mejorar esto
    }
    ifile.close();
}

//Funciones de inventario
void menuInventario()
{
    char opcion;
    vector<Producto> inventario = cargarInventario();
    // system("pause");
    do {
        system("cls");
        cout << "\nMenu Modificar Inventario:" << endl;
        cout << "1. Modificar Inventario (Entrada)" << endl;
        cout << "2. Modificar Inventario (Salida)" << endl;
        cout << "3. Mostrar Inventario" << endl;
        cout << "0. Salir al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                inventario = modificarInventarioEntrada(inventario);
                break;
            case '2':
                inventario = modificarInventarioSalida(inventario);
                break;
            case '3':
                for (const auto& producto : inventario) {
                    cout << producto.getNombre() << "-" << producto.getCant() << "-" << producto.getPrecioCompra() << "-" << producto.getPrecioVenta() << endl;
                }
                break;
            case '0':
                cout << "Volviendo al menu principal." << endl;
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
        }
        //guardar todos los cambios del inventario a el archivo de texto
        guardarInventario(inventario);
        system("pause");
    } while (opcion != '0');
}
void mostrarInventario()
{
    ifstream ifile(inventario);
    string line;

    cout << endl << "El inventario actual es: ";
    while (getline(ifile,line))
    {
        cout << endl << line;
    }
}

vector<Producto> cargarInventario()
{
    vector<Producto> inv;
    ifstream ifile(inventario);
    ifile.clear();
    ifile.seekg(0);
    string nom;
    int cant;
    double pC, pV;

    while (ifile >> nom >> cant >> pC >> pV)
    {
        Producto aux(nom,cant,pC,pV);
        inv.push_back(aux);
    }
    

    ifile.close();
    return inv;
}

void guardarInventario(vector<Producto> inv)
{
    ofstream ofile(inventario);
    for (const auto& producto : inv)
    {
        string line = producto.procesarCadena();
        ofile << line << endl;
    }
}
vector<Producto> modificarInventarioEntrada(vector<Producto> inventario)
{
    ifstream ifile(paquetes);
    char resp;
    string ID;
    Paquete aux;
    do
    {
        ifile.clear();
        ifile.seekg(0);
        cout << endl << "Estos son los paquetes registrados para ingresar productos al inventario: ";
        verBaseDePaquetes();
        cout << endl << "Dame el ID del paquete que se agregara al inventario \n(Si es un nuevo producto, primero debes de agregar el paquete en la opcion de modificar paquetes)\nID: ";
        cin >> ID;
        aux.cargarPaquete(ID, paquetes);
        if (aux.getNombre() == "")
            cout << endl << "El paquete no se encontro, intente de nuevo";

        //logica para agregar los productos del paquete encontrado en el inventario
        for (int i = 0; i < aux.getNumProductos(); i++)
        {
            bool encontrado = false;
            for (auto& producto : inventario)
            {
                if (aux.productos[i].getNombre() == producto.getNombre())
                {
                    producto.setCant(producto.getCant() + aux.productos[i].getCant());
                    encontrado = true;
                }                
            }
            if (!encontrado) //Si el producto es nuevo, entonces se agrega al inventario como un nuevo producto
            {
                Producto nuevo(aux.productos[i].getNombre(),aux.productos[i].getCant(),aux.productos[i].getPrecioCompra(),aux.productos[i].getPrecioVenta());
                inventario.push_back(nuevo);
            }   
        }
        
        cout << endl << "Si quiere agregar mas productos al inventario, pulse 's', para salir pulse 'n'\n";
        cin >> resp;
        system("cls");
        
    } while (resp != 'n');
    


    return inventario;
}

vector<Producto> modificarInventarioSalida(vector<Producto> pasado) 
{
    //Crea un nuevo vector con el inventario actual y otro con el inventario vendido para el reporte de ventas
    vector<Producto> actual;
    vector<Producto> vendido;
    for(const auto& producto : pasado)
    {
        NOSE:   //Esto no me convence
        cout << endl << "Cuantos " << producto.getNombre() << " restantes hay? (Si no queda ninguno, ingresa 0)";
        string restantes;
        cin >> restantes;
        bool band = true;
        for (char c : restantes)
        {
            if (!isdigit(c))
            {
                band = false;
                break;
            }
        }
        if(!band)
        {
            cout << endl << "El valor ingresado no es valido, intentalo de nuevo";
            goto NOSE;
        }
        else
        {
            int n = stoi(restantes); 
            if (n > producto.getCant()) 
            {
                cout << endl << "El valor ingresado es mayor al que se tenia el registro en el inventario, \nsi es un error intente de nuevo con el valor real o si hubo un ingreso no registrado, es necesario registrarlo en entrada de inventario";
                goto NOSE;
            }
            Producto auxActual(producto.getNombre(),n,producto.getPrecioCompra(),producto.getPrecioVenta());
            Producto auxVendido(producto.getNombre(), producto.getCant()-n, producto.getPrecioCompra(),producto.getPrecioVenta());
            
            vendido.push_back(auxVendido);
            if(n != 0)  //Si quedan 0 existencias del producto, no se incluye al inventario actual
                actual.push_back(auxActual);

        }
    }

    // Resumen de todo lo vendido durante la semana
    char resp;
    do
    {
        cout << endl << "Si quieres ver el resumen de ventas de esta semana, pulsa 1. \nSi quieres salir al menu de inventario, pulsa 2\n";
        cin >> resp;
        if (resp == '1')
        {
            reporteVentas(vendido);
        }
        
    } while (resp != '2' && resp != '1');
    
    return actual;
}

void reporteVentas(vector<Producto> vendido)
{
    cout << endl << "Durante esta semana se vendio: ";
    double total = 0, mult;
    for (const auto& producto : vendido)
    {
        mult = producto.getCant() * producto.getPrecioVenta();
        cout << endl << producto.getCant() << " " << producto.getNombre() << " equivalente a: " << mult;
        total += mult;
    }
    cout << endl << "El total vendido durante la semana fue de: " << total;
}
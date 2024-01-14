// Sergio Eder Cervantes Rincon

#include <iostream>
#include <limits>
#include <windows.h>
#include <vector>
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
// void modificarInventarioEntrada();
// void modificarInventarioSalida();
vector<Producto> cargarInventario();


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
                cout << "Saliendo del programa." << endl;
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
        cout << endl << line;
    }
}

//Funciones de inventario
void menuInventario()
{
    char opcion;
    vector<Producto> inventario = cargarInventario();
    do {
        system("cls");
        cout << "\nMenu Modificar Inventario:" << endl;
        cout << "1. Modificar Inventario (Entrada)" << endl;
        cout << "2. Modificar Inventario (Salida)" << endl;
        cout << "0. Salir al Menu Principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                // modificarInventarioEntrada();
                break;
            case '2':
                // modificarInventarioSalida();
                break;
            case '0':
                cout << "Volviendo al menu principal." << endl;
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
        }
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
    Producto aux;
    ifstream ifile(inventario);
    ifile.clear();
    ifile.seekg(0);
    string line;
    while (getline(ifile,line))
    {
        aux.stringToProducto(line);
        inv.push_back(aux);
    }
    

    ifile.close();
}

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "windows.h"

using namespace std;
void crearArchivos(int cantidad);
void agregarTexto();
int contarArchivosDeDirectorio();
int contarArchivosDeDirectorio2();
void mostrarDetalles();
void mostrarDetalles2();
string generarCadenaAleatoria(int cantidad);
void bitacoraDeRegistro(string mensaje);
void renombrar();

int main() {
    int opc;
    system("chcp 65001");
    cout << "Bienvenido al Programa de Manejo de Archivos" << endl;
    do {
        cout << "------------------------------------------------------------------------" << endl;
        cout << "Elija una opcion a realizar" << endl;
        cout << "[1] Crear Archivos" << endl;
        cout << "[2] Mostrar el peso de los archivos" << endl;
        cout << "[3] Renombrar" << endl;
        cout << "[0] Salir" << endl;
        cin >> opc;
        switch (opc) {
            case 1:
                cout << "Opcion seleccionada -> Crear Archivos" << endl;
                int cantidad;
                cout << "Ingrese la cantidad de archivos que desea crear" << endl;
                cin >> cantidad;
                crearArchivos(cantidad);
                bitacoraDeRegistro("Archivos creados");
                break;
            case 2:
                cout << "Opcion seleccionada -> Mostrar el peso de los archivos" << endl;
                mostrarDetalles();
                mostrarDetalles2();
                break;
            case 3:
                cout << "Opcion seleccionada -> Renombrar archivos" << endl;
                renombrar();
                break;
            case 0:
                cout << "Gracias por Utilizar el Programa" << endl;
                break;
            default:
                cout << "Opcion incorrecta, vuelva a intentarlo" << endl;
                break;
        }
    } while (opc != 0);
    return 0;
}

void crearArchivos(int cantidad){
    string nombreArchivo = "documento";
    if (cantidad % 2 == 0){
        cout << "Cantidad de Archivos par" << endl;
        for (int i = 0; i < cantidad; ++i) {
            ofstream file;
            file.open("C:/Users/admin/OneDrive/Documentos/prueba windows/" + nombreArchivo + to_string(i + 1) + ".txt");
            agregarTexto();
            for (int j = 0; j < i+1; ++j) {
                file << "linea que escribe texto bien epico" << endl;
            }
            file.close();
        }
        cout << cantidad << " Archivos creados con Exito" << endl;
        contarArchivosDeDirectorio();
    }else{
        cout << "Cantidad de Archivos impar" << endl;
        for (int i = 0; i < cantidad; ++i) {
            ofstream file;
            file.open("C:/Users/admin/OneDrive/Desktop/copy/" + nombreArchivo + to_string(i + 1) + ".txt");
            agregarTexto();
            for (int j = 0; j < i+1; ++j) {
                file << "linea de texto" << endl;
            }
            file.close();
        }
        cout << cantidad << " Archivos creados con Exito" << endl;
        contarArchivosDeDirectorio2();
    }
}

void agregarTexto(){
    cout << "Agregando texto..." << endl;
}

int contarArchivosDeDirectorio(){
    WIN32_FIND_DATA findFileData;
    HANDLE          hFind;
    int cantidadDeArchivos=0;
    hFind = FindFirstFile("C:/Users/admin/OneDrive/Documentos/prueba windows/*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE){
        cout << "Ruta incorrecta" << endl;
    }else{
        while (FindNextFile(hFind, &findFileData)!=0){
            cantidadDeArchivos=cantidadDeArchivos+1;
        }
    }
    return cantidadDeArchivos-1;
}

int contarArchivosDeDirectorio2(){
    WIN32_FIND_DATA findFileData;
    HANDLE          hFind;
    int cantidadDeArchivos=0;
    hFind = FindFirstFile("C:/Users/admin/OneDrive/Desktop/copy/*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE){
        cout << "Ruta incorrecta" << endl;
    }else{
        while (FindNextFile(hFind, &findFileData)!=0){
            cantidadDeArchivos=cantidadDeArchivos+1;
        }
    }
    return cantidadDeArchivos-1;
}

void mostrarDetalles(){
    filesystem::directory_iterator directoryIterator("C:/Users/admin/OneDrive/Documentos/prueba windows/");
    cout <<"======================DIRECTORIO========================="<< endl;
    for(const auto& entry: directoryIterator){
        if (!filesystem::is_directory(entry.status())){
            cout<< endl;
            cout << "Tamanio en Bytes: " << file_size(entry.path()) << " bytes" << endl;
            cout << "Nombre de Archivo: " << entry.path().filename() << endl;
        }
    }
}

void mostrarDetalles2(){
    filesystem::directory_iterator directoryIterator("C:/Users/admin/OneDrive/Documentos/prueba windows/");

    cout<< endl <<"======================DIRECTORIO========================="<< endl;
    for(const auto& entry: directoryIterator){
        if (!filesystem::is_directory(entry.status())){
            cout<< endl;
            cout << "Peso: " << file_size(entry.path()) << " bytes" << endl;
            cout << "Nombre de Archivo: " << entry.path().filename() << endl;
        }
    }
    bitacoraDeRegistro("Archivos Leidos");
}
void bitacoraDeRegistro(string mensaje) {
    SYSTEMTIME st;
    GetSystemTime(&st);

    stringstream ss;
    ss << mensaje << endl
       << " Hora actual (UTC): "
       << (st.wHour < 10 ? "0" : "") << st.wHour << ":"
       << (st.wMinute < 10 ? "0" : "") << st.wMinute;

    string horaMensaje = ss.str();  // Convertir a string normal
    MessageBoxA(NULL, horaMensaje.c_str(), "Hora del Sistema", MB_OK | MB_ICONINFORMATION);
}
void renombrar() {
    string rutaPar = "C:/Users/admin/OneDrive/Documentos/prueba windows/";
    string rutaImpar = "C:/Users/admin/OneDrive/Desktop/copy/";
    string nuevoNombre;

    cout << "---- Renombrando archivos en carpeta PAR ----" << endl;
    for (const auto& entry : filesystem::directory_iterator(rutaPar)) {
        if (!filesystem::is_directory(entry.status())) {
            cout << "Archivo encontrado: " << entry.path().filename() << endl;
            cout << "Escribe el nuevo nombre (sin espacios, sin extensión): ";
            cin >> nuevoNombre;
            nuevoNombre += ".txt";
            auto nuevaRuta = entry.path().parent_path() / nuevoNombre;

            try {
                filesystem::rename(entry.path(), nuevaRuta);
                cout << "Renombrado a: " << nuevaRuta.filename() << endl << endl;
            } catch (const exception& e) {
                cerr << "Error al renombrar: " << e.what() << endl;
            }
        }
    }

    cout << "\n---- Renombrando archivos en carpeta IMPAR ----" << endl;
    for (const auto& entry : filesystem::directory_iterator(rutaImpar)) {
        if (!filesystem::is_directory(entry.status())) {
            cout << "Archivo encontrado: " << entry.path().filename() << endl;
            cout << "Escribe el nuevo nombre (no espacios y sin extensión): ";
            cin >> nuevoNombre;
            nuevoNombre += ".txt";
            auto nuevaRuta = entry.path().parent_path() / nuevoNombre;

            try {
                filesystem::rename(entry.path(), nuevaRuta);
                cout << "Renombrado a: " << nuevaRuta.filename() << endl << endl;
            } catch (const exception& e) {
                cerr << "Error al renombrar: " << e.what() << endl;
            }
        }
    }

    bitacoraDeRegistro("Archivos renombrados manualmente");
}// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
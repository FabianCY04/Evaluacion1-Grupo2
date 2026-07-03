#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

struct Estudiante
{
    string nombre;
    string materia;
    string seccion;
    double nota;
};

vector<Estudiante> estudiantes;

void limpiarPantalla()
{
#if defined(_WIN32)
    system("cls");
#else
    system("clear");
#endif
}

string obtenerMateriaPorOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        return "Matematicas";
    case 2:
        return "Programacion";
    case 3:
        return "Fisica";
    case 4:
        return "Base de Datos";
    default:
        return "";
    }
}

string obtenerSeccionPorOpcion(int opcion)
{
    switch (opcion)
    {
    case 1:
        return "1";
    case 2:
        return "2";
    case 3:
        return "3";
    default:
        return "";
    }
}

string elegirMateria()
{
    int opcion;
    while (true)
    {
        cout << "\n=== Materias Disponibles ===\n";
        cout << "1. Matematicas\n";
        cout << "2. Programacion\n";
        cout << "3. Fisica\n";
        cout << "4. Base de Datos\n";
        cout << "Seleccione una materia: ";

        if (cin >> opcion)
        {
            string materia = obtenerMateriaPorOpcion(opcion);
            if (!materia.empty())
                return materia;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Opcion invalida. Intente de nuevo.\n";
    }
}

string elegirSeccion()
{
    int opcion;
    while (true)
    {
        cout << "\n=== Secciones Disponibles ===\n";
        cout << "1. Seccion 1\n";
        cout << "2. Seccion 2\n";
        cout << "3. Seccion 3\n";
        cout << "Seleccione una seccion: ";

        if (cin >> opcion)
        {
            string seccion = obtenerSeccionPorOpcion(opcion);
            if (!seccion.empty())
                return seccion;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Opcion invalida. Intente de nuevo.\n";
    }
}

// NUEVA FUNCIÓN AUXILIAR: Cuenta cuántos alumnos hay en una materia y sección específica
int contarEstudiantesEnSeccion(const string &materia, const string &seccion)
{
    int contador = 0;
    for (const auto &e : estudiantes)
    {
        if (e.materia == materia && e.seccion == seccion)
        {
            contador++;
        }
    }
    return contador;
}

void registrarEstudiante()
{
    string materiaCandidata = elegirMateria();
    string seccionCandidata = elegirSeccion();

    // 1. VALIDACIÓN DE CUPO: Verificar si la sección ya llegó a 30
    int totalInscritos = contarEstudiantesEnSeccion(materiaCandidata, seccionCandidata);
    if (totalInscritos >= 30)
    {
        cout << "\n❌ ERROR: Lo sentimos, la Seccion " << seccionCandidata
             << " de la materia " << materiaCandidata
             << " ya alcanzo el limite maximo de 30 estudiantes.\n";
        return; // Rompe la función y regresa al menú principal sin pedir más datos
    }

    // 2. Si hay cupo, procedemos con el registro normal
    Estudiante e;
    e.materia = materiaCandidata;
    e.seccion = seccionCandidata;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nNombre del estudiante: ";
    getline(cin, e.nombre);

    cout << "Nota (1 al 20): ";
    while (!(cin >> e.nota) || e.nota < 1 || e.nota > 20)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nota invalida. Ingrese una nota valida entre 1 y 20: ";
    }

    estudiantes.push_back(e);
    cout << "\n¡Estudiante registrado con exito! (Cupos ocupados en esta seccion: "
         << totalInscritos + 1 << "/30)\n";
}

void mostrarEstudiantes()
{
    if (estudiantes.empty())
    {
        cout << "\nNo hay estudiantes registrados.\n";
        return;
    }

    cout << "\n=== Lista de Estudiantes ===\n";
    double suma = 0;

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        cout << i + 1 << ". " << estudiantes[i].nombre
             << " | Materia: " << estudiantes[i].materia
             << " | Seccion: " << estudiantes[i].seccion
             << " | Nota: " << estudiantes[i].nota << "\n";
        suma += estudiantes[i].nota;
    }

    cout << "\nPromedio general: " << (suma / estudiantes.size()) << "\n";
}

void mostrarPorMateriaYSeccion()
{
    if (estudiantes.empty())
    {
        cout << "\nNo hay estudiantes registrados.\n";
        return;
    }

    string materiaSeleccionada = elegirMateria();
    string seccionSeleccionada = elegirSeccion();

    double suma = 0;
    int contador = 0;

    cout << "\n=== Estudiantes de " << materiaSeleccionada
         << " - Seccion " << seccionSeleccionada << " ===\n";

    for (const auto &e : estudiantes)
    {
        if (e.materia == materiaSeleccionada && e.seccion == seccionSeleccionada)
        {
            cout << e.nombre << " | Nota: " << e.nota << "\n";
            suma += e.nota;
            contador++;
        }
    }

    if (contador > 0)
    {
        cout << "\nPromedio del grupo filtrado: " << (suma / contador) << "\n";
    }
    else
    {
        cout << "No se encontraron estudiantes en esa materia y seccion.\n";
    }
}

void guardarEnArchivo()
{
    ofstream archivo("calificaciones.txt");

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo para guardar.\n";
        return;
    }

    archivo << "=== Lista de Estudiantes ===\n";
    double suma = 0;

    for (size_t i = 0; i < estudiantes.size(); i++)
    {
        archivo << i + 1 << ". " << estudiantes[i].nombre
                << " | Materia: " << estudiantes[i].materia
                << " | Seccion: " << estudiantes[i].seccion
                << " | Nota: " << estudiantes[i].nota << "\n";
        suma += estudiantes[i].nota;
    }

    if (!estudiantes.empty())
    {
        archivo << "\nPromedio general: " << (suma / estudiantes.size()) << "\n";
    }
    else
    {
        archivo << "\nNo hay estudiantes registrados.\n";
    }

    archivo.close();
    cout << "Datos guardados exitosamente en 'calificaciones.txt'\n";
}

int main()
{
    int opcion;

    do
    {
        limpiarPantalla();

        cout << "=== MENU PRINCIPAL ===\n";
        cout << "1. Registrar estudiante\n";
        cout << "2. Mostrar todos los estudiantes\n";
        cout << "3. Mostrar por materia y seccion\n";
        cout << "4. Guardar en archivo TXT\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0;
        }

        switch (opcion)
        {
        case 1:
            registrarEstudiante();
            break;
        case 2:
            mostrarEstudiantes();
            break;
        case 3:
            mostrarPorMateriaYSeccion();
            break;
        case 4:
            guardarEnArchivo();
            break;
        case 5:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }

        cout << "\nPresione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

    } while (opcion != 5);

    return 0;
}

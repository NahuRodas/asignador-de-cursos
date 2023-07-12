#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void asignarLista();
void asignarIndividual();
void leerCurso();
void buscarEnCurso();
void eliminarAlumno();
void crearCurso();
int verificarTamCurso(char *);

struct Alumno
{
    char legajo[8];
    char nombre[20];
    char apellido[20];
};

int main()
{
    menu();
    system("pause");
    return 0;
}

void menu()
{

    int seleccion;

    printf("%s", "\n***********************************************");
    printf("%s", "\nBIENVENIDO AL SISTEMA ASIGNADOR DE ALUMNOS");
    printf("%s", "\n***********************************************");
    printf("%s", "\n1. Asignar automaticamente una lista de alumnos a los cursos.");
    printf("%s", "\n2. Asignar un alumno a un curso especifico.");
    printf("%s", "\n3. Ver lista de alumnos de un curso.");
    printf("%s", "\n4. Buscar, por legajo, un alumno en un curso.");
    printf("%s", "\n5. Eliminar un alumno de un curso.");
    printf("%s", "\n6. Crear un curso nuevo (solo es posible si hay un minimo de 10 alumnos disponibles).");
    printf("%s", "\n0. Salir.");
    printf("%s", "\n");
    printf("%s", "\nQue accion desea realizar: ");
    scanf("%d", &seleccion);

    switch (seleccion)
    {
        /*     case 1:
                asignarArchivo();
                break; */
    case 2:
        asignarIndividual();
        break;
    case 3:
        leerCurso();
        break;
    case 4:
        buscarEnCurso();
        break;
        /*  case 5:
             eliminarAlumno();
             break;
         case 6:
             crearCurso();
             break; */
    case 0:
        exit;
        break;

    default:
        printf("%s", "Error, por favor ingrese una opcion valida.");
        break;
    }
}

void asignarIndividual()
{
    struct Alumno alumno = {"", "", ""};
    char curso[8] = "";

    printf("%s", "\n***********************************************");
    printf("%s", "\nASIGNAR ALUMNO A UN CURSO");
    printf("%s", "\n***********************************************");
    printf("%s", "\nIngrese los datos del alumno.");
    printf("%s", "\nLegajo: ");
    scanf("%s", alumno.legajo);

    while (strlen(alumno.legajo) != 7)
    {
        printf("%s", "\nError, el legajo debe ser 7 caracteres numericos.");
        printf("%s", "\nLegajo: ");
        scanf("%s", alumno.legajo);
    }

    printf("%s", "Nombre: ");
    scanf("%s", alumno.nombre);
    printf("%s", "Apellido: ");
    scanf("%s", alumno.apellido);
    printf("%s", "\nIngrese codigo del curso al cual desea agregar el alumno.");
    printf("%s", "\nCurso: ");
    scanf("%s", curso);
    strcat(curso, ".txt");

    while (verificarTamCurso(curso) > 40)
    {
        printf("Curso lleno, por favor ingrese otro curso.");
        printf("%s", "\nCurso: ");
        scanf("%s", &curso);
        strcat(curso, ".txt");
    }

    FILE *pCurso = fopen(curso, "a");
    if (pCurso == NULL)
        printf("No se pudo abrir el archivo.\n");

    fprintf(pCurso, alumno.legajo);
    fprintf(pCurso, "-");
    fprintf(pCurso, alumno.nombre);
    fprintf(pCurso, "-");
    fprintf(pCurso, alumno.apellido);
    fprintf(pCurso, "\n");

    fclose(pCurso);
}

int verificarTamCurso(char *curso)
{
    FILE *pCurso = fopen(curso, "r");
    char linea[50];
    int contador = 0;

    if (pCurso == NULL)
        printf("No se pudo abrir el archivo.\n");

    while (fgets(linea, sizeof(linea), pCurso) != NULL)
    {
        contador++;
    }

    fclose(pCurso);

    return contador;
}

void leerCurso()
{
    char curso[8] = "";
    char linea[50];

    printf("%s", "\nIngrese codigo del curso que desea ver.");
    printf("%s", "\nCurso: ");
    scanf("%s", &curso);
    strcat(curso, ".txt");
    FILE *pCurso = fopen(curso, "r");
    while (fgets(linea, sizeof(linea), pCurso) != NULL)
    {
        printf("%s", linea);
    }
    fclose(pCurso);
}

void buscarEnCurso()
{
    char linea[50];
    char legajoEnCurso[8];
    char legajo[8] = "";
    char curso[8] = "";
    printf("\nIngrese el legajo del alumno que desea buscar: ");
    scanf("%s", legajo);
    printf("\nIngrese el curso: ");
    scanf("%s", curso);
    char auxiliar[8] = "";
    strcat(auxiliar, curso);
    strcat(curso, ".txt");

    FILE *pCurso = fopen(curso, "r");

    while (fgets(linea, sizeof(linea), pCurso) != NULL)
    {
        for (int i = 0; i < 8; i++)
        {
            legajoEnCurso[i] = linea[i];
        }
        if (strcmp(legajoEnCurso, legajo))
        {
            printf("\nEl alumno se encuentra en el curso %s", auxiliar);
        }
    }
    fclose(pCurso);
}
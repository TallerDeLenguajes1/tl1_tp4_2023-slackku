#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

void initializeLists(int cantidad, Tarea **pendientes, Tarea **terminadas);
void chargeToDoList(int cantidad, Tarea **pendientes);
void reqDuration(int *duracion);
void askIfDone(int cantidad, Tarea **pendientes, Tarea **terminadas);
int isTareaFinished(int idTarea);
int isRightChar(char *character);
void moveFinishedTarea(int cantidad, Tarea *pendientes, Tarea **terminadas);
void showLists(int cantidad, Tarea **pendientes, Tarea **terminadas);
Tarea *findByIdImpl(int cantidad, Tarea **pendientes, int id);
void BuscaTareaPorPalabra(int cantidad, Tarea **pendientes);
Tarea *findFirstTareaByInput(int cantidad, Tarea **pendientes, char *input);
int isSameInput(Tarea *tarea, char *input);
void BuscaTareaPorId(int cantidad, Tarea **pendientes);
int main()
{
    srand(time(NULL));
    int cTareas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cTareas);
    fflush(stdin);

    Tarea **listaTareasPendientes = (Tarea **)malloc(sizeof(Tarea *) * cTareas);
    Tarea **listaTareasTerminadas = (Tarea **)malloc(sizeof(Tarea *) * cTareas);

    initializeLists(cTareas, listaTareasPendientes, listaTareasTerminadas);
    chargeToDoList(cTareas, listaTareasPendientes);
    askIfDone(cTareas, listaTareasPendientes, listaTareasTerminadas);
    showLists(cTareas, listaTareasPendientes, listaTareasTerminadas);

    printf("|===========================|\n");
    printf("|        BUSCAR TAREA       |\n");
    printf("|===========================|\n");
    printf("--    Busqueda por ID    --\n");
    BuscaTareaPorId(cTareas, listaTareasPendientes);
    printf("--  Busqueda por palabra  --\n");
    BuscaTareaPorPalabra(cTareas, listaTareasPendientes);

    return 0;
}

void initializeLists(int cantidad, Tarea **pendientes, Tarea **terminadas) // Checked
{
    for (int i = 0; i < cantidad; i++) // Inicializa en cada puntero tarea, las tareas, en NULL
    {
        pendientes[i] = NULL;
        terminadas[i] = NULL;
    }
}

void chargeToDoList(int cantidad, Tarea **pendientes) // Checked
{
    fflush(stdin);
    printf("|===========================|\n");
    printf("|---    Cargar Tareas    ---|\n");
    printf("|===========================|\n");

    for (int i = 0; i < cantidad; i++)
    {
        printf("Tarea N: %d\n", i + 1);

        int *duracion = (int *)malloc(sizeof(int));
        char *buffer = malloc(sizeof(char) * 50);

        printf("Ingrese la descripcion: ");
        gets(buffer);
        fflush(stdin);

        pendientes[i] = (Tarea *)malloc(sizeof(Tarea)); // A cada fila del arreglo de arreglo pendientes, le asigno memoria dinamica
        pendientes[i]->TareaID = i + 1;

        pendientes[i]->Descripcion = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(pendientes[i]->Descripcion, buffer);
        free(buffer);
        reqDuration(duracion);

        pendientes[i]->Duracion = *duracion;
        free(duracion);
        printf("---------------------------\n");
    }
}

void reqDuration(int *duracion) // Checked
{
    printf("Ingrese la duracion: "); // Obtencion y control de datos ingresados de duracion
    scanf("%d", duracion);           // Para que cumpla con pertenecer al intervalo [10,100]
    fflush(stdin);
    if (*duracion < 10)
    {
        printf("Error. Duracion menor a la minima. (Min: 10)\n");
        reqDuration(duracion);
    }
    if (*duracion > 100)
    {
        printf("Error. Duracion mayor a la maxima. (Max: 100)\n");
        reqDuration(duracion);
    }
}

void askIfDone(int cantidad, Tarea **pendientes, Tarea **terminadas) // Checked
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("|===========================|\n");
        printf("|---     TAREA N: %2d     ---|\n", pendientes[i]->TareaID);
        printf("|===========================|\n");
        printf("Descripcion: ");
        puts(pendientes[i]->Descripcion);
        printf("Duracion: %d\n", pendientes[i]->Duracion);
        int isFinishedResult;
        isFinishedResult = isTareaFinished(pendientes[i]->TareaID);
        if (isFinishedResult)
        {
            moveFinishedTarea(cantidad, pendientes[i], terminadas);
            pendientes[i] = NULL;
            // Una vez movida la tarea pendiente a terminada, pendiente queda en null
        }
    }
}

int isTareaFinished(int idTarea) // Checked
{
    int result;
    char *buff = (char *)malloc(sizeof(char));
    printf("La tarea N: %d, fue completada? : (y/n)\n", idTarea);
    *buff = getchar();
    fflush(stdin);
    if (!isRightChar(buff))
    {
        printf("El caracter ingresado es incorrecto\n");
        isTareaFinished(idTarea);
    }
    if (*buff == 'y')
    {
        result = 1;
    }

    if (*buff == 'n')
    {
        result = 0;
    }
    free(buff);
    return result;
}

int isRightChar(char *character) // Checked
{
    return ((*character == 'y') || (*character == 'n'));
}

void moveFinishedTarea(int cantidad, Tarea *pendientes, Tarea **terminadas) // Checked
{
    for (int i = 0; i < cantidad; i++)
    {
        if (terminadas[i] == NULL) // Si ese espacio de Terminadas es nulo, lo sobreescribo
        {
            terminadas[i] = (Tarea *)malloc(sizeof(Tarea));
            terminadas[i] = pendientes;
            i = cantidad;
        }
    }
}

void showLists(int cantidad, Tarea **pendientes, Tarea **terminadas) // Checked
{
    for (int i = 0; i < cantidad; i++)
    {
        if (pendientes[i] != NULL)
        {
            printf("|------LISTA PENDIENTES-----|\n");
            printf("|===========================|\n");
            printf("|---     TAREA N: %2d     ---|\n", pendientes[i]->TareaID);
            printf("|===========================|\n");
            printf("Descripcion: %s\n", pendientes[i]->Descripcion);
            printf("Duracion: %d\n", pendientes[i]->Duracion);
        }
    }
    for (int i = 0; i < cantidad; i++)
    {
        if (terminadas[i] != NULL)
        {
            printf("|------LISTA TERMINADAS-----|\n");
            printf("|===========================|\n");
            printf("|---     TAREA N: %2d     ---|\n", terminadas[i]->TareaID);
            printf("|===========================|\n");
            printf("Descripcion: %s\n", terminadas[i]->Descripcion);
            printf("Duracion: %d\n", terminadas[i]->Duracion);
            printf("\n");
        }
    }
}

Tarea *findFirstTareaByInput(int cantidad, Tarea **pendientes, char *input) // Checked
{
    for (int i = 0; i < cantidad; i++)
    {
        if ((pendientes[i] != NULL) && (strstr(pendientes[i]->Descripcion, input)))
        {
            return pendientes[i];
        }
    }
    return NULL;
}

void BuscaTareaPorId(int cantidad, Tarea **pendientes) // Checked
{
    char *input, *buff = (char *)malloc(sizeof(char) * 100);
    Tarea *findedTarea = (Tarea *)malloc(sizeof(Tarea));
    findedTarea = NULL;
    printf("Ingrese la palabra para buscar: ");
    gets(buff);
    fflush(stdin);
    input = (char *)malloc(sizeof(char) * (strlen(buff) + 1)); // strstr detecta los espacios extra dentro del buffer
    strcpy(input, buff);                                       // Terminando en una Segmentation fault.
    free(buff);
    findedTarea = findFirstTareaByInput(cantidad, pendientes, input);
    free(input);
    if (findedTarea != NULL)
    {
        printf("|     LISTA SELECCIONADA    |\n");
        printf("|===========================|\n");
        printf("|---     TAREA N: %2d     ---|\n", findedTarea->TareaID);
        printf("|===========================|\n");
        printf("Descripcion: %s\n", findedTarea->Descripcion);
        printf("Duracion: %d\n", findedTarea->Duracion);
    }
    else
    {
        printf("La palabra ingresada para buscar no pertenece a ninguna tarea pendiente. Intentelo de nuevo.\n");
        BuscaTareaPorId(cantidad, pendientes);
    }
    free(findedTarea);
}

Tarea *findByIdImpl(int cantidad, Tarea **pendientes, int id) // Checked
{
    for (int i = 0; i < cantidad; i++)
    {
        if ((pendientes[i] != NULL) && (pendientes[i]->TareaID == id))
        {
            return pendientes[i];
        }
    }
    return NULL;
}

void BuscaTareaPorPalabra(int cantidad, Tarea **pendientes) // Checked
{
    int num;
    Tarea *findedTarea = (Tarea *)malloc(sizeof(Tarea));
    findedTarea = NULL;
    printf("Ingrese el id de la tarea que quiere buscar: ");
    scanf("%d", &num);
    fflush(stdin);
    findedTarea = findByIdImpl(cantidad, pendientes, num);
    if (findedTarea != NULL)
    {
        printf("|     LISTA SELECCIONADA    |\n");
        printf("|===========================|\n");
        printf("|---     TAREA N: %2d     ---|\n", findedTarea->TareaID);
        printf("|===========================|\n");
        printf("Descripcion: %s\n", findedTarea->Descripcion);
        printf("Duracion: %d\n", findedTarea->Duracion);
    }
    else
    {
        printf("El id de tarea ingresado, no pertenece a ninguna tarea Pendiente. Intentelo de nuevo.\n");
        BuscaTareaPorPalabra(cantidad, pendientes);
    }
    free(findedTarea);
}
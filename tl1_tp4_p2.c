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
struct Tnodo
{
    Tarea tarea;
    struct Tnodo *sig;
};
typedef struct Tnodo Tnodo;

void reqDuration(int *duracion);
void askIfDone(Tnodo *pendientes, Tnodo *terminadas);
int isTareaFinished(int idTarea);
int isRightChar(char *character);
void moveFinishedTarea(Tnodo **pendientes, Tnodo *terminadas);
void showLists(int cantidad, Tarea **pendientes, Tarea **terminadas);
Tarea *findByIdImpl(int cantidad, Tarea **pendientes, int id);
void BuscaTareaPorPalabra(int cantidad, Tarea **pendientes);
Tarea *findFirstTareaByInput(int cantidad, Tarea **pendientes, char *input);
void BuscaTareaPorId(int cantidad, Tarea **pendientes);

Tnodo *createEmptyLits();
Tnodo *createNode(int id);
void insertNodeOnList(Tnodo **start, Tnodo *nodo);
Tarea createTarea(int id);
int main()
{
    srand(time(NULL));
    int cTareas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cTareas);
    fflush(stdin);

    Tnodo *startPendientes = createEmptyLits();
    Tnodo *startTerminadas = createEmptyLits();

    for (int i = 0; i < cTareas; i++)
    {
        Tnodo *nodo = createNode(i);
        insertNodeOnList(&startPendientes, nodo);
    }

    return 0;
}

Tnodo *createEmptyLits() // Checked
{
    return NULL;
}

Tnodo *createNode(int id) // Checked
{
    Tnodo *nodo = (Tnodo *)malloc(sizeof(Tnodo));
    Tarea tarea = createTarea(id);
    nodo->tarea = tarea;
    nodo->sig = NULL;
    return nodo;
}

void insertNodeOnList(Tnodo **start, Tnodo *nodo) // Checked
{
    nodo->sig = *start;
    *start = nodo;
}

Tarea createTarea(int id) // Checked
{
    Tarea tarea;
    char *buffer = malloc(sizeof(char) * 50);
    int *duracion = (int *)malloc(sizeof(int));
    fflush(stdin);
    printf("|===========================|\n");
    printf("|---    Cargar Tareas    ---|\n");
    printf("|===========================|\n");
    tarea.TareaID = id + 1;
    printf("Tarea N: %d\n", tarea.TareaID);
    printf("Ingrese la descripcion: ");
    gets(buffer);
    tarea.Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(tarea.Descripcion, buffer);
    fflush(stdin);
    reqDuration(duracion);

    printf("---------------------------\n");
    free(buffer);
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

void askIfDone(Tnodo *pendientes, Tnodo *terminadas) // Checked
{
    Tnodo *aux = pendientes;
    while (aux)
    {
        printf("|===========================|\n");
        printf("|---     TAREA N: %2d     ---|\n", pendientes->tarea.TareaID);
        printf("|===========================|\n");
        printf("Descripcion: ");
        puts(pendientes->tarea.Descripcion);
        printf("Duracion: %d\n", pendientes->tarea.Duracion);
        int isFinishedResult;
        isFinishedResult = isTareaFinished(pendientes->tarea.TareaID);
        if (isFinishedResult)
        {
            moveFinishedTarea(pendientes, terminadas);
        }
        aux->sig = aux;
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

void moveFinishedTarea(Tnodo **pendientes, Tnodo *terminadas) // Checked
{

    while (*pendientes)
    {
        if (terminadas->sig == NULL) // Si ese espacio de Terminadas es nulo, lo sobreescribo
        {
        }
        *(pendientes)->sig = *pendientes;
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
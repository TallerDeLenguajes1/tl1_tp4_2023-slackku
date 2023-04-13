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

void chargeToDoList(int cantidad, Tarea **pendientes);
void reqDuration(int *duracion);
void showAskDone(int cantidad, Tarea **pendientes, Tarea **terminadas);
int isTareaFinished(int idTarea);
int isRightChar(char *character);
void askIfCompleted(char *character, int idTarea);
void moveFinishedTarea(int cantidad, Tarea *pendientes, Tarea **terminadas);
void retireFromPendientes(int cantidad, int id, Tarea **pendientes);
int main()
{
    srand(time(NULL));
    int cTareas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cTareas);

    Tarea **listaTareasPendientes = (Tarea **)malloc(sizeof(Tarea *) * cTareas);
    Tarea **listaTareasTerminadas = (Tarea **)malloc(sizeof(Tarea *) * cTareas);

    for (int i = 0; i < cTareas; i++)
    {
        listaTareasPendientes[i] = (Tarea *)malloc(sizeof(Tarea));
        listaTareasTerminadas[i] = (Tarea *)malloc(sizeof(Tarea));
    }

    // for (int i = 0; i < cTareas; i++)
    // {
    //     listaTareasPendientes[i] = NULL;
    //     listaTareasTerminadas[i] = NULL;
    // }

    chargeToDoList(cTareas, listaTareasPendientes);

    showAskDone(cTareas, listaTareasPendientes, listaTareasTerminadas);

    return 0;
}

void chargeToDoList(int cantidad, Tarea **pendientes)
{
    printf("|===========================|\n");
    printf("|---    Cargar Tareas    ---|\n");
    printf("|===========================|\n");

    for (int i = 0; i < cantidad; i++)
    {
        printf("Tarea N: %d\n", i + 1);
        int *duracion;
        char *buffer = malloc(sizeof(char) * 50);
        printf("Ingrese la descripcion: ");
        gets(buffer);
        fflush(stdin);

        pendientes[i]->TareaID = i + 1;
        pendientes[i]->Descripcion = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(pendientes[i]->Descripcion, buffer);

        reqDuration(duracion);
        pendientes[i]->Duracion = *duracion;
    }
}

void reqDuration(int *duracion)
{
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", duracion);
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

void showAskDone(int cantidad, Tarea **pendientes, Tarea **terminadas)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("|===========================|\n");
        printf("|---     TAREA N: %d     ---|\n", pendientes[i]->TareaID);
        printf("|===========================|\n");
        printf("Descripcion: ");
        puts(pendientes[i]->Descripcion);
        printf("Duracion: %d\n", pendientes[i]->Duracion);

        if (isTareaFinished(pendientes[i]->TareaID))
        {
            moveFinishedTarea(cantidad, pendientes[i], terminadas);
            retireFromPendientes(cantidad, pendientes[i]->TareaID, pendientes);
        }
    }
}

int isTareaFinished(int idTarea)
{
    int result;
    char *buff;
    askIfCompleted(buff, idTarea);
    if (!isRightChar(buff))
    {
        askIfCompleted(buff, idTarea);
    }
    if (*buff == 'y')
    {
        return 1;
    }
    if (*buff == 'n')
    {
        return 0;
    }
}

int isRightChar(char *character)
{
    return ((*character == 'y') || (*character == 'n'));
}

void askIfCompleted(char *character, int idTarea)
{
    printf("La tarea N: %d, fue completada? : (y/n)\n");
    *character = getchar();
}

void moveFinishedTarea(int cantidad, Tarea *pendientes, Tarea **terminadas)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (terminadas[i] != NULL)
        {
            terminadas[i] = pendientes;
            i = cantidad;
        }
    }
}

void retireFromPendientes(int cantidad, int id, Tarea **pendientes)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (pendientes[i]->TareaID == id)
        {
            pendientes[i] = NULL;
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define LONGDESCRIPCION 100
struct
{
    int tareaID;       // Numérico autoincremental comenzando en 1000
    char *descripcion; //
    int duracion;      // entre 10 – 100
} typedef Tarea;

typedef struct Nodo Nodo;
struct Nodo
{
    Tarea toDo;
    Nodo *siguiente;
} typedef Nodo;

Nodo* crearListaVacia();
Tarea crearTarea(int id);
Nodo* crearNodo(Tarea tareaDelNodo);
void insertarNodo(Nodo **pDobleTareas, Nodo *pNodo);
void eliminarNodo(Nodo **pDobleTareas, int idTarea);
Nodo* quitarNodo(Nodo **pDobleTareas, int idTarea);
Nodo* buscarTarea(Nodo **pDobleTareas, int id); //me devuelve el nodo que tiene esa tarea buscada
void mostrarLista(Nodo **pDobleTareas);

// void insertarAlFinal(Nodo **pDobleTareas, Nodo *pNodo);

int main()
{
    srand(time(NULL));
    Nodo *tareasPendientes = crearListaVacia();
    Nodo *tareasRealizadas = crearListaVacia();
    printf("---------------MOSTRAR LISTA TAREAS PENDIENTES---------------\n");
    mostrarLista(&tareasPendientes);
    printf("---------------MOSTRAR LISTA TAREAS REALIZADAS---------------\n");
    mostrarLista(&tareasRealizadas);

    printf("---------------INSERTAR TAREA---------------\n");
    int cantidadTotalTareas;
    int id = 1000;
    int seguir = 1;
    bool continuar = false;

    do
    {
        Tarea tareaNueva = crearTarea(id);
        Nodo *nuevoNodo = crearNodo(tareaNueva);
        insertarNodo(&tareasPendientes,nuevoNodo);
        id++;
        printf("Desea seguir agregando tareas? Ingrese 0 para continuar o 1 para salir:");
        scanf("%d", &seguir);
        if(seguir == 0){
            continuar = true;
        }else{
            continuar = false;
        }
    } while (continuar);

    printf("---------------MOVER TAREA---------------\n");
    printf("---------------MOSTRAR LISTA TAREAS PENDIENTES---------------\n");
    mostrarLista(&tareasPendientes);
    printf("---------------MOSTRAR LISTA TAREAS REALIZADAS---------------\n");
    mostrarLista(&tareasRealizadas);

    bool continuar2 = false;
    int seguir2= 1;
    do
    {
        printf("Ingrese el ID de la tarea que desea mover de PENDIENTE  a REALIZADA:");
        int id;
        fflush(stdin);
        scanf("%d", &id);

        Nodo *nodoMovido = quitarNodo(&tareasPendientes,id);
        eliminarNodo(&tareasPendientes,id);
        // insertarNodo(&tareasRealizadas,nodoMovido);

        printf("---------------MOSTRAR LISTA TAREAS PENDIENTES---------------\n");
        mostrarLista(&tareasPendientes);
        printf("---------------MOSTRAR LISTA TAREAS REALIZADAS---------------\n");
        mostrarLista(&tareasRealizadas);

        printf("Desea seguir moviendo tareas PENDIENTES a REALIZADAS? Ingrese 0 para continuar o 1 para salir:");
        scanf("%d", &seguir2);
        if(seguir2 == 0){
            continuar2 = true;
        }else{
            continuar2 = false;
        }
    } while (continuar2);

    //Libero memoria
    while(tareasPendientes!=NULL){
        free(tareasPendientes->toDo.descripcion);
        tareasPendientes = tareasPendientes->siguiente;
    }
    while(tareasRealizadas!=NULL){
        free(tareasRealizadas->toDo.descripcion);
        tareasRealizadas = tareasRealizadas->siguiente;
    }

    free(tareasPendientes);
    free(tareasRealizadas);
    return 0;
}

Nodo* crearListaVacia(){
    return NULL;
}
Tarea crearTarea(int id){
    Tarea nuevaTarea;
    nuevaTarea.tareaID = id;
    nuevaTarea.duracion = rand()%91+10;

    char *descripcionIngresada;
    descripcionIngresada = (char *) malloc(LONGDESCRIPCION*sizeof(char));
    fflush(stdin);
    printf("Ingrese una descripcion de la tarea:");
    gets(descripcionIngresada);

    nuevaTarea.descripcion = (char*)malloc( (strlen(descripcionIngresada) +1)*sizeof(char));
    strcpy(nuevaTarea.descripcion,descripcionIngresada);

    free(descripcionIngresada);
    return nuevaTarea;
}

Nodo* crearNodo(Tarea tareaDelNodo){
    Nodo *nodoCreado;

    nodoCreado = (Nodo *)malloc(sizeof(Nodo));
    nodoCreado->toDo = tareaDelNodo;
    nodoCreado->siguiente = NULL;

    return nodoCreado;
}

void insertarNodo(Nodo **pDobleTareas, Nodo *pNodo){
    Nodo *aux = *pDobleTareas;

    *pDobleTareas = pNodo;
    pNodo->siguiente = aux;
}

void eliminarNodo(Nodo **pDobleTareas,int idTarea){ //
    Nodo *aux = *pDobleTareas;
    Nodo *anterior = *pDobleTareas;
    Nodo *nodoEliminado= NULL;

    if(aux!=NULL){
        if((aux)->toDo.tareaID == idTarea){
            *pDobleTareas = (aux)->siguiente; //hago que la cabecera apunte al nodo 2.
            nodoEliminado = aux;
            free(nodoEliminado);
        }else{
            while ( (aux)!=NULL && (aux)->toDo.tareaID != idTarea){
                anterior = aux;
                aux = aux->siguiente;
            }

            if((aux)!= NULL){ //si el puntero AUX tiene algo., contiene el p al nodo que quero quitar
                printf("Quitando nodo...\n");
                Nodo *proximo = aux->siguiente;
                anterior->siguiente = proximo;
                nodoEliminado= aux;
                free(nodoEliminado);
            }
        }
    }else{
        puts("ERROR. LA LISTA ESTÁ VACIA.");
    }
}

Nodo* quitarNodo(Nodo **pDobleTareas,int idTarea){ //
    Nodo *aux = *pDobleTareas;
    Nodo *anterior = *pDobleTareas;
    Nodo *nodoQuitado= NULL;

    if(aux!=NULL){
        if((aux)->toDo.tareaID == idTarea){
            *pDobleTareas = (aux)->siguiente; //hago que la cabecera apunte al nodo 2.
            nodoQuitado = aux;
        }else{
            while ( (aux)!=NULL && (aux)->toDo.tareaID != idTarea){
                anterior = aux;
                aux = aux->siguiente;
            }

            if((aux)!= NULL){ //si el puntero AUX tiene algo., contiene el p al nodo que quero quitar
                printf("Quitando nodo...\n");
                Nodo *proximo = aux->siguiente;
                anterior->siguiente = proximo;
                nodoQuitado= aux;
                nodoQuitado->siguiente = NULL;
            }
        }
    }else{
        puts("ERROR. LA LISTA ESTÁ VACIA.");
    }

    return nodoQuitado;
}

Nodo* buscarTarea(Nodo **pDobleTareas, int id){
    Nodo **aux = pDobleTareas;
    Nodo **anterior = pDobleTareas;
    Nodo *nodoContenedor= NULL; //nodo que contiene a la tea que quiero buscar

    if((*aux)!= NULL && (*aux)->toDo.tareaID == id){
        pDobleTareas = &(*pDobleTareas)->siguiente; //hago que la cabecera apunte al nodo 2.
        nodoContenedor = *aux;
    }else{
        while ( (*aux)!=NULL && (*aux)->toDo.tareaID != id){
            *anterior = *aux;
            aux = &(*aux)->siguiente;
        }
    }

    if((*aux)!= NULL){ //si el puntero AUX tiene algo., contiene el p al nodo que quero quitar
        printf("Encontramos el nodo que conteiene a la tarea...\n");
        nodoContenedor= *aux;
    }

    return nodoContenedor;
}

void mostrarLista(Nodo **pDobleTareasPend){
    printf("---------------LISTA---------------\n");
    Nodo **aux = pDobleTareasPend;
    int i = 0;
    if( (*aux)== NULL){
        printf("La lista está vacía.\n");
        return;
    }else{
        while((*aux) != NULL){
            Nodo *nodoActual = *aux;
            printf("---->Nodo [%d]: \n", i);
            printf("-Tarea ID: %d \n", nodoActual->toDo.tareaID);
            printf("-Tarea duracion: %d \n", nodoActual->toDo.duracion);
            printf("-Tarea descripcion: %s \n", nodoActual->toDo.descripcion);

            aux = &(*aux)->siguiente;
            i++;
        }
    }
}


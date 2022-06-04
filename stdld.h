#ifndef STDLD_H_INCLUDED
#define STDLD_H_INCLUDED
#define MAX 5

typedef struct informacao
{
    float ctrlpoints[9][3];
    float vetColorCurve[3], vetColorPoint[3];
    short ID, l;
}info;

typedef struct elementos elem;
typedef struct noDiscritor lista;

bool criaLista( lista** );
bool criaNo( elem**, info );
bool liberaLista( lista* );

bool listaVazia( lista* );
bool listaCheia( lista* );
short listaTamanho( lista* );

bool insereListaInicio( lista*, info );
bool insereListaMeio( lista*, info );
bool insereListaFinal( lista*, info );

bool removeInicio( lista* );
bool removeMeio( lista*, short );
bool removeFinal( lista* );

bool consultaListaPos( lista*, unsigned long, info* );

#endif

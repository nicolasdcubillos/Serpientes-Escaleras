#ifndef PROYECTONDCC_H
#define PROYECTONDCC_H
#include "proyectondcc.cpp"

/*	 
								NICOLÁS DAVID CUBILLOS CUBILLOS
								  PROGRAMACIÓN DE COMPUTADORES
								PONTIFICIA UNIVERSIDAD JAVERIANA
									  NOVIEMBRE 15 DE 2020
									  	SEGUNDA ENTREGA
*/

using namespace std;

int* configuracion(int*);
template <typename T>
void jugar(int, Tablero <T>*, Player*, int*);
int menu(int*, Player*);
void nuevaCasilla (Tablero <Casilla*> *, int);
template <typename T>
void nueva_escalera(Tablero<T> *, int, int, int*);
template <typename T>
void nueva_serpiente(Tablero<T> *, int, int, int*);
Casilla* puntero(Tablero <Casilla*> *, int);
void restaurarConfig();
void top();
template <typename T>
Tablero <T> * _crearTablero();
void _ganador(int, Player*);
template <typename T>
Tablero <T> *_inicializarTablero (Tablero<T> *, int*);
int* _leerConfig();
bool _preguntar(stack <char*>&, stack <char*>&, int, Player*, char);
template <typename T>
void _tablero(Tablero <T> *, int, int, int, Player*);
bool _verPreguntas(stack <char*>&, stack <char*>&);

#endif

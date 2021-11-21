#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <stack>
#include "proyectondcc.h"

/*	 
								NICOL�S DAVID CUBILLOS CUBILLOS
								  PROGRAMACI�N DE COMPUTADORES
								PONTIFICIA UNIVERSIDAD JAVERIANA
									  NOVIEMBRE 15 DE 2020
									  	SEGUNDA ENTREGA
			  	
			En esta segunda entrega se implementa el concepto de Lista y sus funciones.
		 Trabaja mediante una lista sencilla encadenada, en donde los Nodos tienen un �nico
	apuntador al siguiente Nodo y en la informaci�n de cada uno se encuentra la casilla del tablero
	
*/

using namespace std;

int main( ) 
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15); // Asigna un color m�s n�tido a la letra = 15 en vez de 07
	
	int nplayers;
	int* config = new int [4];
	config = _leerConfig();
	
	/*
		El vector-pointer config, hace referencia la configuraci�n del juego de la siguiente manera:
		Posici�n 0: N�mero total de casillas del juego.
		Posici�n 1: N�mero de casillas por l�nea.
		Posici�n 2: Bool de Encarcelamiento por triple 6.
		Posici�n 3: Bool de Juego con preguntas (es -1 si hay problemas con los archivos).
	*/
	
	Player* players;
	Tablero <Casilla*> * tablero = _crearTablero<Casilla*>();
	nplayers = menu(config, players);
	jugar(nplayers, tablero, players, config);
	
	delete[] config;
	delete[] players;
	delete[] tablero;
}

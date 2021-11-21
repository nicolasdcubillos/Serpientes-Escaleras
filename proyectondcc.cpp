#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <stack>

/*	 
								NICOLÁS DAVID CUBILLOS CUBILLOS
								  PROGRAMACIÓN DE COMPUTADORES
								PONTIFICIA UNIVERSIDAD JAVERIANA
									  NOVIEMBRE 15 DE 2020
									  	SEGUNDA ENTREGA
	
*/

using namespace std;

int G_ID = 1; 

/*  
	Uso de UNA ÚNICA variable global, se usa en las funciones de nueva_escalera y nueva_serpiente.
	Esto para evitar hacer el envío de la variable mediante las diferentes funciones	
*/

struct Casilla {
	char* type = new char [2];
	Casilla* ptr = NULL; // Apuntador a otra casilla en caso de que sea la parte inicial de una escalera/serpiente
	int id = 0;
	int num = -1;
};

struct Player {
	char* nombre = new char [15];
	Casilla* posicion = NULL;
	int registro_dados = 0;
	int num_posicion = 0;
	bool encarcelado;
};

template<typename T>
struct Nodo
{
       Nodo <T> * sig;
       T info;     
};

template<typename T>
struct Tablero
{
       Nodo <T> * inicio;
       int tam;
};

template <typename T>
void _tablero(Tablero <T> * tablero, int totalcasillas, int linea, int nplayers, Player* players)
{	
	int doblarvec = totalcasillas/linea; // Veces en las que se dobla el vector tablero
	int pos = totalcasillas;
	
	char** color = new char* [4]; // Color para aplicarle a cada jugador.
	for (int i=0; i<4; i++)
		*(color+i) = new char [2];
	
	bool encontrado = 0;
	bool texto = 0;
	bool texto_e = 0;
	
	strcpy(*(color), "04"); // Colores de los jugadores por consola
	strcpy(*(color+1), "09");
	strcpy(*(color+2), "03");
	strcpy(*(color+3), "05");
	
	// Asignación de la propiedad de los colores a la consola
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << endl;
	for (int doblar=0; doblar<doblarvec; doblar++)
	{
		encontrado = false;
		
		// Impresión de cada casilla
		
		cout << "\t\t  ";
		for (int i=0; i<linea; i++)
		{
			for (int h=0; h<10; h++)
				cout << "_";
			cout << " ";
		}
		cout << "\n\t\t |";
		/* 
			Para saber en donde doblar el vector y hacer la impresion correcta del orden de las casillas,
			se hace por pares/impares (doblar%2)
		*/
		
		if (doblar%2==0)
		{
			pos--;
			for (int i=0; i<linea; i++)
			{
				encontrado = false;
				for (int j=0; j<nplayers; j++)
				{
					if ((players+j)->posicion == puntero(tablero, pos-i))
					{
						SetConsoleTextAttribute(hConsole, atoi(*(color+j))); // Se aplica el color a la consola únicamente para "P" y la variable J.
						cout << "P" << j;
						SetConsoleTextAttribute(hConsole, 15); // Se restablece el color a negro con letra blanca brillante.
						encontrado = 1;
						break;
					}
				}
				if (!encontrado) 
					cout << "  ";
				if ((pos-i) < 10)
					cout << " ";
				cout << "      " << pos-i << "|";
			}
			cout << endl << "\t\t |";
			for (int i=0; i<linea; i++)
			{
				cout << "    ";
				if (pos-i != 0)
				{
					if (strcmp((puntero(tablero, pos-i))->type,"AA") != 0 && pos-i != 0)
						cout << (puntero(tablero, pos-i))->type << (puntero(tablero, pos-i))->id;
					else cout << "   ";
				}
				else cout << "   ";
				cout << "   |";
			}
			pos=pos-linea+1;
		}
		else
		{
			pos=pos-linea;
			for (int i=0; i<linea; i++)
			{
				encontrado = false;
				for (int j=0; j<nplayers; j++)
				{
					if ((players+j)->posicion == puntero(tablero, pos+i))
					{
						SetConsoleTextAttribute(hConsole, atoi(*(color+j)));
						cout << "P" << j;
						SetConsoleTextAttribute(hConsole, 15);
						encontrado = 1;
						break;
					}
				}
				if (!encontrado)
					cout << "  ";
				if ((pos+i) < 10)
					cout << " ";
				cout << "      " << pos+i << "|";
			}
			cout << endl << "\t\t |";
			for (int i=0; i<linea; i++)
			{
				cout << "    ";
				if (pos+i != 0)
				{
					if (strcmp((puntero(tablero,pos+i))->type,"AA") != 0)
						cout << (puntero(tablero, pos+i))->type << (puntero(tablero, pos+i))->id;
					else cout << "   ";
				}
				else cout << "   ";
				cout << "   |";
				}
			}
		cout << endl << "\t\t |";
		for (int i=0; i<linea; i++)
		{
			for (int h=0; h<10; h++)
				cout << "_";
			cout << "|";
		}	
		cout << endl;
		/* 
			Se imprime la flecha que indica por donde continúa el tablero.
			Esta flecha no es adaptable, sólo se ubica de forma correcta cuando el tablero tiene el Total de Casillas
			predeterminado (54). 
			
			Si el usuario cambia el número de casillas, la flecha derecha no imprime en el lugar correcto.
		*/
		if (doblar%2 == 0)
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t       ^\n\t\t\t\t\t\t\t\t\t\t\t\t\t       |"<< endl;
		else cout << "\t\t       ^\n\t\t       |" << endl;
	}
	for (int i=0; i<nplayers; i++)
	{
		if ((players+i)->posicion == NULL)
		{
			if ((players+i)->encarcelado)
			{
				if (!texto_e)
				{
					cout << "\t\t\t\t\t      Jugadores en carcel: ";
					texto_e = true;
				}
				cout << "P" << i;
				if (texto_e) 
					cout << " - ";
			}
			else
			{
				if (!texto)
				{
					cout << "\t\t\t\t\t      Jugadores en salida: ";
					texto = true;
				}
				cout << "P" << i;
				if (i!=nplayers-1 && texto)
					cout << " - ";
			}
		}
		
	}
	cout << endl;
	
	for (int i=0; i<4; i++)
		delete[] *(color+i);
		
	delete[] color;
}
	
void top()
{
	cout << "\t\t\t\t\t\t  ------ Serpientes y Escaleras ------" << endl;
	cout << "\t\t\t\t\t\t  Elaborado por Nicol" << char(160) << "s David Cubillos" << endl;
	cout << "\t\t\t\t\t\t    Pontificia Universidad Javeriana" << endl;
	cout << "\t\t\t\t\t\t      Programaci" << char(162) << "n de Computadores" << endl;	
	cout << "\t\t\t\t\t\t";
}

void restaurarConfig()
{
	ofstream Nuevo ("config.txt", ios::out);
	Nuevo << "54" << endl;
	Nuevo << "9" << endl;
	Nuevo << "1" << endl;
	Nuevo << "1";
	Nuevo.close();
}

/*
	(void) Crea el archivo "config.txt" con la configuración predeterminada del juego.
*/
	
int* configuracion(int* config)
{
	char* opcion = new char [1];
	char* temp = new char [1];
	int ascii;
	bool salir = 0, valido = 0;
	while (!salir)
	{
		system("Cls");
		top();
		cout << "\n\t\t\t\t\t\t\tConfiguraci" << char(162) << "n del tablero" << endl;
		cout << "\n\t\t\t[A] Numero total de casillas: " << *(config);
		cout << "\n\t\t\t[B] Numero de casillas por fila: " << *(config+1);
		cout << "\n\t\t\t[C] Encarcelar por triple 6: ";
		
		if (*(config+2) == 1)
			cout << "Activado";
		else 
			cout << "Desactivado";
			
		cout << "\n\t\t\t[D] Juego con preguntas: ";
		if (*(config+3) == 1)
			cout << "Activado";
		else if (*(config+3) == 0)
			cout << "Desactivado";
		else 
			cout << "Problema con archivos";
			
		cout << "\n\t\t\t[P] Restaurar a configuracion pretederminada." << endl;
		cout << "\n\t\tIngrese la opcion que desea cambiar o 'Z' para salir y guardar: ";
		
		cin >> opcion;
		strupr(opcion);
		ascii = int(*(opcion));
		switch (ascii)
		{
			case 65:
				{
					cout << "\t\t\t\tEscriba el nuevo total de casillas: ";
					cin >> *(config);
					cout << "\t\t\t\tAl cambiar el numero de casillas debe cambiar el numero de filas." << endl;
				}
			case 66:
				{
					valido = false;
					while (!valido)
					{
						cout << "\t\t[!] El n" << char (163) << "mero debe ser m" << char(163) << "ltiplo del total de casillas." << endl;
						cout << "\t\t\t\tEscriba el nuevo numero de casillas por fila: ";
						cin >> temp;
						if (*(config) % atoi(temp) == 0)
						{
							valido = true;
							*(config+1) = atoi(temp);
						}
					}
					break;
				}
			case 67:
				{
					if (*(config+2) == 1)
						*(config+2) = 0;
					else *(config+2) = 1;
					break;
				}
			case 68:
				{
					if (*(config+3) == 1)
						*(config+3) = 0;
					else if (*(config+3) == 0)
						*(config+3) = 1;
					break;
				}
			case 90:
				{
					ofstream Salida ("config.txt", ios::out);
					Salida << *(config) << endl;
					Salida << *(config+1) << endl;
					Salida << *(config+2) << endl;
					Salida << *(config+3);
					Salida.close();
					salir = true;
					break;
				}
			case 80:
				{
					restaurarConfig();
					*(config) = 54;
					*(config+1) = 9;
					*(config+2) = 1;
					break;
				}
			default: system ("cls");
		}
	}
	return config;
	delete[] opcion;
	delete[] temp;
}

/*
	(int*) La función recibe el vector-pointer *config, lo modifica y lo retorna modificado.
*/	
	
int menu(int* config, Player* players)
{
	char* opcion = new char [1];
	bool salir = 0;
	top();
	system("Pause");
	cout << "\n\n\t\t\t\t\t\t\t  Instrucciones y reglas:" << endl << endl;
	cout << "\t\t 1. La posici" << char(162) << "n de los jugadores est" << char(160) << " representada por P y el n" << char(163) << "mero del jugador." << endl;
	cout << "\t\t 2. Las escaleras est" << char(160) << "n representadas por una EI# en la parte inicial de la escalera y EF# en la parte final." << endl;
	cout << "\t\t 3. Las serpientes est" << char (160) << "n representadas por una SI# en la cabeza de la serpiente y SF# en la cola." << endl;
	cout << "\n\t\t\t\t\t\t\tUn ejemplo de una casilla es:" << endl;
	cout << "\t\t\t\t\t\t\t\t ";
	for (int i=0; i<10; i++)
	cout << "_";
	cout << endl;
	cout << "\t\t\t\t\t\t\t\t|P3      13|\n";
	cout << "\t\t\t\t\t\t\t\t|   SI2    |\n";
	cout << "\t\t\t\t\t\t\t\t|__________|\n" << endl;
	cout << "\t\t\t   Indica que el jugador 3 est" << char(160) << " ubicado en la casilla 13, en la cabeza de la serpiente 2." << endl << endl;
		
	cout << "\t\t 4. Para realizar un movimiento, se debe presionar 'Enter' cuando se indique y el n" << char(163) << "mero del dado ser" << char(160) << " aleatorio." << endl;
	cout << "\t\t 5. Si un jugador obtiene el n" << char(163) << "mero 6 en los dados, podr" << char(160) << " lanzar una segunda vez." << endl;
	cout << "\t\t 6. Un jugador, al obtener tres veces consecutivas un 6, se devuelve a su posici" << char(162) << "n inicial hasta que obtenga de nuevo un 6 (" << char(160) << "rcel). Se puede desactivar." << endl;
	cout << "\t\t 7. Al estar en las " << char(163) << "ltimas casillas, debe obtener el n" << char(163) << "mero exacto para ganar. Ej: Si faltan 3 posiciones, debe obtener un 3." << endl;
	cout << "\t\t 8. Si dos jugadores est" << char(160) << "n en la misma casilla, s" << char(162) << "lo se mostrar" << char(160) << " el " << "primero en llegar a la misma." << endl << endl;
			
	cout << "\t\t[!] Se recomienda abrir la consola en pantalla completa y con fuente en tama" << char(164) << "o mediana para ver el tablero completo." << endl;
	cout << "\t\t\t\t El primer jugador que llegue a la casilla final gana y termina el juego." << endl;
	cout << "\t\t\t\t\t\t";
	system("Pause");
	while (!salir)
	{
		system("cls");
		top();
		cout << "\n\t\t\t\tEl m" << char(160) << "ximo de jugadores es de 4 (minimo 2). Ingrese '9' para cambiar la configuraci" << char(162) << "n del tablero." << endl;
		cout << "\n\t\t\t\t\t\t   Ingrese el n" << char(163) << "mero de jugadores: ";
		cin >> opcion;
		if (atoi(opcion) == 9)
			configuracion(config);
		else if (atoi(opcion) > 4 || atoi(opcion) < 2)
			system("cls");
		else
			return atoi(opcion);
	}
	delete[] opcion;
}
	
/*
	(int) La función pide por pantalla el número de jugadores y lo retorna.
*/	

template <typename T>
void nueva_escalera(Tablero<T> * tablero, int pos_i, int pos_f, int* config)
{
	char* temp = new char [1];
	/*
		Si se trata de crear una escalera en una casilla que no existe en el tablero, retorna mensaje de error
	*/
	if (pos_i>pos_f || pos_i > *(config) || pos_f > *(config))
		cout << "\t\t\tError: Los valores ingresados para crear la escalera no son v" << char(160) << "lidos." << endl;
	else
	{
		itoa(G_ID, temp, 10);
		(puntero(tablero,pos_i))->id = G_ID;
		(puntero(tablero,pos_f))->id = G_ID;
		(puntero(tablero, pos_i)->ptr) = puntero(tablero, pos_f);
		strcpy((puntero(tablero, pos_i))->type, "EI");
		strcpy((puntero(tablero, pos_f))->type, "EF");
		G_ID++;
	}
	delete[] temp;
}

/*
	(void) Esta función crea los punteros correspondientes en las casillas del tablero y modifica los 'type'
	para que en la impresión aparezca la parte inicial (EI) y la parte final (EF).
*/

template <typename T>
void nueva_serpiente(Tablero <T> * tablero, int pos_i, int pos_f, int* config)
{
	char* temp = new char [1];
	/*
		Si se trata de crear una serpiente en una casilla que no existe en el tablero, retorna mensaje de error
	*/
	if (pos_i<pos_f || pos_f > *(config) || pos_i > *(config))
		cout << "\t\t\tError: Los valores ingresados para crear la serpiente no son v" << char(160) << "lidos." << endl;
	else
	{
		itoa(G_ID, temp, 10);
		(puntero(tablero, pos_i))->id = G_ID;
		(puntero(tablero, pos_f))->id = G_ID;
		((puntero(tablero, pos_i))->ptr) = puntero(tablero,pos_f);
		strcpy((puntero(tablero, pos_i))->type, "SI");
		strcpy((puntero(tablero, pos_f))->type, "SF");
		G_ID++;
	}
	delete[] temp;
}

/*
	(void) Esta función crea los punteros correspondientes en las casillas del tablero y modifica los 'type'
	para que en la impresión aparezca la parte inicial (SI) y la parte final (SF).
*/

void _ganador(int n, Player* players)
{
	system("cls");
	top();
	cout << "\n\t\t\t\t\t" << char(173) << char(173) << char(173) << "El ganador es el jugador " << n << ": " << (players+n)->nombre << char(33) << char(33) << char(33);
	cout << "\n\t\t\tGracias por jugar." << endl;
	exit(1);
}

/*
	(void) Esta función termina el juego, recibe por parámetro el número del jugador ganador y lo
	imprime por pantalla. 
*/	

void nuevaCasilla (Tablero <Casilla*> * tablero, int num)
{
	Nodo <Casilla*> * nuevo;
    nuevo = new Nodo <Casilla*> ();
    
	Casilla* nuevaInfo = new Casilla [1];
	
	nuevaInfo->num = num;
	nuevaInfo->ptr = NULL;
	strcpy(nuevaInfo->type, "AA");
    
    nuevo->info = nuevaInfo;
    nuevo->sig = NULL;
    
    if (tablero->tam == 0)
        tablero->inicio = nuevo;
        
    else
    {
        Nodo <Casilla*> * aux;
        aux = tablero->inicio;
        
        while(aux->sig != NULL)
           aux = aux->sig;
           
        aux->sig = nuevo;    
    }
    
	tablero->tam++;
}

/*
	(void) Crea una nueva casilla dentro del tablero. Recibe por parámetros el tablero
	y un número (num) que es el que indicará el número de la casilla. Para hacer uso de
	esta función y que tenga un correcto funcionamiento, se debe acompañar de un ciclo
	que aumente el 'num' consecutivamente.
	
	Adaptada del TAD Lista.
*/

template <typename T>
Tablero <T> *_inicializarTablero (Tablero<T> * tablero, int* config)
{
	for (int i=0; i<*(config); i++)
		nuevaCasilla(tablero, i);
	return tablero;
}

/*
	(Tablero <T> *) La función inicializa el tablero, hace la creación correspondiente de casillas
	por medio de la función nuevaCasilla y finalmente lo retorna creado.
*/

Casilla* puntero(Tablero <Casilla*> * tablero, int p)
{
   Nodo <Casilla*> * aux;
   aux = tablero->inicio;
   int i = 1;
   
   while (aux != NULL)
   {
		if(i == p) return aux->info;
        aux = aux->sig;
        i++;
   }
}
/*
	(Casilla*) Es una de las funciones más importantes. Trabaja como un tipo Apuntador hacia las diferentes
	Casillas, ubicadas en los Nodos de la Lista (la lista es Tablero y la Casilla es la información del Nodo).
	
	Es una adaptación del TAD Lista, para poder acceder fácilmente a las casillas del tablero.
*/

bool _verPreguntas(stack <char*> &preguntas, stack <char*> &respuestas)
{	
	ifstream Preguntas("preguntas.txt", ios::in);
	if (!Preguntas)
	{
		cout << "\t\t\t\t[!] ERROR: No existe el archivo 'preguntas.txt'.";
		system("Pause");
		return false;
	}
	
	ifstream Respuestas("respuestas.txt", ios::in);
	if (!Respuestas)
	{
		cout << "\t\t\t\t[!] ERROR: No existe el archivo 'respuestas.txt'.";
		system("Pause");
		return false;
	}
	
	while (!Preguntas.eof())
	{
		char* line = new char [30];
		Preguntas.getline(line, sizeof(Preguntas));
		strlwr(line);
		preguntas.push(line);
	}
	
	Preguntas.close();
	
	while (!Respuestas.eof())
	{
		char* line = new char [30];
		Respuestas.getline(line, sizeof(Respuestas));
		strlwr(line);
		respuestas.push(line);
	}
	
	Respuestas.close();
	
	if (preguntas.size() != respuestas.size()) return false;
	else return true;
}

/*
	(bool) Accede a los archivos 'preguntas.txt' y 'respuestas.txt' en busca de llenar
	las pilas correspondientes. Retorna verdadero si ambas pilas tienen el mismo tamaño, es decir
	si hay la misma cantidad de preguntas que de respuestas en los archivos. Retorna falso si
	no se cumple lo anteriormente mencionado o si los archivos no existen.
*/

bool _preguntar(stack <char*> &preguntas, stack <char*> &respuestas, int jugador, Player* players, char t)
{
	char* pregunta = new char [30];
	char* respuesta = new char [30];
	
	system("cls");
	top();

	if (preguntas.empty())
	{
		cout << "\n\t\t\t\tSe acabaron las preguntas del juego. Se repetiran las anteriores." << endl;
		_verPreguntas(preguntas, respuestas);
	}
	cout << "\n\t\t\t\t\t\t[!] " << char(173) << (players+jugador)->nombre << " ha caido en";
	if (t == 'E')
		cout << " una escalera!" << endl;
	else if (t == 'S')
		cout << " una serpiente!" << endl;
	cout << "\t\t\t\tDebe contestar para avanzar: " << endl;
	
	pregunta = preguntas.top();
	cout << "\t\t\t\tPregunta: " << char(168) << pregunta << char(63) << endl;
	cout << "\t\t\t\tRespuesta: ";
	
	cin.getline(respuesta, 30);
	strlwr(respuesta);
	if (strcmp(respuesta, respuestas.top()) == 0)
	{
		cout << "\t\t\t\t\t\t" << char(173) << "RESPUESTA CORRECTA! ";
		if (t == 'E')
			cout << "Subir" << char(160) << " la escalera." << endl;
		else if (t == 'S')
			cout << "No caer" << char(160) << " en la serpiente." << endl;
			
		preguntas.pop();
		respuestas.pop();
		
		return true;	
	}

	else 
	{
		cout << "\t\t\t\t\t\t" << char(173) << "RESPUESTA INCORRECTA! ";
		if (t == 'E')
			cout << "No subir" << char(160) << " la escalera :(" << endl;
		else if (t == 'S')
			cout << "Caer" << char(160) << " en la serpiente :(" << endl;
		return false;
	}
}

/*
	(bool) Esta función es llamada por la función "jugar" en caso de que un jugador caiga en
	una casilla y requiera responder una pregunta para continuar el juego. Retorna si el jugador
	contestó correctamente o no (verdadero-falso).
	
	Hace uso de las pilas de preguntas y respuestas. Si el jugador contesta bien la pregunta,
	hará un 'pop' en ambas pilas para que así el siguiente jugador que deba contestar 
	tenga una pregunta nueva. Y en caso de que las preguntas se acaben, vuelve a llamar la 
	función "_verPreguntas" para restaurarlas
	de nuevo.
*/
	
template <typename T>
void jugar(int nplayers, Tablero <T> * tablero, Player* players, int* config)
{
	tablero = _inicializarTablero(tablero, config);
	int dados = 0;
	int t = 0; // Variable que irá contando el número de posiciones que avanza un jugador
	players = new Player [nplayers];
	stack <char*> preguntas, respuestas;
	
	if (*(config+3) != -1)
		_verPreguntas(preguntas, respuestas);
	
	for (int i=0; i<nplayers; i++)
	{
		(players+i)->posicion = NULL;
		(players+i)->registro_dados = 0;
		(players+i)->encarcelado = false;
		(players+i)->num_posicion = 0;
	}
	
	// Creación de las escaleras y serpientes por defecto
	
	nueva_escalera(tablero, 7, 39, config);
	nueva_escalera(tablero, 4, 13, config);
	nueva_escalera(tablero, 17, 32, config);
	nueva_serpiente(tablero, 40, 6, config);
	nueva_serpiente(tablero, 21, 3, config);
	nueva_serpiente(tablero, 50, 23, config);
	
	// (tablero+*(config)-1)->id = 99; 
	
	system("cls");
	
	for (int i=0; i<15; i++)
		cout << endl;
		
	for (int i=0; i<nplayers; i++)
	{
		cout << "\t\t\t\t\t Ingrese el nombre del jugador " << i << ": ";
		cin >> (players+i)->nombre;
	}
	
	system("cls");
	
	for (int i=0; i<15; i++)
		cout << endl;
		
	cout << "\t\t\t\t\t";
	for (int i=0; i<nplayers; i++)
	{
		cout << " Jugador " << i <<": " << (players+i)->nombre;
		if (i!=nplayers-1)
			cout << " |";				
	}
	cout << "\n\n\n\n\t\t\t\t\t\tIniciando juego . . . N" << char(163) << "mero de jugadores: " << nplayers << " . . ." << endl;
	cout << "\t\t\t\t\t\t    ";
	system ("pause");
	system("cls");
	while (1)
	{
		for (int turno=0; turno<nplayers; turno++)
		{
			system("cls");
			top();
			_tablero(tablero, *(config),*(config+1), nplayers, players); // Refresh del tablero 
			cout << "\n\t\t\tTurno del jugador " << turno << ": " << (players+turno)->nombre << "\n\t\t\t\t\t";
			system("Pause");
			cout << "\t\t\tLanzando Dados . . .\n\t\t\t";
			
			for (int i=0; i<50; i++)
			{
				srand(time(0));
				dados = (1+rand() % 6);
				if (dados == 0)
					dados = 1;
				cout << dados << " ";
				//Sleep(50);
				/*
					El uso de este Sleep es únicamente visual, para que al jugador se le de una perspectiva
					diferente al momento de lanzar los dados y se vean los números random que va
					generando el sistema.
					
					Se puede eliminar o disminuir su valor para agilizar el juego.
				*/
			}
			
			cout << "\n\t\t\tNumero obtenido: " << dados << endl;
			cout << "\t\t\tPresione 'Enter' para mover la ficha.\n\t\t\t\t\t";
			if (dados==6)
			{
				if (*(config+2) == true)
				{
					if ((players+turno)->encarcelado)
					{
						(players+turno)->encarcelado = false;
						(players+turno)->registro_dados = 0;
					}
					else if ((players+turno)->registro_dados == 2)
					{
						(players+turno)->encarcelado = true;
						(players+turno)->posicion = NULL;
					}				
					else (players+turno)->registro_dados++;
				}
			}
			else (players+turno)->registro_dados = 0; // Restablece el contador si dados no generan el número 6
			
			if (!((players+turno)->encarcelado))
			{
				if ((players+turno)->posicion == NULL)
				{
					(players+turno)->posicion = puntero(tablero, dados);
					(players+turno)->num_posicion = dados;
				}
				else
				{
					if ((players+turno)->num_posicion + dados < *(config) - 1) // Validación para saber si está en las últimas casillas
					{
						(players+turno)->posicion = puntero(tablero, (players+turno)->num_posicion + dados);
						(players+turno)->num_posicion += dados;
					}
					else if ((players+turno)->num_posicion + dados == *(config) - 1)
						_ganador(turno, players);
				}
				
				if (strcmp(((players+turno)->posicion)->type, "EI") == 0)
				{
					if (*(config+3) == 1)
					{
						cin.ignore();
						if (_preguntar(preguntas, respuestas, turno, players, 'E'))
						{
							(players+turno)->posicion = ((players+turno)->posicion)->ptr;
							(players+turno)->num_posicion = ((players+turno)->posicion)->num;
						}
					}
					else
					{
						(players+turno)->posicion = ((players+turno)->posicion)->ptr;
						(players+turno)->num_posicion = ((players+turno)->posicion)->num;
					}
				}
				else if (strcmp(((players+turno)->posicion)->type, "SI") == 0)
				{
					if (*(config+3) == 1)
					{
						cin.ignore();
						if (!_preguntar(preguntas, respuestas, turno, players, 'S'))
						{
							(players+turno)->posicion = ((players+turno)->posicion)->ptr;
							(players+turno)->num_posicion = ((players+turno)->posicion)->num;
						}
					}
					else
					{
						(players+turno)->posicion = ((players+turno)->posicion)->ptr;
						(players+turno)->num_posicion = ((players+turno)->posicion)->num;
					}
				}
			}
			if (dados == 6)
					turno--;
			system("Pause");
		}
	}
}

/*
	(void) Esta función es la principal del juego. Recibe por parámetro el número de jugadores, el tablero de juego,
	el struct-vector de jugadores que contiene la información de cada uno y la configuración del juego.
	
	Hace el encadenamiento de toda esta información y el sistema de dados al final con sus respectivas validaciones,
	el encarcelamiento por triple 6 y el número exacto para ganar, todo mediante pointers (la mayoría struct-pointers).
*/

template <typename T>
Tablero <T> * _crearTablero()
{
	Tablero <T> *nuevoTablero;
	
    nuevoTablero = new Tablero <T>;
    nuevoTablero->tam = 0;
	nuevoTablero->inicio = NULL;
	
	return nuevoTablero;
}

/*
	(Tablero <T> *) Devuelve un tablero creado. Inicializa los valores correspondientes.
	Adaptado del TAD Lista. Es la creación de una nueva lista (tipo Tablero*).
*/

int* _leerConfig()
{
	char opt;
	int* config = new int [3];
	ifstream Lec_Config("config.txt", ios::in);
	
	if (!Lec_Config){
		cout << "\t\t\t[!] ERROR: No existe el archivo 'config.txt'." << endl;
		cout << "\t\t\t[!] Ingrese '1' para crear este archivo.\n\t\t\t";
		cin >> opt;
		if (opt == '1')
		{
			restaurarConfig();
			cout << "\t\t\t[!] Archivo creado. Inicie de nuevo el juego." << endl;
		}
		exit(1);
	}
	
	Lec_Config >> *(config);
	Lec_Config >> *(config+1);
	Lec_Config >> *(config+2);
	Lec_Config >> *(config+3);
	
	if (*(config+2) > 1 || *(config+2) < 0 || *(config+3) > 1 || *(config+3) < 0)
	{
		cout << "\t\t\t[!] Error al leer el archivo. Los datos no son validos." << endl;
		cout << "\t\t\t[!] Ingrese '1' para restaurar este archivo al original.\n\t\t\t";
		cin >> opt;
		if (opt == '1')
		{
			restaurarConfig();
			cout << "\t\t\t[!] Archivo creado. Inicie de nuevo el juego." << endl;
		}
		exit(1);
	}
	else if (*(config) == 0 || *(config+1) == 0 || *(config)%*(config+1) != 0)
	{
		cout << "\t\t\t[!] Error al leer el archivo. Los datos no son validos." << endl;
		cout << "\t\t\t[!] El campo 2 debe ser multiplo del 1 y no pueden ser 0." << endl;
		cout << "\t\t\t[!] Ingrese '1' para restaurar este archivo al original.\n\t\t\t";
		cin >> opt;
		if (opt == '1')
		{
			restaurarConfig();
			cout << "\t\t\t[!] Archivo creado. Inicie de nuevo el juego." << endl;
		}
		exit(1);
	}
	stack <char*> preguntas;
	stack <char*> respuestas;
	
	if (!_verPreguntas(preguntas, respuestas))
	{
		cout << "\t\t\t[!] ERROR: Se ha desactivado la opcion de juego con preguntas. Revise los archivos 'preguntas.txt' y 'respuestas.txt'." << endl;
		cout << "\t\t\t[!] Asegurese de que haya la misma cantidad de preguntas que de respuestas en los archivos (y que estos existan)." << endl << "\t\t\t\t\t\t";
		*(config+3) = -1;
		system("Pause");
		system("cls");
	}
	
	Lec_Config.close();
	return config;
}
/*
	(int*) Esta función ingresa al archivo 'config.txt' y según la lectura correspondiente, retorna
	el vector de configuración actualizado. Si encuentra algún problema, sugiere al usuario restaurar
	el archivo de configuraciones a uno predeterminado (original).
*/



/*
	  Código Elaborado por Nicolás David Cubillos Cubillos
	Estudiante de Ingeniería de Sistemas - Segundo Semestre
	       Profesor: José Hernando Hurtado Rojas
             Pontificia Universidad Javeriana
	           Programación de Computadores
	
	
	             25 de noviembre de 2020
*/

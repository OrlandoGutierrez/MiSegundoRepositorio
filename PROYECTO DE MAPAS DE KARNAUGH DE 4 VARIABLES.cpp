#include <string.h>
#include <conio.h>
#include <stdio.h>   
#include <stdlib.h>
#include <iostream>

using namespace std; //para poder usar String ya que vamos a guardar caracteres de una matriz 
//Area de estructuras
struct Verdadero{ //Esta estructura guarda la posicion y la cantidad de veces que esta posicion aparece en los grupos
	int pos;
	int can;
	Verdadero(){
	}
	Verdadero(int pos_,int can_){
		pos = pos_;
		can = can_;
	}
};
struct Coleccion{//Almacena solo valores verdaderos 
	int num;//el numero de coleccion al que pertenece
	Verdadero lis[20]; //la cantidad de valores verdaderos que tiene 
	int can;//si hay grupos redundante sera marcado con 10 de lo contrario sera marcado con 20
	bool boo;//sirve para marcar que este grupo no debe ser tomado en cuenta
	Coleccion(){
	}
	Coleccion(int num_, int can_, bool boo_, int ver0, int ver1, int ver2, int ver3, int ver4, int ver5, int ver6, int ver7, int ver8, int ver9, int ver10, int ver11, int ver12, int ver13, int ver14, int ver15, int ver16, int ver17, int ver18, int ver19)
	{
		num = num_; // matriz 
		lis[0] =  Verdadero(ver0, can_);
		lis[1] =  Verdadero(ver1, can_);
		lis[2] =  Verdadero(ver2, can_);
		lis[3] =  Verdadero(ver3, can_);
		lis[4] =  Verdadero(ver4, can_);
		lis[5] =  Verdadero(ver5, can_);
		lis[6] =  Verdadero(ver6, can_);
		lis[7] =  Verdadero(ver7, can_);
		lis[8] =  Verdadero(ver8, can_);
		lis[9] =  Verdadero(ver9, can_);
		lis[10] =  Verdadero(ver10, can_);
		lis[11] =  Verdadero(ver11, can_);
		lis[12] =  Verdadero(ver12, can_);
		lis[13] =  Verdadero(ver13, can_);
		lis[14] =  Verdadero(ver14, can_);
		lis[15] =  Verdadero(ver15, can_);
		lis[16] =  Verdadero(ver16, can_);
		lis[17] =  Verdadero(ver17, can_);
		lis[18] =  Verdadero(ver18, can_);
		lis[19] =  Verdadero(ver19, can_);
		can = can_;
		boo = boo_;
	}
};
struct Expresion
{ //Esto enlaza la expresion correspondiente con la coleccion correspondiente
	int num;
	string text;
	Expresion(){
	}
	Expresion(int num_, string text_){
		num = num_;
		text = text_;
	}
};
 //Area de variables globales
int m[15];
Coleccion col[81];
bool GruRedun(Coleccion*);
void MarcaColeccion(Coleccion*);
void BorraMatriz81(int*);
void Agregar(int, int*);
void Alterar(int,int*,int*); 
void Eliminar(int,int*);
void CaptarColecciones(int*);
void Algoritmo(int*);
Expresion exp[81];
//Area de metodos y funciones generales
void BorraMapa()
{
	for(int i = 0;i<15;i++){
		m[i] = 0;
	}
}

void MenPricipal()
{//Metodo que presenta el menu y el mapa de karcaugh segun como este almacenado en la variable int m[15]
	
	system("cls");
	
	printf("\n\t\t\t    ________________________________________");
	printf("\n\n\t\t\t    | MAPA DE KARNAUGH DE 4 VARIABLES EN C |");
	printf("\n\t\t\t    ________________________________________");
	
	
	printf("\n\n                   AB              \t\t|                   AB");
	printf("\n           00    01     11     10    \t\t|            00    01     11     10    ");
	printf("\n        _____________________________\t\t|        _____________________________");
	printf("\n                                     \t\t|");
	printf("\n    00  |   0  |   1  |   2  |   3  |\t\t|     00  |   %d  |   %d  |   %d  |   %d  |",m[0],m[1],m[2],m[3]);
	printf("\n        _____________________________\t\t|        _____________________________");
	printf("\n CD                                  \t\t| CD");
	printf("\n    01  |   4  |   5  |   6  |   7  |\t\t|     01  |   %d  |   %d  |   %d  |   %d  |",m[4],m[5],m[6],m[7]);
	printf("\n        _____________________________\t\t|        _____________________________");
	printf("\n                                     \t\t|");
	printf("\n    11  |   8  |   9  |  10  |  11  |\t\t|     11  |   %d  |   %d  |   %d  |   %d  |",m[8],m[9],m[10],m[11]);
	printf("\n        _____________________________\t\t|        _____________________________");
	printf("\n                                     \t\t|");
	printf("\n    10  |  12  |  13  |  14  |  15  |\t\t|     10  |   %d  |   %d  |   %d  |   %d  |",m[12],m[13],m[14],m[15]);
	printf("\n        _____________________________\t\t|        _____________________________");
	printf("\n\n");
	printf("\n Si desea cerrar el programa digite 20");
	printf("\n");
	printf("\n Si quiere ver la expresion minima digite 21");
	printf("\n");
	printf("\n -Ingrese la posicion en la que quiere alterar el valor: ");
}
int HiloPrincipal()
{//Se encarga de gestionar la recoleccion de los valores para la matriz, de cerrar el programa o de permitir la ejecucion del algoritmo
	MenPricipal();
	int b;
	for (b;b>=0;){
		scanf("%d",&b);
		if ((b > -1 && b < 16)||(b > 19 && b < 22)){
			switch (b){
				case 20:
					return 20;
				break;
				case 21:
					return 21;
				break;
			}
			if (m[b]==1){
				m[b]=0;
			}else{
				m[b]=1;
			}
			MenPricipal();
		}
	}
}
void BorraMatriz81(int *arr)
{//Aqui ingresa una matriz con distindos valores y todo lo que hace es asignarle a cada puesto el -1
	for(int i = 0;i<81;i++)
	{
		*arr =  -1;
		arr++; 
	}
}
//Area de metodos y funciones del algoritmo
void IngresaExpresiones()
{//Metodo de configuracion ya que solo se le ingresa los valores que enlazan a la coleccion y la expresion
	exp[0] =  Expresion(0, "1");
	
	exp[1] =  Expresion(1, "c");
	exp[2] =  Expresion(2, "D");
	exp[3] =  Expresion(3, "C");
	exp[4] =  Expresion(4, "d");
			
	exp[5] =  Expresion(5, "a");
	exp[6] =  Expresion(6, "B");
	exp[7] =  Expresion(7, "A");
	exp[8] =  Expresion(8, "b");
	
	exp[9] =  Expresion(9, "cd");
	exp[10] =  Expresion(10, "cD");
	exp[11] =  Expresion(11, "CD");
	exp[12] =  Expresion(12, "Cd");
	
	exp[13] =  Expresion(13, "ab");
	exp[14] =  Expresion(14, "aB");
	exp[15] =  Expresion(15, "AB");
	exp[16] =  Expresion(16, "Ab");
	
	exp[17] =  Expresion(17, "ac");
	exp[18] =  Expresion(18, "Bc");
	exp[19] =  Expresion(19, "Ac");
	exp[20] =  Expresion(20, "bc");
	exp[21] =  Expresion(21, "aD");
	exp[22] =  Expresion(22, "BD");
	exp[23] =  Expresion(23, "AD");
	exp[24] =  Expresion(24, "bD");
	
	exp[25] =  Expresion(25, "aC");
	exp[26] =  Expresion(26, "BC");
	exp[27] =  Expresion(27, "AC");
	exp[28] =  Expresion(28, "bC");
	exp[29] =  Expresion(29, "aD");
	exp[30] =  Expresion(30, "Bd");
	exp[31] =  Expresion(31, "Ad");
	exp[32] =  Expresion(32, "bd");
	
	exp[33] =  Expresion(33, "acd");
	exp[34] =  Expresion(34, "Bcd");
	exp[35] =  Expresion(35, "Acd");
	exp[36] =  Expresion(36, "bcd");
	exp[37] =  Expresion(37, "acD");
	exp[38] =  Expresion(38, "BcD");
	exp[39] =  Expresion(39, "AcD");
	exp[40] =  Expresion(40, "bcD");
	
	exp[41] =  Expresion(41, "aCD");
	exp[42] =  Expresion(42, "BCD");
	exp[43] =  Expresion(43, "ACD");
	exp[44] =  Expresion(44, "bCD");
	exp[45] =  Expresion(45, "aCd");
	exp[46] =  Expresion(46, "BCd");
	exp[47] =  Expresion(47, "ACd");
	exp[48] =  Expresion(48, "bCd");
	
	exp[49] =  Expresion(49, "abc");
	exp[50] =  Expresion(50, "aBc");
	exp[51] =  Expresion(51, "ABc");
	exp[52] =  Expresion(52, "Abc");
	exp[53] =  Expresion(53, "abD");
	exp[54] =  Expresion(54, "aBD");
	exp[55] =  Expresion(55, "ABD");
	exp[56] =  Expresion(56, "AbD");
	
	exp[57] =  Expresion(57, "abC");
	exp[58] =  Expresion(58, "aBC");
	exp[59] =  Expresion(59, "ABC");
	exp[60] =  Expresion(60, "AbC");
	exp[61] =  Expresion(61, "abd");
	exp[62] =  Expresion(62, "aBd");
	exp[63] =  Expresion(63, "ABd");
	exp[64] =  Expresion(64, "Abd");
	
	exp[65] =  Expresion(65, "abcd");
	exp[66] =  Expresion(66, "aBcd");
	exp[67] =  Expresion(67, "ABcd");
	exp[68] =  Expresion(68, "Abcd");
	exp[69] =  Expresion(69, "abcD");
	exp[70] =  Expresion(70, "aBcD");
	exp[71] =  Expresion(71, "ABcD");
	exp[72] =  Expresion(72, "AbcD");
	
	exp[73] =  Expresion(73, "abCD");
	exp[74] =  Expresion(74, "aBCD");
	exp[75] =  Expresion(75, "ABCD");
	exp[76] =  Expresion(76, "AbCD");
	exp[77] =  Expresion(77, "abCd");
	exp[78] =  Expresion(78, "aBCd");
	exp[79] =  Expresion(79, "ABCd");
	exp[80] =  Expresion(80, "AbCd");
}
void IngresaColecciones()
{//Esto sirve para verificar que no hay grupos redundantes 
	col[0] = Coleccion(0,-1,false,0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -1, -1, -1,-1);
	col[1] = Coleccion(1,-1,false,0, 1, 2, 3, 4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[2] = Coleccion(2,-1,false,4, 5, 6, 7, 8, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[3] = Coleccion(3,-1,false,8, 9, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[4] = Coleccion(4,-1,false,0, 1, 2, 3, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[5] = Coleccion(5,-1,false,0, 1, 4, 5, 8, 9, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[6] = Coleccion(6,-1,false,1, 2, 5, 6, 9, 10, 13, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[7] = Coleccion(7,-1,false,2, 3, 6, 7, 10, 11, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[8] = Coleccion(8,-1,false,0, 3, 4, 7, 8, 11, 12, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[9] = Coleccion(9,-1,false,0, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[10] = Coleccion(10,-1,false,4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[11] = Coleccion(11,-1,false,8, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[12] = Coleccion(12,-1,false,12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[13] = Coleccion(13,-1,false,0, 4, 8, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[14] = Coleccion(14,-1,false,1, 5, 9, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[15] = Coleccion(15,-1,false,2, 6, 10, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[16] = Coleccion(16,-1,false,3, 7, 11, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[17] = Coleccion(17,-1,false,0, 1, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[18] = Coleccion(18,-1,false,1, 2, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[19] = Coleccion(19,-1,false,2, 3, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[20] = Coleccion(20,-1,false,0, 3, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[21] = Coleccion(21,-1,false,4, 5, 8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[22] = Coleccion(22,-1,false,5, 6, 9, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[23] = Coleccion(23,-1,false,6, 7, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[24] = Coleccion(24,-1,false,4, 7, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[25] = Coleccion(25,-1,false,8, 9, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[26] = Coleccion(26,-1,false,9, 10, 13, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[27] = Coleccion(27,-1,false,10, 11, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[28] = Coleccion(28,-1,false,8, 11, 12, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[29] = Coleccion(29,-1,false,0, 1, 12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[30] = Coleccion(30,-1,false,1, 2, 13, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[31] = Coleccion(31,-1,false,2, 3, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[32] = Coleccion(32,-1,false,0, 3, 12, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[33] = Coleccion(33,-1,false,0, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[34] = Coleccion(34,-1,false,1, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[35] = Coleccion(35,-1,false,2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[36] = Coleccion(36,-1,false,0, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[37] = Coleccion(37,-1,false,4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[38] = Coleccion(38,-1,false,5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[39] = Coleccion(39,-1,false,6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[40] = Coleccion(40,-1,false,4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[41] = Coleccion(41,-1,false,8, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[42] = Coleccion(42,-1,false,9, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[43] = Coleccion(43,-1,false,10, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[44] = Coleccion(44,-1,false,8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[45] = Coleccion(45,-1,false,12, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[46] = Coleccion(46,-1,false,13, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[47] = Coleccion(47,-1,false,14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[48] = Coleccion(48,-1,false,12, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[49] = Coleccion(49,-1,false,0, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[50] = Coleccion(50,-1,false,1, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[51] = Coleccion(51,-1,false,2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[52] = Coleccion(52,-1,false,3, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[53] = Coleccion(53,-1,false,4, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[54] = Coleccion(54,-1,false,5, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[55] = Coleccion(55,-1,false,6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[56] = Coleccion(56,-1,false,7, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[57] = Coleccion(57,-1,false,8, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[58] = Coleccion(58,-1,false,9, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[59] = Coleccion(59,-1,false,10, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[60] = Coleccion(60,-1,false,11, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[61] = Coleccion(61,-1,false,0, 12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[62] = Coleccion(62,-1,false,1, 13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[63] = Coleccion(63,-1,false,2, 14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[64] = Coleccion(64,-1,false,3, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
	col[65] = Coleccion(65,-1,false,0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[66] = Coleccion(66,-1,false,1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[67] = Coleccion(67,-1,false,2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[68] = Coleccion(68,-1,false,3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[69] = Coleccion(69,-1,false,4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[70] = Coleccion(70,-1,false,5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[71] = Coleccion(71,-1,false,6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[72] = Coleccion(72,-1,false,7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[73] = Coleccion(73,-1,false,8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[74] = Coleccion(74,-1,false,9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[75] = Coleccion(75,-1,false,10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[76] = Coleccion(76,-1,false,11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[77] = Coleccion(77,-1,false,12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[78] = Coleccion(78,-1,false,13, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[79] = Coleccion(79,-1,false,14, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	col[80] = Coleccion(80,-1,false,15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,-1);
	
}
void VerColecciones(Coleccion *col_)
{//Esto es a modo de depuracion y no es parte del programa, permite ver que el ingreso este correcto
	for (int i = 0;i<81;i++){
		printf("Cole= %i  %i  %i (",col_->num,col_->can,col_->boo);
		for (int j = 0;j<20;j++){
			if(col_->lis[j].pos != -1){
				if (j != 0){
					printf(", ",col_->lis[j].pos);
				}
				printf("%i",col_->lis[j].pos);	
			}
		}
		printf(")\n");
		col_++;
	}
}
void ResetColecciones(Coleccion *col_)
{//Esto es a modo de depuracion y no es parte del programa, permite ver que enl ingreso este correcto
	for (int i = 0;i<81;i++){
		col_->boo = false;
		col_->can = -1;
		col_++;
	}
}
//Main 
int main()
{//Aqui es donde se ejecutan las acciones que se mandan a traves de la funcion de HiloPrincipal()
  //Configuracion
	IngresaExpresiones();
	IngresaColecciones();
	
  //Ejecucion
	bool ejecutando = true;
	int opcion = 0;
	string expresion = "";
	string aux = "";
	while(ejecutando){//Este es quien mantiene al programa sin cerrar hasta que ejecutrando sea falso
		//Declaracion de matriz y poniendo todos los valores a -1
		ResetColecciones(&col[0]);
		int Col_1[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
		BorraMapa(); //Borrando mapa ya que se ejecuta todo como al inicio
		opcion = HiloPrincipal();//*Aqui es donde se recupera el valor para tomal la decision de correr el algoritmo o cerrar el programa
		bool mas = false;
		switch (opcion){
			case 20:
				ejecutando = false;//Para salir del while y cerrar el programa
			break;
			case 21:
				expresion = "";
				Algoritmo(&Col_1[0]);//Aqui se da como resultado las colecciones que forman la expresion minima
				//asi que la funcion Algoritmo
				
				for (int i = 0;i<81;i++){
					if (Col_1[i] == -1){
						break;
					}else{
						
						if (mas){
							expresion = expresion + " + ";
						}
						aux = exp[Col_1[i]].text;
						
						expresion = expresion + aux;
						mas = true;
					}
				}
				printf("\n Su expresion minima es: %s", expresion.c_str());
				printf("\n\n Presione cualquier tecla para continuar");
				getch();
				ejecutando = true;
			break;
		}
	}
    return 0;
	
}

void Algoritmo(int *arr)
{// el corazon de todo el programa
	//-1 significa espacio vacio
	int Col_Alg[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
	CaptarColecciones(&Col_Alg[0]);
	
	//fin siguiente algoritmo
	for(int i = 0;i<81;i++)
	{
		if (Col_Alg[i] == -1)
		{
			break;
		}else{
			*arr =  Col_Alg[i];
			arr++; 
		}
	}
}


Coleccion Col[81];

void CaptarColecciones(int *arr){
	//Arma todos los grupos
	
	//-1 significa espacio vacio
	int Col_Alg[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
	int Indice = 0;
if(true)
{	//este if solo es para plegar todo ese codigo
	if (m[ 0]    && m[ 1]    && m[ 2]    && m[ 3]    &&
		m[ 4]    && m[ 5]    && m[ 6]    && m[ 7]    &&
		m[ 8]    && m[ 9]    && m[10]    && m[11]    &&
		m[12]    && m[13]    && m[14]    && m[15]   )
	{
		Col_Alg[Indice] = 0;
		Indice++;
		
	}
	
	if (m[ 0] && m[ 1] && m[ 2] && m[ 3] && m[ 4] && m[ 5] && m[ 6] && m[ 7])
	{
		Col_Alg[Indice] = 1;
		Indice++;
	}
	
	if (m[ 4] && m[ 5] && m[ 6] && m[ 7] && m[ 8] && m[ 9] && m[10] && m[11])
	{
		Col_Alg[Indice] = 2;
		Indice++;
	}
	
	if (m[ 8] && m[ 9] && m[10] && m[11] && m[12] && m[13] && m[14] && m[15])
	{
		Col_Alg[Indice] = 3;
		Indice++;
	}
	
	if (m[ 0] && m[ 1] && m[ 2] && m[ 3] && m[12] && m[13] && m[14] && m[15])
	{
		Col_Alg[Indice] = 4;
		Indice++;
	}
	
	if (m[ 0] && m[ 1] && m[ 4] && m[ 5] && m[ 8] && m[ 9] && m[12] && m[13])
	{
		Col_Alg[Indice] = 5;
		Indice++;
	}
	
	if (m[ 1] && m[ 2] && m[ 5] && m[ 6] && m[ 9] && m[10] && m[13] && m[14])
	{
		Col_Alg[Indice] = 6;
		Indice++;
	}
	
	if (m[ 2] && m[ 3] && m[ 6] && m[ 7] && m[10] && m[11] && m[14] && m[15])
	{
		Col_Alg[Indice] = 7;
		Indice++;
	}
	
	if (m[ 0] && m[ 3] && m[ 4] && m[ 7] && m[ 8] && m[11] && m[12] && m[15])
	{
		Col_Alg[Indice] = 8;
		Indice++;
	}
	
	if (m[ 0] && m[ 1] && m[ 2] && m[ 3])
	{
		Col_Alg[Indice] = 9;
		Indice++;
	}
	
	if (m[ 4] && m[ 5] && m[ 6] && m[ 7])
	{
		Col_Alg[Indice] = 10;
		Indice++;
	}
	
	if (m[ 8] && m[ 9] && m[10] && m[11])
	{
		Col_Alg[Indice] = 11;
		Indice++;
	}
	
	if (m[12] && m[13] && m[14] && m[15])
	{
		Col_Alg[Indice] = 12;
		Indice++;
	}
	
	if (m[ 0] && m[ 4] && m[ 8] && m[12])
	{
		Col_Alg[Indice] = 13;
		Indice++;
	}
	
	if (m[ 1] && m[ 5] && m[ 9] && m[13])
	{
		Col_Alg[Indice] = 14;
		Indice++;
	}
	
	if (m[ 2] && m[ 6] && m[10] && m[14])
	{
		Col_Alg[Indice] = 15;
		Indice++;
	}
	
	if (m[ 3] && m[ 7] && m[11] && m[15])
	{
		Col_Alg[Indice] = 16;
		Indice++;
	}
	
	if (m[ 0] && m[ 1] && m[ 4] && m[ 5])
	{
		Col_Alg[Indice] = 17;
		Indice++;
	}
	
	if (m[ 1] && m[ 2] && m[ 5] && m[ 6])
	{
		Col_Alg[Indice] = 18;
		Indice++;
	}
	
	if (m[ 2] && m[ 3] && m[ 6] && m[ 7])
	{
		Col_Alg[Indice] = 19;
		Indice++;
	}
	
	if (m[ 0] && m[ 3] && m[ 4] && m[ 7])
	{
		Col_Alg[Indice] = 20;
		Indice++;
	}
	
	if (m[ 4] && m[ 5] && m[ 8] && m[ 9])
	{
		Col_Alg[Indice] = 21;
		Indice++;
	}
	
	if (m[ 5] && m[ 6] && m[ 9] && m[10])
	{
		Col_Alg[Indice] = 22;
		Indice++;
	}
	
	if (m[ 6] && m[ 7] && m[10] && m[11])
	{
		Col_Alg[Indice] = 23;
		Indice++;
	}
	
	if (m[ 4] && m[ 7] && m[ 8] && m[11])
	{
		Col_Alg[Indice] = 24;
		Indice++;
	}
	
	if (m[ 8] && m[ 9] && m[12] && m[13])
	{
		Col_Alg[Indice] = 25;
		Indice++;
	}
	
	if (m[ 9] && m[10] && m[13] && m[14])
	{
		Col_Alg[Indice] = 26;
		Indice++;
	}
	
	if (m[10] && m[11] && m[14] && m[15])
	{
		Col_Alg[Indice] = 27;
		Indice++;
	}
	
	if (m[ 8] && m[11] && m[12] && m[15])
	{
		Col_Alg[Indice] = 28;
		Indice++;
	}
	
	if (m[ 0] && m[ 1] && m[12] && m[13])
	{
		Col_Alg[Indice] = 29;
		Indice++;
	}
	
	if (m[ 1] && m[ 2] && m[13] && m[14])
	{
		Col_Alg[Indice] = 30;
		Indice++;
	}
	
	if (m[ 2] && m[ 3] && m[14] && m[15])
	{
		Col_Alg[Indice] = 31;
		Indice++;
	}
	
	if (m[ 0] && m[ 3] && m[12] && m[15])
	{
		Col_Alg[Indice] = 32;
		Indice++;
	}
	
	if (m[ 0] && m[ 1])
	{
		Col_Alg[Indice] = 33;
		Indice++;
	}
	
	if (m[ 1] && m[ 2])
	{
		Col_Alg[Indice] = 34;
		Indice++;
	}
	
	if (m[ 2] && m[ 3])
	{
		Col_Alg[Indice] = 35;
		Indice++;
	}
	
	if (m[ 0] && m[ 3])
	{
		Col_Alg[Indice] = 36;
		Indice++;
	}
	
	if (m[ 4] && m[ 5])
	{
		Col_Alg[Indice] = 37;
		Indice++;
	}
	
	if (m[ 5] && m[ 6])
	{
		Col_Alg[Indice] = 38;
		Indice++;
	}
	
	if (m[ 6] && m[ 7])
	{
		Col_Alg[Indice] = 39;
		Indice++;
	}
	
	if (m[ 4] && m[ 7])
	{
		Col_Alg[Indice] = 40;
		Indice++;
	}
	
	if (m[ 8] && m[ 9])
	{
		Col_Alg[Indice] = 41;
		Indice++;
	}
	
	if (m[ 9] && m[10])
	{
		Col_Alg[Indice] = 42;
		Indice++;
	}
	
	if (m[10] && m[11])
	{
		Col_Alg[Indice] = 43;
		Indice++;
	}
	
	if (m[ 8] && m[11])
	{
		Col_Alg[Indice] = 44;
		Indice++;
	}
	
	if (m[12] && m[13])
	{
		Col_Alg[Indice] = 45;
		Indice++;
	}
	
	if (m[13] && m[14])
	{
		Col_Alg[Indice] = 46;
		Indice++;
	}
	
	if ( m[14] && m[15])
	{
		Col_Alg[Indice] = 47;
		Indice++;
	}
	
	if (m[12] && m[15]   )
	{
		Col_Alg[Indice] = 48;
		Indice++;
	}
	
	if (m[ 0] && m[ 4])
	{
		Col_Alg[Indice] = 49;
		Indice++;
	}
	
	if (m[ 1] && m[ 5])
	{
		Col_Alg[Indice] = 50;
		Indice++;
	}
	
	if (m[ 2] && m[ 6])
	{
		Col_Alg[Indice] = 51;
		Indice++;
	}
	
	if (m[ 3] && m[ 7])
	{
		Col_Alg[Indice] = 52;
		Indice++;
	}
	
	if (m[ 4] && m[ 8])
	{
		Col_Alg[Indice] = 53;
		Indice++;
	}
	
	if (m[ 5] && m[ 9])
	{
		Col_Alg[Indice] = 54;
		Indice++;
	}
	
	if (m[ 6] && m[10])
	{
		Col_Alg[Indice] = 55;
		Indice++;
	}
	
	if (m[ 7] && m[11])
	{
		Col_Alg[Indice] = 56;
		Indice++;
	}
	
	if (m[ 8] && m[12])
	{
		Col_Alg[Indice] = 57;
		Indice++;
	}
	
	if (m[ 9] && m[13])
	{
		Col_Alg[Indice] = 58;
		Indice++;
	}
	
	if (m[10] && m[14])
	{
		Col_Alg[Indice] = 59;
		Indice++;
	}
	
	if (m[11] && m[15])
	{
		Col_Alg[Indice] = 60;
		Indice++;
	}
	
	if (m[ 0] && m[12])
	{
		Col_Alg[Indice] = 61;
		Indice++;
	}
	
	if (m[ 1] && m[13])
	{
		Col_Alg[Indice] = 62;
		Indice++;
	}
	
	if (m[ 2] && m[14])
	{
		Col_Alg[Indice] = 63;
		Indice++;
	}
	
	if (m[ 3] && m[15] )
	{
		Col_Alg[Indice] = 64;
		Indice++;
	}
	
	if (m[ 0])
	{
		Col_Alg[Indice] = 65;
		Indice++;
	}
	
	if (m[ 1])
	{
		Col_Alg[Indice] = 66;
		Indice++;
	}
	
	if (m[ 2])
	{
		Col_Alg[Indice] = 67;
		Indice++;
	}
	
	if (m[ 3])
	{
		Col_Alg[Indice] = 68;
		Indice++;
	}
	
	if (m[ 4])
	{
		Col_Alg[Indice] = 69;
		Indice++;
	}
	
	if (m[ 5])
	{
		Col_Alg[Indice] = 70;
		Indice++;
	}
	
	if (m[ 6])
	{
		Col_Alg[Indice] = 71;
		Indice++;
	}
	
	if (m[ 7])
	{
		Col_Alg[Indice] = 72;
		Indice++;
	}
	
	if (m[ 8])
	{
		Col_Alg[Indice] = 73;
		Indice++;
	}
	
	if (m[ 9])
	{
		Col_Alg[Indice] = 74;
		Indice++;
	}
	
	if (m[10])
	{
		Col_Alg[Indice] = 75;
		Indice++;
	}
	
	if (m[11])
	{
		Col_Alg[Indice] = 76;
		Indice++;
	}
	
	if (m[12])
	{
		Col_Alg[Indice] = 77;
		Indice++;
	}
	
	if (m[13])
	{
		Col_Alg[Indice] = 78;
		Indice++;
	}
	
	if (m[14])
	{
		Col_Alg[Indice] = 79;
		Indice++;
	}
	
	if (m[15])
	{
		Col_Alg[Indice] = 80;
		Indice++;
	}
}
	//fin Arma todos los grupos
	int Col_AlgNue[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
	int IndiceNue = 0;
	
	for(int i = 0; i<81;i++)
	{
		if(Col_AlgNue[i] == -1)
		{
			Alterar(Col_Alg[i], &Col_Alg[0], &Col_AlgNue[0]);
			IndiceNue += 1;
		}
	}
	IndiceNue = 0;
	for(int i = 0; i<81;i++)
	{
		if(Col_AlgNue[i] != -1)
		{
			col[Col_AlgNue[i]].boo = true;
		}
		
	}
	//Siguiente algoritmo
	bool continua = true;
    while(continua)
	{
    	MarcaColeccion(&col[0]);
        continua = GruRedun(&col[0]);
	}
	// fin siguiente algoritmo
	for (int i = 0;i<81;i++)
	{// En esta parte solo paso de un array al otro array que es quien en realidad es visible desde afuera de este metodo
		if (col[i].can != -1)
		{
			*arr =  col[i].num;
			arr++; 
		}
	}
}
bool GruRedun(Coleccion *col_)
{
	for(int i = 0;i<81;i++)
	{
		if (col_->can == 30)
		{
			col_->can = -1;
			col_->boo = false;
			return true;
		}
		col_++;
	}
	return false;
}
int BCGPP(int verd_, Coleccion *col_)
{
	int Acumulador = 0;
	for(int i = 0;i<81;i++)
	{
		if (col_->boo != false)
		{
			for(int j = 0; j < 20 ;j++)
			{
				if (col_->lis[j].pos == verd_)
				{
					Acumulador++;
				}
			}
		}
		col_++; 
	}
	return Acumulador;
}

void MarcaColeccion(Coleccion *col_)
{
	int ListaPos_[81] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; 
	for(int i = 0;i<81;i++)
	{
		BorraMatriz81(&ListaPos_[0]);
		int ind = 0;
		if (col_->boo != false)
		{
			for (int j = 0;j<20;j++){
				if(col_->lis[j].pos != -1){
					col_->lis[j].can = BCGPP(col_->lis[j].pos, &col[0]);
					ListaPos_[ind] = col_->lis[j].can;
					ind++;
				}
			}
			
		}
		bool solouno = false;
		bool masduno = false;
		for( int k = 0;k<20;k++)
		{
			if (ListaPos_[k] != -1)
			{
				if (ListaPos_[k] == 1)
				{
					solouno = true;
				}
				else if(ListaPos_[k] != 1)
				{
					masduno = true;
				}
				
			}
		}
		if (solouno && masduno){//Existe almenos un verdadero que pertenece a una coleccion
			col_->can = 10;
		}else if (solouno && !masduno){//Todos los verdaderos pertenecen a una coleccion
			col_->can = 20;
		}else if (!solouno && masduno){//Todos los verdaderos pertenecen a mas de una coleccion REDUNDANTE
			col_->can = 30;
		}
		
		col_++; 
	}
}

void Eliminar(int num,int *arr)
{//lo que hace es que encuentra el valor y lo sobreescribe con -1
	for(int i = 0;i < 81;i++){
		if(*arr == num){
			*arr = -1;
			break;
		}
		arr++; 
	}
}

void Alterar(int num,int *arr,int *Lista1)
{//Este metodo esta interno en CaptarColecciones
	if(num == 0)
	{//Agrega el valor correspondiente y elimina todas las colecciones internas
	    Agregar(num, &Lista1[0]); // ELIMINA LOS GRUPOS INTERNOS  
	    Eliminar(0, &arr[0]);Eliminar(1, &arr[0]);Eliminar(2, &arr[0]);Eliminar(3, &arr[0]);Eliminar(4, &arr[0]);Eliminar(5, &arr[0]);Eliminar(6, &arr[0]);Eliminar(7, &arr[0]);Eliminar(8, &arr[0]);Eliminar(9, &arr[0]);Eliminar(10, &arr[0]);Eliminar(11, &arr[0]);Eliminar(12, &arr[0]);Eliminar(13, &arr[0]);Eliminar(14, &arr[0]);Eliminar(15, &arr[0]);Eliminar(16, &arr[0]);Eliminar(17, &arr[0]);Eliminar(18, &arr[0]);Eliminar(19, &arr[0]);Eliminar(20, &arr[0]);Eliminar(21, &arr[0]);Eliminar(22, &arr[0]);Eliminar(23, &arr[0]);Eliminar(24, &arr[0]);Eliminar(25, &arr[0]);Eliminar(26, &arr[0]);Eliminar(27, &arr[0]);Eliminar(28, &arr[0]);Eliminar(29, &arr[0]);Eliminar(30, &arr[0]);Eliminar(31, &arr[0]);Eliminar(32, &arr[0]);Eliminar(33, &arr[0]);Eliminar(34, &arr[0]);Eliminar(35, &arr[0]);Eliminar(36, &arr[0]);Eliminar(37, &arr[0]);Eliminar(38, &arr[0]);Eliminar(39, &arr[0]);Eliminar(40, &arr[0]);Eliminar(41, &arr[0]);Eliminar(42, &arr[0]);Eliminar(43, &arr[0]);Eliminar(44, &arr[0]);Eliminar(45, &arr[0]);Eliminar(46, &arr[0]);Eliminar(47, &arr[0]);Eliminar(48, &arr[0]);Eliminar(49, &arr[0]);Eliminar(50, &arr[0]);Eliminar(51, &arr[0]);Eliminar(52, &arr[0]);Eliminar(53, &arr[0]);Eliminar(54, &arr[0]);Eliminar(55, &arr[0]);Eliminar(56, &arr[0]);Eliminar(57, &arr[0]);Eliminar(58, &arr[0]);Eliminar(59, &arr[0]);Eliminar(60, &arr[0]);Eliminar(61, &arr[0]);Eliminar(62, &arr[0]);Eliminar(63, &arr[0]);Eliminar(64, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(81, &arr[0]);Eliminar(82, &arr[0]);Eliminar(83, &arr[0]);Eliminar(84, &arr[0]);
	    goto Retorna;//Para no ejecutar los demas if y salte mediante el for externo a este metodo eficiente pero asi estan las cosas
	}
	if(num == 1)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(1,&arr[0]);Eliminar(9, &arr[0]);Eliminar(10, &arr[0]);Eliminar(17, &arr[0]);Eliminar(18, &arr[0]);Eliminar(19, &arr[0]);Eliminar(20, &arr[0]);Eliminar(33, &arr[0]);Eliminar(34, &arr[0]);Eliminar(35, &arr[0]);Eliminar(36, &arr[0]);Eliminar(37, &arr[0]);Eliminar(38, &arr[0]);Eliminar(39, &arr[0]);Eliminar(40, &arr[0]);Eliminar(49, &arr[0]);Eliminar(50, &arr[0]);Eliminar(51, &arr[0]);Eliminar(52, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(81, &arr[0]);Eliminar(82, &arr[0]);Eliminar(83, &arr[0]);Eliminar(84, &arr[0]);
	    goto Retorna;
	    
	}
	if(num == 2)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(2, &arr[0]);Eliminar(10, &arr[0]);Eliminar(11, &arr[0]);Eliminar(21, &arr[0]);Eliminar(22, &arr[0]);Eliminar(23, &arr[0]);Eliminar(24, &arr[0]);Eliminar(37, &arr[0]);Eliminar(38, &arr[0]);Eliminar(39, &arr[0]);Eliminar(40, &arr[0]);Eliminar(41, &arr[0]);Eliminar(42, &arr[0]);Eliminar(43, &arr[0]);Eliminar(44, &arr[0]);Eliminar(53, &arr[0]);Eliminar(54, &arr[0]);Eliminar(55, &arr[0]);Eliminar(56, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(85, &arr[0]);Eliminar(86, &arr[0]);Eliminar(87, &arr[0]);Eliminar(88, &arr[0]);
	    goto Retorna;
	}
	if(num == 3)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(3, &arr[0]);Eliminar(11, &arr[0]);Eliminar(12, &arr[0]);Eliminar(25, &arr[0]);Eliminar(26, &arr[0]);Eliminar(27, &arr[0]);Eliminar(28, &arr[0]);Eliminar(41, &arr[0]);Eliminar(42, &arr[0]);Eliminar(43, &arr[0]);Eliminar(44, &arr[0]);Eliminar(45, &arr[0]);Eliminar(46, &arr[0]);Eliminar(47, &arr[0]);Eliminar(48, &arr[0]);Eliminar(57, &arr[0]);Eliminar(58, &arr[0]);Eliminar(59, &arr[0]);Eliminar(60, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(89, &arr[0]);Eliminar(90, &arr[0]);Eliminar(91, &arr[0]);Eliminar(92, &arr[0]);
	    goto Retorna;
	}
	if(num == 4)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(4, &arr[0]);Eliminar(9, &arr[0]);Eliminar(12, &arr[0]);Eliminar(29, &arr[0]);Eliminar(30, &arr[0]);Eliminar(31, &arr[0]);Eliminar(32, &arr[0]);Eliminar(33, &arr[0]);Eliminar(34, &arr[0]);Eliminar(35, &arr[0]);Eliminar(36, &arr[0]);Eliminar(45, &arr[0]);Eliminar(46, &arr[0]);Eliminar(47, &arr[0]);Eliminar(48, &arr[0]);Eliminar(61, &arr[0]);Eliminar(62, &arr[0]);Eliminar(63, &arr[0]);Eliminar(64, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(93, &arr[0]);Eliminar(94, &arr[0]);Eliminar(95, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 5)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(5, &arr[0]);Eliminar(13, &arr[0]);Eliminar(14, &arr[0]);Eliminar(17, &arr[0]);Eliminar(21, &arr[0]);Eliminar(25, &arr[0]);Eliminar(29, &arr[0]);Eliminar(33, &arr[0]);Eliminar(37, &arr[0]);Eliminar(41, &arr[0]);Eliminar(45, &arr[0]);Eliminar(49, &arr[0]);Eliminar(50, &arr[0]);Eliminar(53, &arr[0]);Eliminar(54, &arr[0]);Eliminar(57, &arr[0]);Eliminar(58, &arr[0]);Eliminar(61, &arr[0]);Eliminar(62, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(81, &arr[0]);Eliminar(82, &arr[0]);Eliminar(85, &arr[0]);Eliminar(86, &arr[0]);Eliminar(89, &arr[0]);Eliminar(90, &arr[0]);Eliminar(93, &arr[0]);Eliminar(94, &arr[0]);
	    goto Retorna;
	}
	if(num == 6)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(6, &arr[0]);Eliminar(14, &arr[0]);Eliminar(15, &arr[0]);Eliminar(18, &arr[0]);Eliminar(22, &arr[0]);Eliminar(26, &arr[0]);Eliminar(30, &arr[0]);Eliminar(34, &arr[0]);Eliminar(38, &arr[0]);Eliminar(42, &arr[0]);Eliminar(46, &arr[0]);Eliminar(50, &arr[0]);Eliminar(51, &arr[0]);Eliminar(54, &arr[0]);Eliminar(55, &arr[0]);Eliminar(58, &arr[0]);Eliminar(59, &arr[0]);Eliminar(62, &arr[0]);Eliminar(63, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(82, &arr[0]);Eliminar(83, &arr[0]);Eliminar(86, &arr[0]);Eliminar(87, &arr[0]);Eliminar(90, &arr[0]);Eliminar(91, &arr[0]);Eliminar(94, &arr[0]);Eliminar(95, &arr[0]);
	    goto Retorna;
	}
	if(num == 7)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(7, &arr[0]);Eliminar(15, &arr[0]);Eliminar(16, &arr[0]);Eliminar(19, &arr[0]);Eliminar(23, &arr[0]);Eliminar(27, &arr[0]);Eliminar(31, &arr[0]);Eliminar(35, &arr[0]);Eliminar(39, &arr[0]);Eliminar(43, &arr[0]);Eliminar(47, &arr[0]);Eliminar(51, &arr[0]);Eliminar(52, &arr[0]);Eliminar(55, &arr[0]);Eliminar(56, &arr[0]);Eliminar(59, &arr[0]);Eliminar(60, &arr[0]);Eliminar(63, &arr[0]);Eliminar(64, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(83, &arr[0]);Eliminar(84, &arr[0]);Eliminar(87, &arr[0]);Eliminar(88, &arr[0]);Eliminar(91, &arr[0]);Eliminar(92, &arr[0]);Eliminar(95, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 8)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(8, &arr[0]);Eliminar(13, &arr[0]);Eliminar(16, &arr[0]);Eliminar(20, &arr[0]);Eliminar(24, &arr[0]);Eliminar(28, &arr[0]);Eliminar(32, &arr[0]);Eliminar(36, &arr[0]);Eliminar(40, &arr[0]);Eliminar(44, &arr[0]);Eliminar(48, &arr[0]);Eliminar(49, &arr[0]);Eliminar(52, &arr[0]);Eliminar(53, &arr[0]);Eliminar(56, &arr[0]);Eliminar(57, &arr[0]);Eliminar(60, &arr[0]);Eliminar(61, &arr[0]);Eliminar(64, &arr[0]);Eliminar(65, &arr[0]);Eliminar(68, &arr[0]);Eliminar(69, &arr[0]);Eliminar(72, &arr[0]);Eliminar(73, &arr[0]);Eliminar(76, &arr[0]);Eliminar(77, &arr[0]);Eliminar(80, &arr[0]);Eliminar(81, &arr[0]);Eliminar(84, &arr[0]);Eliminar(85, &arr[0]);Eliminar(88, &arr[0]);Eliminar(89, &arr[0]);Eliminar(92, &arr[0]);Eliminar(93, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 9)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(9, &arr[0]);Eliminar(33, &arr[0]);Eliminar(34, &arr[0]);Eliminar(35, &arr[0]);Eliminar(36, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);
	    goto Retorna;
	}
	if(num == 10)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(10, &arr[0]);Eliminar(37, &arr[0]);Eliminar(38, &arr[0]);Eliminar(39, &arr[0]);Eliminar(40, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);
	    goto Retorna;
	}
	if(num == 11)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(11, &arr[0]);Eliminar(41, &arr[0]);Eliminar(42, &arr[0]);Eliminar(43, &arr[0]);Eliminar(44, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);
	    goto Retorna;
	}
	if(num == 12)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(12, &arr[0]);Eliminar(45, &arr[0]);Eliminar(46, &arr[0]);Eliminar(47, &arr[0]);Eliminar(48, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);
	    goto Retorna;
	}
	if(num == 13)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(13, &arr[0]);Eliminar(49, &arr[0]);Eliminar(53, &arr[0]);Eliminar(57, &arr[0]);Eliminar(61, &arr[0]);Eliminar(65, &arr[0]);Eliminar(69, &arr[0]);Eliminar(73, &arr[0]);Eliminar(77, &arr[0]);Eliminar(81, &arr[0]);Eliminar(85, &arr[0]);Eliminar(89, &arr[0]);Eliminar(93, &arr[0]);
	    goto Retorna;
	}
	if(num == 14)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(14, &arr[0]);Eliminar(50, &arr[0]);Eliminar(54, &arr[0]);Eliminar(58, &arr[0]);Eliminar(62, &arr[0]);Eliminar(66, &arr[0]);Eliminar(70, &arr[0]);Eliminar(74, &arr[0]);Eliminar(78, &arr[0]);Eliminar(82, &arr[0]);Eliminar(86, &arr[0]);Eliminar(90, &arr[0]);Eliminar(94, &arr[0]);
	    goto Retorna;
	}
	if(num == 15)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(15, &arr[0]);Eliminar(51, &arr[0]);Eliminar(55, &arr[0]);Eliminar(59, &arr[0]);Eliminar(63, &arr[0]);Eliminar(67, &arr[0]);Eliminar(71, &arr[0]);Eliminar(75, &arr[0]);Eliminar(79, &arr[0]);Eliminar(83, &arr[0]);Eliminar(87, &arr[0]);Eliminar(91, &arr[0]);Eliminar(95, &arr[0]);
	    goto Retorna;
	}
	if(num == 16)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(16, &arr[0]);Eliminar(52, &arr[0]);Eliminar(56, &arr[0]);Eliminar(60, &arr[0]);Eliminar(64, &arr[0]);Eliminar(68, &arr[0]);Eliminar(72, &arr[0]);Eliminar(76, &arr[0]);Eliminar(80, &arr[0]);Eliminar(84, &arr[0]);Eliminar(88, &arr[0]);Eliminar(92, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 17)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(17, &arr[0]);Eliminar(33, &arr[0]);Eliminar(37, &arr[0]);Eliminar(49, &arr[0]);Eliminar(50, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(81, &arr[0]);Eliminar(82, &arr[0]);
	    goto Retorna;
	}
	if(num == 18)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(18, &arr[0]);Eliminar(34, &arr[0]);Eliminar(38, &arr[0]);Eliminar(50, &arr[0]);Eliminar(51, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(82, &arr[0]);Eliminar(83, &arr[0]);
	    goto Retorna;
	}
	if(num == 19)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(19, &arr[0]);Eliminar(35, &arr[0]);Eliminar(39, &arr[0]);Eliminar(51, &arr[0]);Eliminar(52, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(83, &arr[0]);Eliminar(84, &arr[0]);
	    goto Retorna;
	}
	if(num == 20)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(20, &arr[0]);Eliminar(36, &arr[0]);Eliminar(40, &arr[0]);Eliminar(49, &arr[0]);Eliminar(52, &arr[0]);Eliminar(65, &arr[0]);Eliminar(68, &arr[0]);Eliminar(69, &arr[0]);Eliminar(72, &arr[0]);Eliminar(81, &arr[0]);Eliminar(84, &arr[0]);
	    goto Retorna;
	}
	if(num == 21)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(21, &arr[0]);Eliminar(37, &arr[0]);Eliminar(41, &arr[0]);Eliminar(53, &arr[0]);Eliminar(54, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(85, &arr[0]);Eliminar(86, &arr[0]);
	    goto Retorna;
	}
	if(num == 22)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(22, &arr[0]);Eliminar(38, &arr[0]);Eliminar(42, &arr[0]);Eliminar(54, &arr[0]);Eliminar(55, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(86, &arr[0]);Eliminar(87, &arr[0]);
	    goto Retorna;
	}
	if(num == 23)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(23, &arr[0]);Eliminar(39, &arr[0]);Eliminar(43, &arr[0]);Eliminar(55, &arr[0]);Eliminar(56, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(87, &arr[0]);Eliminar(88, &arr[0]);
	    goto Retorna;
	}
	if(num == 24)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(24, &arr[0]);Eliminar(40, &arr[0]);Eliminar(44, &arr[0]);Eliminar(53, &arr[0]);Eliminar(56, &arr[0]);Eliminar(69, &arr[0]);Eliminar(72, &arr[0]);Eliminar(73, &arr[0]);Eliminar(76, &arr[0]);Eliminar(85, &arr[0]);Eliminar(88, &arr[0]);
	    goto Retorna;
	}
	if(num == 25)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(25, &arr[0]);Eliminar(41, &arr[0]);Eliminar(45, &arr[0]);Eliminar(57, &arr[0]);Eliminar(58, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(89, &arr[0]);Eliminar(90, &arr[0]);
	    goto Retorna;
	}
	if(num == 26)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(26, &arr[0]);Eliminar(42, &arr[0]);Eliminar(46, &arr[0]);Eliminar(58, &arr[0]);Eliminar(59, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(90, &arr[0]);Eliminar(91, &arr[0]);
	    goto Retorna;
	}
	if(num == 27)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(27, &arr[0]);Eliminar(43, &arr[0]);Eliminar(47, &arr[0]);Eliminar(59, &arr[0]);Eliminar(60, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(91, &arr[0]);Eliminar(92, &arr[0]);
	    goto Retorna;
	}
	if(num == 28)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(28, &arr[0]);Eliminar(44, &arr[0]);Eliminar(48, &arr[0]);Eliminar(57, &arr[0]);Eliminar(60, &arr[0]);Eliminar(73, &arr[0]);Eliminar(76, &arr[0]);Eliminar(77, &arr[0]);Eliminar(80, &arr[0]);Eliminar(89, &arr[0]);Eliminar(92, &arr[0]);
	    goto Retorna;
	}
	if(num == 29)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(29, &arr[0]);Eliminar(33, &arr[0]);Eliminar(45, &arr[0]);Eliminar(61, &arr[0]);Eliminar(62, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);Eliminar(93, &arr[0]);Eliminar(94, &arr[0]);
	    goto Retorna;
	}
	if(num == 30)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(30, &arr[0]);Eliminar(34, &arr[0]);Eliminar(46, &arr[0]);Eliminar(62, &arr[0]);Eliminar(63, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);Eliminar(94, &arr[0]);Eliminar(95, &arr[0]);
	    goto Retorna;
	}
	if(num == 31)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(31, &arr[0]);Eliminar(35, &arr[0]);Eliminar(47, &arr[0]);Eliminar(63, &arr[0]);Eliminar(64, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);Eliminar(95, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 32)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(32, &arr[0]);Eliminar(36, &arr[0]);Eliminar(48, &arr[0]);Eliminar(61, &arr[0]);Eliminar(64, &arr[0]);Eliminar(65, &arr[0]);Eliminar(68, &arr[0]);Eliminar(77, &arr[0]);Eliminar(80, &arr[0]);Eliminar(93, &arr[0]);Eliminar(96, &arr[0]);
	    goto Retorna;
	}
	if(num == 33)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(33, &arr[0]);Eliminar(65, &arr[0]);Eliminar(66, &arr[0]);
	    goto Retorna;
	}
	if(num == 34)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(34, &arr[0]);Eliminar(66, &arr[0]);Eliminar(67, &arr[0]);
	    goto Retorna;
	}
	if(num == 35)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(35, &arr[0]);Eliminar(67, &arr[0]);Eliminar(68, &arr[0]);
	    goto Retorna;
	}
	if(num == 36)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(36, &arr[0]);Eliminar(65, &arr[0]);Eliminar(68, &arr[0]);
	    goto Retorna;
	}
	if(num == 37)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(37, &arr[0]);Eliminar(69, &arr[0]);Eliminar(70, &arr[0]);
	    goto Retorna;
	}
	if(num == 38)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(38, &arr[0]);Eliminar(70, &arr[0]);Eliminar(71, &arr[0]);
	    goto Retorna;
	}
	if(num == 39)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(39, &arr[0]);Eliminar(71, &arr[0]);Eliminar(72, &arr[0]);
	    goto Retorna;
	}
	if(num == 40)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(40, &arr[0]);Eliminar(69, &arr[0]);Eliminar(72, &arr[0]);
	    goto Retorna;
	}
	if(num == 41)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(41, &arr[0]);Eliminar(73, &arr[0]);Eliminar(74, &arr[0]);
	    goto Retorna;
	}
	if(num == 42)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(42, &arr[0]);Eliminar(74, &arr[0]);Eliminar(75, &arr[0]);
	    goto Retorna;
	}
	if(num == 43)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(43, &arr[0]);Eliminar(75, &arr[0]);Eliminar(76, &arr[0]);
	    goto Retorna;
	}
	if(num == 44)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(44, &arr[0]);Eliminar(73, &arr[0]);Eliminar(76, &arr[0]);
	    goto Retorna;
	}
	if(num == 45)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(45, &arr[0]);Eliminar(77, &arr[0]);Eliminar(78, &arr[0]);
	    goto Retorna;
	}
	if(num == 46)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(46, &arr[0]);Eliminar(78, &arr[0]);Eliminar(79, &arr[0]);
	    goto Retorna;
	}
	if(num == 47)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(47, &arr[0]);Eliminar(79, &arr[0]);Eliminar(80, &arr[0]);
	    goto Retorna;
	}
	if(num == 48)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(48, &arr[0]);Eliminar(77, &arr[0]);Eliminar(80, &arr[0]);
	    goto Retorna;
	}
	if(num == 49)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(49, &arr[0]);Eliminar(65, &arr[0]);Eliminar(69, &arr[0]);
	    goto Retorna;
	}
	if(num == 50)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(50, &arr[0]);Eliminar(66, &arr[0]);Eliminar(70, &arr[0]);
	    goto Retorna;
	}
	if(num == 51)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(51, &arr[0]);Eliminar(67, &arr[0]);Eliminar(71, &arr[0]);
	    goto Retorna;
	}
	if(num == 52)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(52, &arr[0]);Eliminar(68, &arr[0]);Eliminar(72, &arr[0]);
	    goto Retorna;
	}
	if(num == 53)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(53, &arr[0]);Eliminar(69, &arr[0]);Eliminar(73, &arr[0]);
	    goto Retorna;
	}
	if(num == 54)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(54, &arr[0]);Eliminar(70, &arr[0]);Eliminar(74, &arr[0]);
	    goto Retorna;
	}
	if(num == 55)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(55, &arr[0]);Eliminar(71, &arr[0]);Eliminar(75, &arr[0]);
	    goto Retorna;
	}
	if(num == 56)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(56, &arr[0]);Eliminar(72, &arr[0]);Eliminar(76, &arr[0]);
	    goto Retorna;
	}
	if(num == 57)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(57, &arr[0]);Eliminar(73, &arr[0]);Eliminar(77, &arr[0]);
	    goto Retorna;
	}
	if(num == 58)
	{
	    Agregar(num,&Lista1[0]);
	    Eliminar(58, &arr[0]);Eliminar(74, &arr[0]);Eliminar(78, &arr[0]);
	    goto Retorna;
	}
	if(num == 59)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(59, &arr[0]);Eliminar(75, &arr[0]);Eliminar(79, &arr[0]);
	    goto Retorna;
	}
	if(num == 60)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(60, &arr[0]);Eliminar(76, &arr[0]);Eliminar(80, &arr[0]);
	    goto Retorna;
	}
	if(num == 61)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(61, &arr[0]);Eliminar(65, &arr[0]);Eliminar(77, &arr[0]);
	    goto Retorna;
	}
	if(num == 62)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(62, &arr[0]);Eliminar(66, &arr[0]);Eliminar(78, &arr[0]);
	    goto Retorna;
	}
	if(num == 63)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(63, &arr[0]);Eliminar(67, &arr[0]);Eliminar(79, &arr[0]);
	    goto Retorna;
	}
	if(num == 64)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(64, &arr[0]);Eliminar(68, &arr[0]);Eliminar(80, &arr[0]);
	    goto Retorna;
	}
	if(num == 65)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(65, &arr[0]);
	    goto Retorna;
	}
	if(num == 66)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(66, &arr[0]);
	    goto Retorna;
	}
	if(num == 67)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(67, &arr[0]);
	    goto Retorna;
	}
	if(num == 68)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(68, &arr[0]);
	    goto Retorna;
	}
	if(num == 69)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(69, &arr[0]);
	    goto Retorna;
	}
	if(num == 70)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(70, &arr[0]);
	    goto Retorna;
	}
	if(num == 71)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(71, &arr[0]);
	    goto Retorna;
	}
	if(num == 72)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(72, &arr[0]);
	    goto Retorna;
	}
	if(num == 73)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(73, &arr[0]);
	    goto Retorna;
	}
	if(num == 74)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(74, &arr[0]);
	    goto Retorna;
	}
	if(num == 75)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(75, &arr[0]);
	    goto Retorna;
	}
	if(num == 76)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(76, &arr[0]);
	    goto Retorna;
	}
	if(num == 77)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(77, &arr[0]);
	    goto Retorna;
	}
	if(num == 78)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(78, &arr[0]);
	    goto Retorna;
	}
	if(num == 79)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(79, &arr[0]);
	    goto Retorna;
	}
	if(num == 80)
	{
	    Agregar(num, &Lista1[0]);
	    Eliminar(80, &arr[0]);
	    goto Retorna;
	}
Retorna:;
}
void Agregar(int num, int *arr)//Agrega un valor al final de un array tipo int
{
	for(int i = 0;i < 81;i++)
	{
		if(*arr == -1)
		{
			*arr = num;
			break;
		}
		arr++; 
	}
}




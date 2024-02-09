#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;
void imprimir_encabezado();
void imprimir_cuerpo(char);
void imprimir_fooder();
void imprimir_tabla(char, int, int , int);
void iniciar();
void generar_minas();
int verificar_minas(int, int);
char matriz[6][6];
char matrizB[6][6];
char continuar='S';
int pandera=8;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int main() {
    iniciar();
    return 0;
}

void imprimir_tabla(char caracter, int tamano, int posicionx, int posiciony, int tipo) {
    bool estado=false;
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    for(int columna=0; columna<tamano;columna++) {
        for (int i = 0; i < tamano; i++) {
            cout<<columna+1<<" "<<i+1;
            imprimir_encabezado();
        }
        printf("\n");
        for (int fila = 0; fila < tamano; fila++) {
            cout<<"   ";
            if(tipo==2 ){
                matrizB[posiciony][posicionx]='P';
                matriz[posiciony][posicionx]='P';
                pandera++;
            }

            if(matrizB[posiciony][posicionx]=='*'){
                continuar='N';
                estado=true;
                imprimir_cuerpo(matriz[columna][fila]);
            }
            else{
                matrizB[posiciony][posicionx]= matriz[posiciony][posicionx];
                if(matrizB[columna][fila]!='*'){
                    imprimir_cuerpo(matrizB[columna][fila]);
                }
                else if(matrizB[columna][fila]=='0'){
                    int colum=columna;
                    int fil=fila;
                    for(columna-1;columna<=colum+1;columna++){
                        for(fila-1;fila<=fil;fila++){
                            matrizB[columna][fila]='0';
                        }
                    }
                }
                else {
                    imprimir_cuerpo(' ');
                }
            }
        }
        printf("\n");
        for (int m = 0; m < tamano; m++) {
            cout<<"   ";
            imprimir_fooder();
        }
        printf("\n");
    }
    if(estado==true){
        cout<<"Game Over!!!   "<<"En la fila: "<<posiciony+1<<" y en la columna: "<<posicionx+1<<" existia una mina";
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void imprimir_encabezado(){
    printf("%c", 201);
    printf("%c", 205);
    printf("%c", 205);
    printf("%c", 205);
    printf("%c", 187);
    printf(" ");
}
void imprimir_cuerpo(char caracter){
    printf("%c", 186);
    printf(" ");
    if(caracter=='*'){
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED);
        printf("%c",caracter);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED| FOREGROUND_RED| FOREGROUND_BLUE);
    }
    else{
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("%c", caracter);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN| FOREGROUND_RED| FOREGROUND_BLUE);
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf(" ");
    printf("%c", 186);
    printf(" ");
}

void imprimir_fooder(){
    printf("%c", 200);
    printf("%c", 205);
    printf("%c", 205);
    printf("%c", 205);
    printf("%c", 188);
    printf(" ");
}

void generar_minas() {
    srand(time(NULL));
    int fila_aleatorio;
    int columna_aleatorio;
    for(int i=0;i<8;i++){
        fila_aleatorio = rand() % 6;
        columna_aleatorio = rand() % 6;
        if( matriz[fila_aleatorio][columna_aleatorio]=='*'){
            i=i-1;
        }
        else{
            matriz[fila_aleatorio][columna_aleatorio]='*';
            matrizB[fila_aleatorio][columna_aleatorio]='*';
        }
        //cout<<"indice "<<i<<"  fila "<<fila_aleatorio<<"  columna  "<<columna_aleatorio<<"   " <<matriz[fila_aleatorio][columna_aleatorio]<<endl;
    }
    for(int y=0; y< size(matriz); y++){
        for(int x=0; x< size(matriz); x++){
            if(matriz[y][x]!='*'){
                matriz[y][x]='0'+  verificar_minas(x,y);
            }
        }
    }
}
int verificar_minas(int fila, int columna){
    int numero_minas=0;
    int fila_inicio, fila_final, columna_inicio, columna_final;
    columna_final = columna + 1;
    columna_inicio = columna - 1;
    fila_final = fila + 1;
    fila_inicio = fila - 1;
    for (columna_inicio; columna_inicio <= columna_final; columna_inicio++) {
        int fila_inicio_actual = fila_inicio; // Guarda el valor inicial de fila_inicio
        int fila_final_actual = fila_final; // Guarda el valor inicial de fila_final
        for (fila_inicio_actual; fila_inicio_actual <= fila_final_actual; fila_inicio_actual++) {
            if(matriz[columna_inicio][fila_inicio_actual]=='*'){
                numero_minas++;
            }
        }
    }
    return numero_minas;
}

void iniciar(){
    cout << "Bien venido al juego de Busca Minas" <<endl;
    generar_minas();
    int posicionx;
    int posiciony;
    int tipo;
   imprimir_tabla('X', 6, 7, 7,1);
    while(continuar=='S') {
        cout<<"Insertar numero de fila: ";
        cin >>posiciony;
        if(posiciony>6){
            cout<<"Insertar numero  menor o igual a 6: ";
            cin >>posiciony;
        }
        else{
            cout<<"Insertar numero de columna: ";
            cin >>posicionx;
            if(posicionx<=6){
                cout<<"desea ingresar una bandera Si 2, No 1:  ";
                cin>>tipo;
                cout<<endl;
                imprimir_tabla('x', 6, posicionx-1, posiciony-1,tipo);
            }
            else {
                cout<<"Insertar numero  menor o igual a 6: ";
                cin >>posicionx;
            }
        }
    }
}


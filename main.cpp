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
int contar_minas_adyacentes(int, int);
void actualizar_numeros();
bool matriz_llena();
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
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            int nx = columna + dx;
                            int ny = fila + dy;
                            if (nx >= 0 && nx < tamano && ny >= 0 && ny < tamano && matrizB[nx][ny] == '0') {
                                matrizB[nx][ny] = matriz[nx][ny];
                                imprimir_cuerpo(matrizB[nx][ny]);
                            }
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
    else {
        if( matriz_llena()==true){
            cout<<"A GANADO USTED ES UN CRACK!!!!!";
            continuar='N';
        }
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
    actualizar_numeros();
}

void iniciar() {
    cout << "Bienvenido al juego de Busca Minas" << endl;
    generar_minas();
    int posicionx;
    int posiciony;
    int tipo;
    imprimir_tabla('X', 6, 7, 7, 1);
    while (continuar == 'S') {
        cout << "Insertar numero de fila (1-6): ";
        cin >> posiciony;
        while (posiciony < 1 || posiciony > 6) {
            cout << "Numero fuera de rango. Insertar numero de fila (1-6): ";
            cin >> posiciony;
        }
        cout << "Insertar numero de columna (1-6): ";
        cin >> posicionx;
        while (posicionx < 1 || posicionx > 6) {
            cout << "Numero fuera de rango. Insertar número de columna (1-6): ";
            cin >> posicionx;
        }
        cout << "Desea ingresar una bandera? (Si: 2, No: 1): ";
        cin >> tipo;
        cout<<endl;
        while(tipo>2 || tipo<1){
            cout << "Desea ingresar una bandera? (Si: 2, No: 1): ";
            cin >> tipo;
            cout<<endl;
        }
        imprimir_tabla('x', 6, posicionx - 1, posiciony - 1, tipo);
    }
}

void actualizar_numeros() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j <6; j++) {
            if (matriz[i][j] != '*') {
                int num_minas = contar_minas_adyacentes(i, j);
                matriz[i][j] = num_minas + '0'; // Convertir el número a carácter
            }
        }
    }
}

int contar_minas_adyacentes(int fila, int columna) {
    int contador = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = fila + dx;
            int ny = columna + dy;
            if (nx >= 0 && nx < 6 && ny >= 0 && ny <6) {
                if (matriz[nx][ny] == '*') {
                    contador++;
                }
            }
        }
    }
    return contador;
}
bool matriz_llena() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (matrizB[i][j] == ' ') { // Si hay al menos una posición vacía, la matriz no está llena
                return true;
            }
        }
    }
    return false; // Si no se encontró ninguna posición vacía, la matriz está llena
}

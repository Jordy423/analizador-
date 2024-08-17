#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

#define TAM_BUFFER 1024

class Lexico {
    char *nombreFichero;
    FILE* entrada;
    int n1;
    int traza;
    char buffer[TAM_BUFFER];
    int pBuffer;
public:
    Lexico(char *unNombreFichero, int una_traza = 0);
    ~Lexico(void);
    char siguienteToken(void);
    void devuelveToken(char token);
    int lineaActual(void) { return n1; }
    int existeTraza(void) { return traza ? 1 : 0; }
};

Lexico::Lexico(char *unNombreFichero, int una_traza) {
    entrada = fopen(unNombreFichero, "rt");
    if (entrada == NULL) {
        cout << "No se puede abrir el archivo" << endl;
        system("pause");
        exit(-2);
    }
    traza = una_traza ? 1 : 0;
    n1 = 1;
    pBuffer = 0;
}

Lexico::~Lexico() {
    fclose(entrada);
}

char Lexico::siguienteToken(void) {
    char car;
    while ((car = ((pBuffer > 0) ? buffer[--pBuffer] : getc(entrada))) != EOF) {
        if (car == ' ') continue;
        if (car == '\n') { ++n1; continue; }
        break;
    }
    if (traza) cout << "ANALIZADOR LEXICO: Lee el token : " << car << endl;
    switch (car) {
        case 'M':
        case 'R':
        case 'W':
        case '=':
        case '(':
        case ')':
        case ';':
        case '}':
        case '{':
        case '.':
        case '+':
        case '*':
        case '-':
        case '/':
        case '%':
            return car;
    }
    if (islower(car)) return car;
    else if (isdigit(car)) return car;
    else {
        cout << "Error Lexico: Token Desconocido" << endl;
        system("pause");
        exit(-4);
    }
    return car;
}

void Lexico::devuelveToken(char token) {
    if (pBuffer >= TAM_BUFFER) {
        cout << "ERROR: Desbordamiento del buffer del analizador lexico" << endl;
        system("pause");
        exit(-5);
    } else {
        buffer[pBuffer++] = token;
        if (existeTraza()) {
            cout << "ANALIZADOR LEXICO: Recibe en buffer el token" << token << endl;
            system("pause");
        }
    }
}

int main() {
    int traza;
    char token;
   Lexico obj("C:\\Jordy\\Documents\\minidev.txt", 1);
    if (obj.existeTraza()) {
        cout << "INICIO DE ANALISIS" << endl;
    }
    while ((token = obj.siguienteToken()) != '}') {
        cout << token << endl;
    }
    system("pause");
    return 0;
}

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <fstream>

using namespace std;

struct Nodo{
    long long int DPI;
    string nombre;
    int vacunas;
    string vacuna1;
    string vacuna2;
    string vacuna3;
    string departamento;
    string Municipio;
    string LugarVacuna;
    int altura;
    Nodo *der;
    Nodo *izq;
    Nodo *padre;
};

Nodo *arbol = NULL;
Nodo *padre;
int aux;
int auxX=0;
int auxY=0;
int buscado;
void eliminarNodo(Nodo *nodoEl);

Nodo *crearNodo(long long int DPI,string Nombre,int vacunas,string vacuna1,string vacuna2,string vacuna3,string municipio,string departamendo,string LugarVacunacion, Nodo *padre){
    Nodo *nuevoNodo= new Nodo();


    nuevoNodo->DPI=DPI;
    nuevoNodo->nombre=Nombre;
    nuevoNodo->vacunas=vacunas;
    nuevoNodo->vacuna1=vacuna1;
    nuevoNodo->vacuna2=vacuna2;
    nuevoNodo->vacuna3=vacuna3;
    nuevoNodo->departamento=departamendo;
    nuevoNodo->Municipio=municipio;
    nuevoNodo->LugarVacuna=LugarVacunacion;
    nuevoNodo->der=NULL;
    nuevoNodo->izq=NULL;
    nuevoNodo->padre=padre;
    nuevoNodo->altura = 0;

    return nuevoNodo;
}
int getAltura(Nodo* nodo) {
    if (nodo == NULL)
        return -1;
    else
        return nodo->altura;
}

int calcularFactorEquilibrio(Nodo* nodo) {
    if (nodo == NULL)
        return 0;
    else
        return getAltura(nodo->izq) - getAltura(nodo->der);
}

void actualizarAltura(Nodo* nodo) {
    nodo->altura = 1 + max(getAltura(nodo->izq), getAltura(nodo->der));
}
Nodo* rotacionIzquierda(Nodo* nodo) {
    Nodo* nuevoPadre = nodo->der;
    nodo->der = nuevoPadre->izq;
    if (nuevoPadre->izq != NULL)
        nuevoPadre->izq->padre = nodo;
    nuevoPadre->izq = nodo;
    nuevoPadre->padre = nodo->padre;
    nodo->padre = nuevoPadre;
    actualizarAltura(nodo);
    actualizarAltura(nuevoPadre);
    return nuevoPadre;
}

Nodo* rotacionDerecha(Nodo* nodo) {
    Nodo* nuevoPadre = nodo->izq;
    nodo->izq = nuevoPadre->der;
    if (nuevoPadre->der != NULL)
        nuevoPadre->der->padre = nodo;
    nuevoPadre->der = nodo;
    nuevoPadre->padre = nodo->padre;
    nodo->padre = nuevoPadre;
    actualizarAltura(nodo);
    actualizarAltura(nuevoPadre);
    return nuevoPadre;
}


void insertarNodo(Nodo*& arbol,long long int DPI,string Nombre,int vacunas,string vacuna1,string vacuna2,string vacuna3,string municipio,string departamendo,string LugarVacunacion, Nodo *padre){
    if (arbol==NULL){
        Nodo* nuevoNodo=crearNodo(DPI,Nombre,vacunas,vacuna1,vacuna2,vacuna3,municipio,departamendo,LugarVacunacion, padre);
        arbol=nuevoNodo;
    }
    else{
        long long int valorRaiz=arbol->DPI;
        if (DPI<valorRaiz){
            insertarNodo(arbol->izq,DPI,Nombre,vacunas,vacuna1,vacuna2,vacuna3,municipio,departamendo,LugarVacunacion, arbol);
        }else {
            insertarNodo(arbol->der,DPI,Nombre,vacunas,vacuna1,vacuna2,vacuna3,municipio,departamendo,LugarVacunacion, arbol);
        }
        actualizarAltura(arbol);
        int factorEquilibrio = calcularFactorEquilibrio(arbol);
        // Caso de rotación izquierda-izquierda
        if (factorEquilibrio > 1 && DPI < arbol->izq->DPI) {
            arbol = rotacionDerecha(arbol);
        }
        // Caso de rotación derecha-derech
        if (factorEquilibrio < -1 && DPI > arbol->der->DPI) {
            arbol = rotacionIzquierda(arbol);
        }
        // Caso de rotación izquierda-derecha
        if (factorEquilibrio > 1 && DPI > arbol->izq->DPI) {
            arbol->izq = rotacionIzquierda(arbol->izq);
            arbol = rotacionDerecha(arbol);
        }
        // Caso de rotación derecha-izquierda
        if (factorEquilibrio < -1 && DPI < arbol->der->DPI) {
            arbol->der = rotacionDerecha(arbol->der);
            arbol = rotacionIzquierda(arbol);
    }
}
}


void modificarDato(Nodo*& arbol, long long int DPI) {
    if (arbol == NULL) {
        cout << "La persona no existe en el árbol." << endl;
        return;
    }

    if (DPI < arbol->DPI) {
        modificarDato(arbol->izq, DPI);
    } else if (DPI > arbol->DPI) {
        modificarDato(arbol->der, DPI);
    } else {
        cout << "Persona encontrada:\n";
        cout << "DPI: " << arbol->DPI << endl;
        cout << "Ingrese los nuevos datos:" << endl;

        cout << "Nombre: ";
        cin.ignore();
        getline(cin, arbol->nombre);

        cout << "Vacunas: ";
        cin >> arbol->vacunas;
        cin.ignore();

        cout << "Vacuna 1: ";
        getline(cin, arbol->vacuna1);

        cout << "Vacuna 2: ";
        getline(cin, arbol->vacuna2);

        cout << "Vacuna 3: ";
        getline(cin, arbol->vacuna3);

        cout << "Departamento: ";
        getline(cin, arbol->departamento);

        cout << "Municipio: ";
        getline(cin, arbol->Municipio);

        cout << "Lugar de Vacunacion: ";
        getline(cin, arbol->LugarVacuna);

        cout << "Los datos de la persona se han modificado correctamente." << endl;
    }
}

bool buscarDato(Nodo* arbol, long long int DPI) {
    if (arbol == NULL) {
        return false;
    } else if (arbol->DPI == DPI) {

        cout << "Nombre: " << arbol->nombre << endl;
        cout << "Vacunas: " << arbol->vacunas << endl;
        cout << "Vacuna 1: " << arbol->vacuna1 << endl;
        cout << "Vacuna 2: " << arbol->vacuna2 << endl;
        cout << "Vacuna 3: " << arbol->vacuna3 << endl;
        cout << "Departamento: " << arbol->departamento << endl;
        cout << "Municipio: " << arbol->Municipio << endl;
        cout << "Lugar de vacunacion: " <<arbol->LugarVacuna<<endl;
        return true;
    } else if (DPI < arbol->DPI) {
        return buscarDato(arbol->izq, DPI);
    } else {
        return buscarDato(arbol->der, DPI);
    }
}

void eliminar(Nodo* arbol, long long int DPI){
	if (arbol==NULL){
		return;
	}else if(DPI<arbol->DPI){
		eliminar(arbol->izq,DPI);
	}else if(DPI>arbol->DPI){
		eliminar(arbol->der,DPI);
	}else{
		eliminarNodo(arbol);
	}
}

Nodo* minimo(Nodo* arbol){
	if(arbol==NULL){
		return NULL;
	}
	if(arbol->izq){
		return minimo(arbol->izq);
	}else{
		return arbol;
	}
}

void cambiar(Nodo* arbol, Nodo* nuevoNodo){
	if(arbol->padre){
		if(arbol->DPI==arbol->padre->izq->DPI){
			arbol->padre->izq=nuevoNodo;
		}else if(arbol->DPI==arbol->padre->der->DPI){
			arbol->padre->der=nuevoNodo;
		}
	}
	if(nuevoNodo){
		nuevoNodo->padre=arbol->padre;
	}
}

void acabarNodo(Nodo* nodo){
	nodo->izq =NULL;
	nodo->der =NULL;
	delete nodo;
}

void eliminarNodo(Nodo* nodoEl){
	if(nodoEl->izq && nodoEl->der){
		Nodo* menor=minimo(nodoEl->der);
		nodoEl->DPI=menor->DPI;
		eliminarNodo(menor);
	}else if(nodoEl->izq){
		cambiar(nodoEl,nodoEl->izq);
		acabarNodo(nodoEl);
	}else if(nodoEl->der){
		cambiar(nodoEl,nodoEl->der);
		acabarNodo(nodoEl);
	}else {
		cambiar(nodoEl,NULL);
		acabarNodo(nodoEl);
	}
}

void pre(Nodo* arbol){
    if (arbol == NULL){
	return;
    } else{
        cout<<arbol->DPI<<endl;
        pre(arbol->izq);
        pre(arbol->der);
        }
}

void in(Nodo* arbol){
    if (arbol == NULL){
	return;
    } else{
        in(arbol->izq);
        cout<<arbol->DPI<<endl;
        in(arbol->der);
        }
}

void post(Nodo* arbol){
    if (arbol == NULL){
	return;
    } else{
        post(arbol->izq);
        post(arbol->der);
        cout<<arbol->DPI<<endl;
        }
}

void encriPre(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        long long int dpi = arbol->DPI;
        string encriptarDPI;
        while (dpi > 0) {
            int digito = dpi % 10;
            digito = (digito + 7) % 10;
            char encriptarDigito = 'A' + digito;
            encriptarDPI = encriptarDigito + encriptarDPI;
            dpi /= 10;
        }
        cout << encriptarDPI << endl;
        encriPre(arbol->izq);
        encriPre(arbol->der);
    }
}


void encriIn(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        encriIn(arbol->izq);
        long long int dpi = arbol->DPI;
        string encriptarDPI;
        while (dpi > 0) {
            int digito = dpi % 10;
            digito = (digito + 7) % 10;
            char encriptarDigito = 'A' + digito;
            encriptarDPI += encriptarDigito;
            dpi /= 10;
        }
        cout << encriptarDPI << endl;
        encriIn(arbol->der);
    }
}
void encriPost(Nodo *arbol) {
    if (arbol == NULL) {
        return;
    } else {
        encriPost(arbol->izq);
        encriPost(arbol->der);
       long long int dpi = arbol->DPI;
       string encriptarDPI;
       while (dpi >0) {
        int digito = dpi % 10;
        digito =(digito + 7) %10;
        char encriptarDigito = 'A' + digito;
        encriptarDPI += encriptarDigito;
        dpi/= 10;
       }
       cout <<encriptarDPI<<endl;
    }
}
void descriPre(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    } else {
        arbol->DPI = arbol->DPI - 7;
        cout << arbol->DPI << endl;
        descriPre(arbol->izq);
        descriPre(arbol->der);
    }
}
void descrIn(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    } else {
        if (arbol->DPI != 0) {
            arbol->DPI = arbol->DPI - 7;
        }

        descrIn(arbol->izq);
        cout << arbol->DPI << endl;
        descrIn(arbol->der);
    }
}
void descriPost(Nodo* arbol) {
    if (arbol == NULL) {
        return;
    } else {
        descriPost(arbol->izq);
        descriPost(arbol->der);

        if (arbol->DPI != 0) {
            arbol->DPI = arbol->DPI - 7;
        }

        cout << arbol->DPI << endl;
    }
}


void gotoxy(int x,int y){
HANDLE hcon;
hcon = GetStdHandle(STD_OUTPUT_HANDLE);
COORD dwPos;
dwPos.X = x;
dwPos.Y= y;
SetConsoleCursorPosition(hcon,dwPos);
}
void mostrarArbolVertical(Nodo*& arbol, int auxY){
    string nombre;

    if(arbol == NULL){

    return;
    }

    nombre=arbol->nombre.substr(0,arbol->nombre.find(' '));
    aux += 5;
    mostrarArbolVertical(arbol -> izq,auxY+6);
    gotoxy(20+aux-auxY , 40+auxY);
    cout << arbol -> DPI<<endl;
    gotoxy(21+aux-auxY , 41+auxY);
    cout<< nombre<<endl<<endl;



    mostrarArbolVertical(arbol -> der,auxY+4);

    }

void crear(Nodo* arbol){
    ofstream doc;
    doc.open("documento.txt", ios::out | ios::app);
    if (doc.fail()) {
		cout << "No se pudo abrir el archivo " << endl;
		return;
	}
	 if (arbol==NULL){
        return;
	 }
	 else{
        doc<<arbol->DPI;
        crear(arbol->der);
        crear(arbol->izq);
	 }
    doc.close();
}

void lectura(){
 ifstream archivo;
 string texto, linea;

 archivo.open("nombres.txt",ios::in);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." <<endl;
    return;
    }


    int limit;

    cout<<"cuantos datos desea ver?"<<endl;
    cin>>limit;
    int contador = 0;
    bool primerLineaLeida = false;


while (getline(archivo, linea) && contador < limit) {
if (!primerLineaLeida) {
            primerLineaLeida = true;


continue;
}
    string letras = "";
string numeros = "";
bool letrasEncontradas = false;

        for (char c : linea) {
            if (isalpha(c)) {
                letras += c;
                letrasEncontradas = true;
            } else if (isdigit(c) && letrasEncontradas) {
                numeros += c;
            }
        }

        if (numeros.length() > 13) {
            numeros = numeros.substr(0, 13);
        }
        cout << "letras: " << letras << endl;
        cout << "Numeros: " << numeros << endl;
        insertarNodo(arbol,stoll(numeros.c_str()),letras,0,"","","","","","",padre);
        contador++;
    }
}



void Menu(){
    long long int DPI;
    string nombre;
    int vacunas;
    string vacuna1;
    string vacuna2;
    string vacuna3;
    string departamento;
    string Municipio;
    string LugarVacuna;
	int opcion, op2, op3, op4, contador=0,auxY=0;

    do{

    	cout<<" ---------------------------------"<<endl;
        cout<<"|      ---MENU DE OPCIONES---     |"<<endl;
        cout<<"|                                 |"<<endl;
        cout<<"|     1. Ver archivo de texto     |"<<endl;
        cout<<"|     2. Nuevo registro           |"<<endl;
        cout<<"|     3. Mostrar Arbol Vertical   |"<<endl;
        cout<<"|     4. Buscar Dato              |"<<endl;
        cout<<"|     5. Eliminar Dato            |"<<endl;
        cout<<"|     6. Actualizar datos         |"<<endl;
        cout<<"|     7. Mostrar recorridos       |"<<endl;
        cout<<"|     8. Recorridos encriptados   |"<<endl;
        cout<<"|     9. Desencriptar recorridos  |"<<endl;
        cout<<"|    10. Guardar Arbol            |"<<endl;
        cout<<"|    11. Salir                    |"<<endl;
        cout<<" ---------------------------------"<<endl;
        cout<<"Opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
   cout<< "cargar archivo de texto"<<endl;
                lectura();
                getch ();
                break;
            case 2:
        system ("cls");
        cout << "Ingrese los nuevos datos:" << endl;

        cout << "DPI: ";
    long long int DPI;
    cin >> DPI;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Vacunas: ";
    int vacunas;
    cin >> vacunas;
    cin.ignore();

    cout << "Vacuna 1: ";
    getline(cin, vacuna1);

    cout << "Vacuna 2: ";
    getline(cin, vacuna2);

    cout << "Vacuna 3: ";
    getline(cin, vacuna3);

    cout << "Departamento: ";
    getline(cin, departamento);

    cout << "Municipio: ";
    getline(cin, Municipio);

    cout << "Lugar de Vacunacion: ";
    getline(cin, LugarVacuna);
    insertarNodo(arbol, DPI, nombre, vacunas, vacuna1, vacuna2, vacuna3, Municipio, departamento, LugarVacuna, NULL);

    break;
            case 3:

                 cout<<"\nMostrando el arbol\n"<<endl;
                    mostrarArbolVertical(arbol, auxY);
                    cout<<"\n\n";
                    system("pause");
                    break;
            case 4: cout<<"\nEscriba el Dato: ";
            		cin>>DPI;
            		cout<<"\n\n";
                    if(buscarDato(arbol, DPI)==true){
                        cout<<"El dato ("<<DPI<<") fue encontrado"<<endl;
                    }
                    else{
                        cout<<"El dato ("<<DPI<<") no fue encontrado"<<endl;
                    }

                    system("pause");
                    break;
            case 5: cout<<"\nEscriba el Dato: ";
            		cin>>DPI;
            		cout<<"\n\n";
            		if(buscarDato(arbol, DPI)==true){
                        cout<<"El dato ("<<DPI<<") fue eliminado"<<endl;
                    }
                    else{
                        cout<<"El dato ("<<DPI<<") no fue encontrado"<<endl;
                    }
            		eliminar(arbol,DPI);
            		system("pause");
            		break;

            case 6:
    cout << "Ingrese el DPI: ";
    long long int dpi;
    cin >> dpi;
    cin.ignore();
    modificarDato(arbol, dpi);
    getch();
    break;
           case 7: system("cls");
                    do{

                    cout<<" --------------------------------"<<endl;
                    cout<<"|       ---  RECORIDOS  ---      |"<<endl;
                    cout<<"|                                |"<<endl;
                    cout<<"|    1. Recorrido PreOrden       |"<<endl;
                    cout<<"|    2. Recorrido InOrden        |"<<endl;
                    cout<<"|    3. Recorrido PostOrden      |"<<endl;
                    cout<<"|    4. Volver al Menu Opciones  |"<<endl;
                    cout<<" --------------------------------"<<endl;
                    cout<<"Opcion: ";
                    cin>>op2;
                    switch(op2){
                        case 1: cout<<"\nRecorrido en PreOrden: "<<endl;
                                pre(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        case 2: cout<<"\nRecorrido en InOrden: "<<endl;
                                in(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        case 3: cout<<"\nRecorrido en PostOrden: "<<endl;
                                post(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        }
                        system("cls");
                    }while(op2!=4);
            		break;
            		case 8: system("cls");
                    do{
                    cout<<" --------------------------------"<<endl;
                    cout<<"|    ---  ENCRIPTACIONES  ---    |"<<endl;
                    cout<<"|                                |"<<endl;
                    cout<<"|    1. Encriptar en PreOrden    |"<<endl;
                    cout<<"|    2. Encriptar en InOrden     |"<<endl;
                    cout<<"|    3. Encriptar en PostOrden   |"<<endl;
                    cout<<"|    4. Volver al Menu Opciones  |"<<endl;
                    cout<<" --------------------------------"<<endl;
                    cout<<"Opcion: ";
                    cin>>op3;
                    switch(op3){
                        case 1: cout<<"\nRecorrido en PreOrden: "<<endl;
                                encriPre(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                    break;
                        case 2: cout<<"\nRecorrido en InOrden: "<<endl;
                                encriIn(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        case 3: cout<<"\nRecorrido en PostOrden: "<<endl;
                                encriPost(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        }
                        system("cls");
                    }while(op3!=4);
            		break;

                                case 9: system("cls");
                    do{

                    cout<<" -------------------------------"<<endl;
                    cout<<"|  ---  DESENCRIPTACIONES  ---  |"<<endl;
                    cout<<"|                               |"<<endl;
                    cout<<"|   1. Desencriptar PreOrden    |"<<endl;
                    cout<<"|   2. Desencriptar InOrden     |"<<endl;
                    cout<<"|   3. Desencriptar PostOrden   |"<<endl;
                    cout<<"|   4. Volver al Menu Opciones  |"<<endl;
                    cout<<" -------------------------------"<<endl;
                    cout<<"Opcion: ";
                    cin>>op4;
                    switch(op4){
                        case 1: cout<<"\nRecorrido en PreOrden: "<<endl;
                                descriPre(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        case 2: cout<<"\nRecorrido en InOrden: "<<endl;
                                descrIn(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        case 3: cout<<"\nRecorrido en PostOrden: "<<endl;
                                descriPost(arbol);
                                cout<<"\n\n";
                                system("pause");
                                break;
                        }
                        system("cls");
                    }while(op4!=4);
            		break;
        case 10: cout<<"\nArchivo Guardado...\n\n";
                crear(arbol);
                system("pause");
                break;
                    }
        system("cls");
    }while (opcion !=11);
    cout <<"Gracias por usar este software :)"<<endl;
}
int main()
{
    Menu();
    getch();
    return 0;
}

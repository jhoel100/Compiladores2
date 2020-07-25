/*
PRUEBAS: 
( true and true ) #             true
not ( true and true ) #            false
not not ( not true and not true ) #          false
true or not false #          true
false and false #         false
( false and false and not true or false ) #          false 
( not true ) and ( not false ) or ( true or true ) #          true
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;

string preanalisis;
int contador;
vector<string> arreglo;
vector<string> tokens;

void parea(string);
void error();

bool BEXP();
bool BTERM();
bool BFACTOR();

bool BEXP()
{
    //Se usan dos auxiliares para almacenar los valores
    //recursivamente de la evaluacion
    bool auxiliar;
    bool auxiliar2;
    //el primero toma el valor que devuelve recursivamente BTERM
    auxiliar=BTERM();
    //Si todavia hay mas para reconocer, toma cada uno y lo opera
    //con or , con el valor devuelto de BTERM
    while(preanalisis=="or"){
        parea("or");
        auxiliar2=BTERM();
        auxiliar=(auxiliar||auxiliar2);
    }
    return auxiliar;
};

//De manera similar a BEXP, solo que este usa and y no or
bool BTERM(){
    bool auxiliar;
    bool auxiliar2;
    auxiliar=BFACTOR();
    while(preanalisis=="and"){
        parea("and");
        auxiliar2=BFACTOR();
        auxiliar=(auxiliar && auxiliar2);
    }
    return auxiliar;
};

//Se encarga de dar los factores, parentesis y tambien los true y false
bool BFACTOR(){
    bool auxiliar;
    if(preanalisis=="not"){
        parea("not");
        auxiliar=BFACTOR();
        return (!auxiliar);
    }else{
        if(preanalisis=="("){
            parea("(");
            auxiliar=BEXP();
            parea(")");
            return auxiliar;
        }else{
            if(preanalisis=="true"){
                parea("true");
                return true;
            }else{
                if(preanalisis=="false"){
                    parea("false");
                    return false;
                }else{
                    error();
                    return false;
                }
            }
        }
    }
};

void error()
{
    printf("Error de sintaxis");
}

//reduce y verifica que no se llego al final sin reconocer un caracter
void parea(string t)
{
 if (preanalisis==t){

    contador++;
    if(t!="#"){
        preanalisis=arreglo[contador];
    }
 }
 else{
    error();
 }
}

int main(){

    string texto;
    getline(cin,texto);

    istringstream isstream(texto);

    //toma toda una entrada separada por espacios
    //la separa en partes para almacenarla en un vector
    // y sea mas facil recorrerlo al hacer el compilado
    contador=0;
    while(!isstream.eof()){

        string tempStr;

        isstream>>tempStr;
        arreglo.push_back(tempStr);

        if(arreglo[contador]=="and" || arreglo[contador]=="or" || arreglo[contador]=="not" || arreglo[contador]=="(" || arreglo[contador]==")"){
            tokens.push_back(arreglo[contador]);
        }else{
            tokens.push_back("Bool");
        }

        //std::cout <<arreglo[contador]<<"  "<<tokens[contador]<< std::endl;
        contador++;
    }

    //Extrae el primer valor como el de pre analisis
    //para poder comenzar recien con el compilado
    contador=0;
    preanalisis=arreglo[contador];

    //respuesta contiene la respuesta de la llamada recursiva de la expresion
    bool respuesta;

    //Comienza a reconocer los caracteres
    //manda error si la cadena no termina con #
    //en el ejemplo se usa <enter> pero eso
    //se puede cambiar facilmente a <enter>

    if(arreglo[arreglo.size()-1]=="#"){
        respuesta=BEXP();
    }else{
        error();
    }

    //si imprimimos la respuesta tal cual sale 0 o 1
    //pero nos sentimos a gusto con tener true o false
    if(respuesta){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    return 0;
}

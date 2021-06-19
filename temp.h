#include "lib.h"

class Regla; class Token; class Gramatica;


class Token {
    public:

    string simbolo = "";

    vector<Regla> reglas = {};

    bool is_terminal(){
        return reglas.empty();
    }

};

class Regla {
    public:
    vector<Token> tokens = {};

};

class Gramatica {
    public:
    vector<Token> noTerminales = {};

};


vector<Token> Primeros(Token x){
    vector<Token> primeros = {};
    string same = x.simbolo;
    if(x.is_terminal()){
        primeros.push_back(x);
        return primeros;
    }
    for(int i = 0; i< x.reglas.size(); i++){
        if(x.reglas[i].tokens[0].simbolo != same){
            if(x.reglas[i].tokens[0].is_terminal() == true){
                primeros.push_back(x.reglas[i].tokens[0]);
            } else{
                vector<Token> otrosPrimeros = Primeros(x.reglas[i].tokens[0]);
                primeros.insert(primeros.end(), otrosPrimeros.begin(), otrosPrimeros.end());
            }
        }
    }
}

vector<Token> Siguientes(Gramatica x){
    
}


#include "lib.h"

using namespace std;

class Regla; class Token; class Gramatica;


class Token {
public:

    string simbolo;

    Token(string s){
        simbolo = s;
    }
    vector<Regla*> reglas = {};
    bool is_terminal(){
        return reglas.empty();
    }
};

class Regla {
public:
    vector<Token*> tokens = {};
};

class Gramatica {
public:
    vector<Token*> noTerminales = {};
};

static Token Meta("$");

vector<Token*> Primeros(Token& x){
    vector<Token*> primeros = {};
    string same = x.simbolo;
    if(x.is_terminal()){
        primeros.push_back(&x);
        return primeros;
    }

    for(int i = 0; i< x.reglas.size(); i++){

        if(x.reglas[i]->tokens[0]->simbolo != same){

            if(x.reglas[i]->tokens[0]->is_terminal()){

                primeros.push_back(x.reglas[i]->tokens[0]);

            } else{

                vector<Token*> otrosPrimeros = Primeros(*(x.reglas[i]->tokens[0]));
                primeros.insert(primeros.end(), otrosPrimeros.begin(), otrosPrimeros.end());
                
            }
        }
    }
    return primeros;
}

unordered_map<Token*, vector<Token*>> Siguientes(Gramatica& x){

    unordered_map<Token*, vector<Token*>> siguientes;
    vector<Token*> siguientesInicial = {};
    siguientes[x.noTerminales[0]] = siguientesInicial;
    siguientes[x.noTerminales[0]].push_back(&Meta);
    for(int i = 1; i< x.noTerminales.size(); i++){
        siguientes[x.noTerminales[i]] = siguientesInicial;
    }

    int initialSize;
    int afterSize = 1;

    do{
        initialSize = afterSize;

        for(int i = 0; i< x.noTerminales.size(); i++){

            for(int j = 0; j< x.noTerminales[i]->reglas.size(); j++){

                for(int k = 0; k< x.noTerminales[i]->reglas[j]->tokens.size(); k++){

                    if(!x.noTerminales[i]->reglas[j]->tokens[k]->is_terminal()){

                        if(k+1 < x.noTerminales[i]->reglas[j]->tokens.size()){
                            auto primeros = Primeros(*x.noTerminales[i]->reglas[j]->tokens[k+1]);

                            for(int l = 0 ; l<primeros.size(); l++){
                                auto v = siguientes[x.noTerminales[i]->reglas[j]->tokens[k]];
                                if(find(v.begin(), v.end(), primeros[l]) == v.end()){
                                    siguientes[x.noTerminales[i]->reglas[j]->tokens[k]].push_back(primeros[l]);
                                }
                            }

                        } else{
                            auto siguientes1 = siguientes[x.noTerminales[i]];

                            for(int l = 0 ; l<siguientes1.size(); l++){
                                auto v = siguientes[x.noTerminales[i]->reglas[j]->tokens[k]];
                                if(find(v.begin(), v.end(), siguientes1[l]) == v.end()){
                                    siguientes[x.noTerminales[i]->reglas[j]->tokens[k]].push_back(siguientes1[l]);
                                }
                            }
                        }
                    }
                }
            }
        }

        afterSize = 0;
        for (auto& it: siguientes) {
            for(auto& it2: it.second){
                afterSize++;
            }
        }

    }while(initialSize != afterSize);

    return siguientes;
}



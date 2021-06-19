#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class Regla; class Token; class Gramatica;

class Token {
    public:

    Token(string s){
      simbolo = s;
    }

    string simbolo = "";

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


vector<Token*> Primeros(Token x){
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

vector<Token> Siguientes(Gramatica x){
    
}

int main() {
  Token PA("(");
  Token PC(")");
  Token exp("exp");
  Token opsuma("opsuma");
  Token opmult("opmult");
  Token term("term");
  Token factor("factor");
  Token plus("+");
  Token minus("-");
  Token mult("*");
  Token numero("numero");

  Regla r_exp1; r_exp1.tokens.push_back(&exp);r_exp1.tokens.push_back(&opsuma);r_exp1.tokens.push_back(&term);

  Regla r_exp2;r_exp2.tokens.push_back(&term);

  Regla r_opsuma1;r_opsuma1.tokens.push_back(&plus);

  Regla r_opsuma2;r_opsuma2.tokens.push_back(&minus);

  Regla r_term1; r_term1.tokens.push_back(&term);r_term1.tokens.push_back(&opmult);r_term1.tokens.push_back(&factor);

  Regla r_term2;r_term2.tokens.push_back(&factor);

  Regla r_opmult;r_opmult.tokens.push_back(&mult);

  Regla r_factor1; r_factor1.tokens.push_back(&PA);r_factor1.tokens.push_back(&exp);r_factor1.tokens.push_back(&PC);

  Regla r_factor2;r_factor2.tokens.push_back(&numero);

  exp.reglas.push_back(&r_exp1);exp.reglas.push_back(&r_exp2);
  opsuma.reglas.push_back(&r_opsuma1);opsuma.reglas.push_back(&r_opsuma2);
  term.reglas.push_back(&r_term1);term.reglas.push_back(&r_term2);
  opmult.reglas.push_back(&r_opmult);
  factor.reglas.push_back(&r_factor1);factor.reglas.push_back(&r_factor2);

  Gramatica g;
  g.noTerminales.push_back(&exp);
  g.noTerminales.push_back(&opsuma);
  g.noTerminales.push_back(&term);
  g.noTerminales.push_back(&opmult);
  g.noTerminales.push_back(&factor);

  vector<Token*> primeros = Primeros(exp);
  for(int i = 0; i<primeros.size(); i++){
    cout<<primeros[i]->simbolo<<" ";
  }

}

#include "lib.h"
#include "reader.h"
#include "Utility.h"

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

    vector<Token*> primeros = Primeros(PC);
    for(int i = 0; i<primeros.size(); i++){
        cout<<primeros[i]->simbolo<<" ";
    }

    auto siguientes = Siguientes(g);

}
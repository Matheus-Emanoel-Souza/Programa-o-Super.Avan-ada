#include "metodos.h"

int main() 
{   
    Lista HistoricoMsg;
    criaHistorico(HistoricoMsg);
    iniciarSerial();
    setup(HistoricoMsg);
    
    while (1) {
        loop(HistoricoMsg);
        //Imprimir Lista.
    }

    fecharSerial();
    return 0;
}

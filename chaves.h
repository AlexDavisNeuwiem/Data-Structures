// Copyright [2022] <Alex Davis Neuwiem da Silva>
#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    bool erro = false;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    for (int i = 0; i < tamanho; i++) {
        if ('{' == trecho_programa[i]) {
            pilha.push('{');
        } else if ('}' == trecho_programa[i]) {
            if (pilha.empty() != 1) {
                pilha.pop();
            } else {
                erro = true;
            }
        }
    }
    if (pilha.empty() != 1 || erro == true) {
        resposta = false;
    }
    return resposta;
}

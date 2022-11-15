// Copyright [2022] <Alex Davis Neuwiem da Silva>
#include <string>
#include "./array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);
    for (std::size_t i = 0; i < texto.length() ; i++) {
        if (texto[i] == '<') {
            fila.dequeue();
        } else if (texto[i] == '>') {
            fila.enqueue(fila.back());
        } else {
            fila.enqueue(texto[i]);
        }
    }

    return fila;
}

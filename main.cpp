// Copyright [2022] <Alex Davis Neuwiem da Silva e Pedro Philippi Araujo>
#include <iostream>
#include "./ArrayStack.h"
#include "./ArrayQueue.h"
#include <cstring>
#include <fstream>
using namespace std;

int main() {

    char xmlfilename[100];
    std::cin >> xmlfilename;  // Entrada
    
    ifstream arquivo_xml_01;
    arquivo_xml_01.open(xmlfilename);
    
    string linha;  // Linha a ser percorrida
        
    structures::ArrayStack<string> pilha(100);  // Declaração da pilha
    structures::ArrayQueue<int> filx(100);      // Declaração da fila que contém x
    structures::ArrayQueue<int> fily(100);      // Declaração da fila que contém y
    
    string data;
    string name;
    int height = 0;
    int width = 0;
    string texto;
    bool escrever = false;
    bool error = false;
    
    // INICIO DO PROBLEMA 01

    while (getline(arquivo_xml_01, linha)) {                        // Percorre o Arquivo enquanto houverem linhas
        for (int i = 0; i < linha.length(); i++) {                  // Percorre cada linha
            if (linha[i] == '<' && linha[i + 1] != '/') {           // Se não for uma tag de fechamento
                int j = 1;
                string tag = "";
                while (linha[i + j] != '>') {                       // Percorre a linha para encontar o nome da tag
                    tag = tag + linha[i + j];                       // Concatena o nome na variável "tag"
                    j++;
                }
                pilha.push(tag);
                i = i + j;
            } else if (linha[i] == '<' && linha[i + 1] == '/') {    // Se for uma tag de fechamento
                int j = 2;
                string tag = "";
                while (linha[i + j] != '>') {                       // Percorre a linha para encontar o nome da tag
                    tag = tag + linha[i + j];                       // Concatena o nome na variável "tag"
                    j++;
                }
                if (pilha.top() == tag) {
                    pilha.pop();
                } else {
                    error = true;
                    cout << "error" << endl;
                }
                i = i + j;
            }
        }
    }
    if (pilha.empty() == false) {
        error = true;
        cout << "error" << endl;
    }

    // FIM DO PROBLEMA 01
    
    arquivo_xml_01.close();
    
    linha = "";
    
    ifstream arquivo_xml_02;
    arquivo_xml_02.open(xmlfilename);
    
    // INICIO DO PROBLEMA 02
    
    if (error == false) {
        while (getline(arquivo_xml_02, linha)) {                        // Percorre o Arquivo enquanto houverem linhas
            for (int i = 0; i < linha.length(); i++) {                  // Percorre cada linha
                if (linha[i] == '<' && linha[i + 1] != '/') {           // Se não for uma tag de fechamento
                    int j = 1;
                    string tag = "";
                    while (linha[i + j] != '>') {                       // Percorre a linha para encontar o nome da tag
                        tag = tag + linha[i + j];                       // Concatena o nome na variável "tag"
                        j++;
                    }
                    if (tag == "name" || tag == "height" || tag == "width" || tag == "data") {
                        escrever = true;
                    }
                    i = i + j;
                } else if (linha[i] == '<' && linha[i + 1] == '/') {    // Se for uma tag de fechamento
                    int j = 2;
                    string tag = "";
                    while (linha[i + j] != '>') {                       // Percorre a linha para encontar o nome da tag
                        tag = tag + linha[i + j];                       // Concatena o nome na variável "tag"
                        j++;
                    }
                    texto = texto.erase(0,1);
                    if (tag == "name" || tag == "height" || tag == "width" || tag == "data") {
                        if (tag == "name") {
                            name = texto;
                        } else if (tag == "height") {
                            height = stoi(texto);
                        } else if (tag == "width") {
                            width = stoi(texto);
                        } else {
                            data = texto;
                        }
                        escrever = false;
                        texto = "";
                    }
                    if (tag == "img") {
                        
                        int **E;
                        E = new int * [height];
                        int **R;
                        R = new int * [height];
                        
                        for (int k = 0; k < height; k++) {
                            E[k] = new int[width];
                            R[k] = new int[width];
                        }
                        
                        int rotulo = 1;
                        
                        int pos = 0;
                        for (int k = 0; k < height; k++) {
                            for (int l = 0; l < width; l++) {
                                E[k][l] = ((int)data[pos]) - 48;
                                R[k][l] = 0;
                                pos++;
                            }
                        }
                        for (int k = 0; k < height; k++) {
                            for (int l = 0; l < width; l++) {
                                if (E[k][l] == 1 && R[k][l] == 0) {
                                    filx.enqueue(k);
                                    fily.enqueue(l);
                                    R[k][l] = rotulo;
                                    
                                    // COMEÇO FLOOD FILL
                                    
                                    while (filx.empty() == false) {
                                        for (int m = 0; m < filx.size(); m++) {
                                            int x = filx.dequeue();
                                            int y = fily.dequeue();
                                            if (x - 1 >= 0) {
                                                if (E[x - 1][y] == 1 && R[x - 1][y] == 0) {
                                                    filx.enqueue(x - 1);
                                                    fily.enqueue(y);
                                                    R[x - 1][y] = rotulo;
                                                }
                                            }
                                            if (x + 1 < height) {
                                                if (E[x + 1][y] == 1 && R[x + 1][y] == 0) {
                                                    filx.enqueue(x + 1);
                                                    fily.enqueue(y);
                                                    R[x + 1][y] = rotulo;
                                                }
                                            }
                                            if (y - 1 >= 0) {
                                                if (E[x][y - 1] == 1 && R[x][y - 1] == 0) {
                                                    filx.enqueue(x);
                                                    fily.enqueue(y - 1);
                                                    R[x][y - 1] = rotulo;
                                                }
                                            }
                                            if (y + 1 < width) {
                                                if (E[x][y + 1] == 1 && R[x][y + 1] == 0) {
                                                    filx.enqueue(x);
                                                    fily.enqueue(y + 1);
                                                    R[x][y + 1] = rotulo;

                                                }
                                            }
                                        }
                                    }
                                    rotulo++;
                                    
                                    // FIM FLOOD FILL
                                    
                                }
                            }
                        }
            
                        std::cout << name << " " << rotulo - 1 << std::endl;
                        
                        // Resetar aqui as variáveis globais
                        name = "";
                        data = "";
                        height = 0;
                        width = 0;
                        filx.clear();
                        fily.clear();
                        
                    }
                    i = i + j;
                }
                if (escrever == true) {
                    texto = texto + linha[i];
                }
            }
        }
    }
    
    // FIM DO PROBLEMA 02

    arquivo_xml_02.close();

    return 0;
}
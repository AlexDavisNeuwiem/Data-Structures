// Copyright [2022] <Alex Davis Neuwiem da Silva>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int ALPHABET_SIZE = 26;

struct Node {
    char            letter;
    struct Node*    children[ALPHABET_SIZE];
    unsigned long   position;
    unsigned long   length;
};

struct Node* getNode(void) {
    struct Node* ptr =  new Node;
    ptr->letter = '0';
    ptr->position = 0;
    ptr->length = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        ptr->children[i] = NULL;
    return ptr;
}

void insert(struct Node* root, string word, int length, int position) {
    struct Node* ptr = root;
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (!ptr->children[index]) {
            ptr->letter = word[i];
            ptr->children[index] = getNode();
        }
        ptr = ptr->children[index];
    }
    ptr->letter = word.back();
    ptr->length = length;
    ptr->position = position;
}

int count(struct Node* node) {
    int aux = 0;
    if (node->length) {
        aux++;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            aux = aux + count(node->children[i]);
        }
    }
    return aux;
}

void search(struct Node* root, string word) {
    struct Node* ptr = root;
    for (int i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (ptr->children[index] == NULL) {
            cout << word << " is not prefix" << endl;
            return;
        }
        ptr = ptr->children[index];
    }
    int prefix = count(ptr);
    cout << word << " is prefix of " << prefix << " words" << endl;
    if (ptr->length) {
        cout << word << " is at (" << ptr->position << "," << ptr->length << ")" << endl;
    }
    return;
}

void deleteNode (struct Node* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            deleteNode(node->children[i]);
        }
    }
    delete node;
}

int main() {

    string filename;
    string line;
    string word;

    cin >> filename;

    ifstream dicionario;
    dicionario.open(filename);
    
    struct Node* root = getNode();
    int position = 0;
    
    while (getline(dicionario, line)) {
        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '[') {
                if (i != 0 && line[i - 1] != '\n') {
                    position++;
                    continue;
                }
                int j = 1;
                string word = "";
                while (line[i + j] != ']') {
                    word = word + line[i + j];
                    j++;
                }
                unsigned long length = line.length();
                insert(root, word, length, position);
            }
            position++;
            if (i == line.length() - 1) {
                position++;
            }
        }
    }
    
    string input;
    
    while (1) {
        cin >> input;
        if (input.compare("0") == 0) {
            break;
        }
        search(root, input);
    }
    
    deleteNode(root);

    return 0;
}

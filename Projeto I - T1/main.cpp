//! Copyright [2021] <BEATRIZ VALIO WEISS>
/// Projeto I - processamento de XML com imagens binárias
/// Nota desse codigo 10/10
  
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>   /// std::size_t
#include <stdexcept>   /// C++ exceptions
#include <algorithm>   /// intervalos
#include <utility>   /// funcoes utilidades
#include <iostream>   /// leitura e gravacao
#include <fstream>   /// arquivos
#include <sstream>   /// fluxo de dados
#include <string>   /// str e mem
#include <vector>   /// array primitivo
#include <tuple>   /// funcoes tupla
#include <stack>   /// funcoes pilha


namespace xml {
//! metodo valida xml
bool valida(const std::string& contents);
//! metodo obtem a tag
std::string get_tag(
    const std::string& source, 
    const std::string& open_tag,
    const std::string& close_tag, 
    size_t& start_index);
//! metodo obtem o valor
std::string get_value(
    const std::string& source,
    const std::string& open_tag,
    const std::string& close_tag);
}  /// namespace xml

namespace structures {
//! Classe LinkedStack
template<typename T>
class LinkedStack {
 public:
    //! construtor simples
    LinkedStack();
    //! destrutor
    ~LinkedStack();
    //! metodo limpa pilha
    void clear();
    //! metodo empilha
    void push(const T& data);
    //! metodo desempilha
    T pop();
    //! metodo retorna o topo
    T& top() const;
    //! verifica se esta vazia
    bool empty() const;
    //! metodo retorna tamanho
    std::size_t size() const;

 private:
    class Node {   /// Elemento
     public:
        explicit Node(const T &data) {
            data_ = data;
            next_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {   /// getter: dado
            return data_;
        }

        const T& data() const {   /// getter const: dado
            return data_;
        }

        Node* next() {   /// getter: próximo
            return next_;
        }

        const Node* next() const {   /// getter const: próximo
            return next_;
        }

        void next(Node* node) {   /// setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* top_{nullptr};
    std::size_t size_{0u};
};
}   /// namespace structures

namespace area {
    //! enumera sequencia dos pixels
    enum cor {
        /// intensidade 0 para preto
        preto,
        /// intensidade 1 para branco
        branco,
    };
    //! metodo transforma uma area conexa inteira da matriz em zeros
    void transf_area(std::vector<std::vector<bool>>& matrix, int i, int j);
    //! metodo conta areas em branco{1} conexas
    int contador_area(std::vector<std::vector<bool>> matrix);
    //! metodo cria nova matriz booleana a partir de uma string de '0' e '1'
    std::vector<std::vector<bool>> nova_matriz(const std::string& str_matrix, int width, int height);
}   /// namespace area

int main() {
    char xml_file_name[100];
    std::ifstream xml_file;

    std::cin >> xml_file_name;

    xml_file.open(xml_file_name);
    
    if (not xml_file.is_open()) {
        std::cout << "error\n";
        return -1;
    }
    
    std::stringstream stream;
	stream << xml_file.rdbuf();
	std::string contents = stream.str();

    xml_file.close();

    if (not xml::valida(contents)) {
        std::cout << "error\n";
        return -1;
    }

    size_t i = {0};

    while (i < contents.length()) {
        std::string open_tag = "<img>";
        std::string close_tag = "</img>";
        std::string image = xml::get_tag(contents, open_tag, close_tag, i);

        i += image.length() + close_tag.length();
        
        if (i > contents.length()) break;
	
        std::string data = xml::get_value(image, "<data>", "</data>");
        const std::string name = xml::get_value(image, "<name>", "</name>");
        const int width = std::stoi(xml::get_value(image, "<width>", "</width>"));
        const int height = std::stoi(xml::get_value(image, "<height>", "</height>"));

        if (height <= 0|| width <= 0) return -1;

        data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());

        std::vector<std::vector<bool>> matrix = area::nova_matriz(data, width, height);

        int regions = area::contador_area(matrix);
		std::cout << name << ' ' << regions << std::endl;
    }
}

//-----------------------------------------------------------------------------

namespace xml {
bool valida(const std::string& contents) {
    structures::LinkedStack<std::string> tags;
    size_t i = 0u;

    while (i < contents.length()) {
        size_t pos_inicial = contents.find('<', i);
        size_t pos_final = contents.find('>', pos_inicial);

        if (pos_inicial == std::string::npos) {
            break;
        }
        if (pos_final == std::string::npos) {
            return false;
        }
        
        std::string tag = contents.substr(pos_inicial, pos_final + 1 - pos_inicial);
        i = pos_final + 1;

        if (tag[1] != '/') {
            tags.push(tag.insert(1, "/"));
        } else {
            if (tags.empty()) {
                return false;
            } else if (tags.top() == tag) {
                tags.pop();
            } else {
                return false;
            }  
        }
    }
    return tags.empty();
}

std::string get_tag(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag, 
    size_t& start_index) {

    size_t pos_inicial = source.find(open_tag, start_index);
    size_t pos_final = source.find(close_tag, pos_inicial);
            
    pos_inicial += open_tag.length();
    std::string tag_contents = source.substr(pos_inicial, pos_final - pos_inicial);
    return tag_contents;
}

std::string get_value(
    const std::string& source, 
    const std::string& open_tag, 
    const std::string& close_tag) {

    std::size_t pos{0};
    return get_tag(source, open_tag, close_tag, pos);
}
}  /// namespace xml


namespace structures {
template<typename T>
LinkedStack<T>::LinkedStack() {}

template<typename T>
LinkedStack<T>::~LinkedStack() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::clear() {
    top_ = nullptr;
    size_ = 0;
}

template<typename T>
void LinkedStack<T>::push(const T& data) {
    Node* novo = new Node(data, top_);
    top_ = novo;
    size_++;
}

template<typename T>
T LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Pilha vazia!");
    }
    Node* aux = top_;
    T data = aux->data();
    top_ = top_->next();
    size_--;
    delete aux;
    return data;
}

template<typename T>
T& LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Pilha vazia!");
    }
    return top_->data();
}

template<typename T>
bool LinkedStack<T>::empty() const {
    return size_ == 0;
}

template<typename T>
std::size_t LinkedStack<T>::size() const {
    return size_;
}

}   /// namespace structures


namespace area {

void transf_area(std::vector<std::vector<bool>>& matrix, int i, int j) {
    structures::LinkedStack<std::tuple<int, int>> stack;

    int width = matrix[0].size();
    int height = matrix.size();
    stack.push(std::make_tuple(i, j));

    while (!stack.empty()) {
        std::tuple<int, int> aux = stack.pop();
        
        i = std::get<0>(aux);
        j = std::get<1>(aux);
        matrix[i][j] = 0;

        if (j > 0 && matrix[i][j - 1]) {
            stack.push(std::make_tuple(i, j - 1));     
        }
        if (j < (width - 1) && matrix[i][j + 1]) {
            stack.push(std::make_tuple(i, j + 1));
        }
        if (i > 0 && matrix[i - 1][j]) {
            stack.push(std::make_tuple(i - 1, j));
        }
        if (i < (height - 1) && matrix[i + 1][j]) {
            stack.push(std::make_tuple(i + 1, j));
        }
    }

} 

int contador_area(std::vector<std::vector<bool>> matrix) {
    int contagem = 0;
    
    for (int i = 0; i < (int) matrix.size(); i++) {
        for (int j = 0; j < (int) matrix[0].size(); j++) {
            if (matrix[i][j] == cor::branco) {
                contagem++;
                transf_area(matrix, i, j);
            }
        }
    }
    return contagem;
}

std::vector<std::vector<bool>> nova_matriz(const std::string& str_matrix, int width, int height) {
    std::vector<std::vector<bool>> matrix;

    for (int i = 0u; i < height; i++) {
        std::vector<bool> line;
        for (int j = 0; j < width; j++) {
            line.push_back(str_matrix[i * width + j] == '1');
        }
        matrix.push_back(line);
    } 
    return matrix;
}
}   /// namespace area

#endif

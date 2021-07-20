//! Copyright [2021] <BEATRIZ VALIO WEISS>
// Nota desse codigo 100/100

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ Exceptions

namespace structures {

//! Classe Lista Encadeada
template<typename T>
class LinkedList {
 public:
    //! metodo construtor padrao
    LinkedList();
    //! metodo destrutor
    ~LinkedList();
    //! metodo limpar lista
    void clear();
    //! metodo inserir no fim
    void push_back(const T& data);
    //! metodo inserir no inicio
    void push_front(const T& data);
    //! metodo inserir na posicao
    void insert(const T& data, std::size_t index);
    //! metodo inserir em ordem
    void insert_sorted(const T& data);
    //! metodo acessar um elemento na posicao index
    T& at(std::size_t index);
    //! metodo retirar da posicao
    T pop(std::size_t index);
    //! metodo retirar do fim
    T pop_back();
    //! metodo retirar do inicio
    T pop_front();
    //! metodo remover dado especifico
    void remove(const T& data);
    //! metodo verifica lista vazia
    bool empty() const;
    //! metodo verifica se contem dado
    bool contains(const T& data) const;
    //! metodo retorna posicao do dado
    std::size_t find(const T& data) const;
    //! metodo retorna tamanho da lista
    std::size_t size() const;

 private:
    class Node {   // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {   // getter: dado
            return data_;
        }

        const T& data() const {   // getter const: dado
            return data_;
        }

        Node* next() {   // getter: próximo
            return next_;
        }

        const Node* next() const {   // getter const: próximo
            return next_;
        }

        void next(Node* node) {   // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {   // último node da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* current(std::size_t index) {   // indice do node
        auto it = head;
        if (index != 0) {
            for (std::size_t i = 1; i < size(); ++i) {
                if (i == index) {
                    return it;
                }
                it = it->next();
            }
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}   // namespace structures

#endif

//-----------------------------------------------------------------------------

template <typename T>
structures::LinkedList<T>::LinkedList() {
}

template <typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void structures::LinkedList<T>::clear() {
    while (size() != 0) {
        pop_front();
    }
}

template <typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    insert(data, size_);
}

template <typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* aux = new Node(data);
    if (aux == nullptr) {
        delete aux;
        throw std::out_of_range("lista cheia!");
    } else {
        aux -> next(head);
        head = aux;
        size_++;
    }
}

template <typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    Node* aux = new Node(data);
    Node* before;
    if ( aux == nullptr ) {
        throw std::out_of_range("lista cheia!");
    } else if (index > size_) {
        delete aux;
        throw std::out_of_range("lista cheia!");
    } else if (index == 0) {
        delete aux;
        push_front(data);
    } else {
        before = current(index);
        aux->next(before->next());
        before->next(aux);
        size_++;
    }
}

template <typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* before;
    if (empty()) {
        push_front(data);
    } else {
        before = head;
        for (std::size_t i = 0; i != size_; i++) {
            if (before->data() > data) {
                insert(data, i);
                break;
            } else if (i == (size_ - 1)) {
                push_back(data);
                break;
            } else {
                before = before->next();
            }
        }
    }
}

template <typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    Node* it;
    if (index > size()) {
        throw std::out_of_range("indice invalido!");
    } else if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        it = head;
        for (size_t i = 0; i < index; i++) {
            it = it->next();
        }
        return it->data();
    }
}

template <typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    Node *aux, *before;
    T dado;
    if (empty()) {
        throw("lista vazia");
    } else if (index < 0 || index > size_ -1) {
        throw std::out_of_range("lista cheia!");
    } else if (index == 0) {
        pop_front();
    } else {
        before = current(index);
        aux = before->next();
        before->next(aux->next());
        dado = aux->data();
        delete aux;
        size_--;
    }
    return dado;
}

template <typename T>
T structures::LinkedList<T>::pop_back() {
    Node* aux;
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else {
        aux = end();
        T dado = aux->data();
        delete aux;
        size_--;
        return dado;
    }
}

template <typename T>
T structures::LinkedList<T>::pop_front() {
    Node* aux;
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        aux = head;
        head = head->next();
        T dado = aux->data();
        delete aux;
        size_--;
        return dado;
    }
}

template <typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        std::size_t index = find(data);
        pop(index);
    }
}

template <typename T>
bool structures::LinkedList<T>::empty() const {
    return size() == 0;
}

template <typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* aux;
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        aux = head;
        for (std::size_t i = 0; i != size_; i++) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
    return false;
    }
}

template <typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* aux;
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        aux = head;
        for (std::size_t i = 0; i != size_; i++) {
            if (aux->data() == data) {
                return i;
            }
            aux = aux->next();
        }
    }
    return size_;
}

template <typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

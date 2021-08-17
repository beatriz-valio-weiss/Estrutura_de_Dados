//! Copyright [2021] <BEATRIZ VALIO WEISS>
//! Nota desse codigo 99/100

#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ exceptions

namespace structures {

template<typename T>
//! Classe DoublyCircularList
class DoublyCircularList {
 public:
    //! construtor padrao
    DoublyCircularList();
    //! construtor padrao
    ~DoublyCircularList();

    //! metodo limpa a lista
    void clear();

    //! metodo insere na ultima posicao
    void push_back(const T& data);
     //! metodo insere na primeira posicao
    void push_front(const T& data);
    //! metodo insere em determinada posicao
    void insert(const T& data, std::size_t index);
    //! metodo insere ordenadamente
    void insert_sorted(const T& data);

    //! metodo remove de determinada posicao
    T pop(std::size_t index);
    //! metodo remove ultimo
    T pop_back();
    //! metodo remove primeiro
    T pop_front();
    //! metodo verifica se existe e remove determinado elemento
    void remove(const T& data);

    //! metodo verifica se esta vazio
    bool empty() const;
    //! metodo verifica se existe determinado elemento
    bool contains(const T& data) const;

    // metodo consulta um indice (com checagem de limites)
    T& at(std::size_t index);
    //! metodo retorna elemento de determinado indice
    const T& at(std::size_t index) const;

    //! metodo procura determinado elemento e retorna o indice
    std::size_t find(const T& data) const;
    //! metodo retorna tamanho atual
    std::size_t size() const;

 private:
    class Node {
     public:
        explicit Node(const T &data) {
            data_ = data;
            next_ = nullptr;
            prev_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = nullptr;
        }

        Node(const T &data, Node *prev, Node *next) {
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        T& data() {   // getter: dado
            return data_;
        }

        const T& data() const {   // getter const: dado
            return data_;
        }

        Node* prev() {   // getter: anterior
            return prev_;
        }

        const Node* prev() const {   // getter const: anterior
            return prev_;
        }

        void prev(Node* node) {   // setter: anterior
            prev_ = node;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    // retorna o node
    Node* node_of_index(std::size_t index) {
        auto it = head;
        if (index <= size_/2) {
            for (auto i = 1u; i <= index; ++i)
                it = it->next();
        } else {
            for (auto i = 1u; i <= (size_-index); ++i)
                it = it->prev();
        }
        return it;
    }

    // inserir na posicao polimorfico
    void insert(const T& data, Node* current);

    Node* head{nullptr};
    std::size_t size_{0u};
};

}   // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
      insert(data, size_);
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Lista cheia!!");
    } else if (empty()) {
      head = novo;
      head->next(head);
      head->prev(head);
    } else {
      novo->next(head);
      novo->prev(head->prev());
      head->prev()->next(novo);
      head->prev(novo);
      head = novo;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Indice invalido!");
    } else if (index == 0) {
        push_front(data);
    } else {
        Node* novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Lista cheia!!");
        }
        Node* current = node_of_index(index);
        novo->next(current);
        novo->prev(current->prev());
        current->prev()->next(novo);
        current->prev(novo);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, Node* previous) {
    Node* novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Lista cheia!!");
    } else if (empty()) {
        head = novo;
        head->next(head);
        head->prev(head);
    } else {
        previous->next()->prev(novo);
        novo->next(previous->next());
        previous->next(novo);
        novo->prev(previous);
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto current = head;
        std::size_t position = 0u;
        while (data > current->data()) {
            if (++position == size_)
                break;
            current = current->next();
        }
        if (position == 0) {
            push_front(data);
        } else if (position == size_) {
            push_back(data);
        } else {
            insert(data, current->prev());
        }
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else if (index >= size()) {
        throw std::out_of_range("Indice invalido!");
    } else if (index == 0) {
        return pop_front();
    } else {
        auto aux = node_of_index(index);
        T data = aux->data();
        aux->prev()->next(aux->next());
        aux->next()->prev(aux->prev());
        size_--;
        delete aux;
        return data;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    return pop(size_-1);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    T dado;
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else {
        auto aux = head;
        dado = head->data();
        head->prev()->next(head->next());
        head->next()->prev(head->prev());
        head = head->next();
        size_--;
        delete aux;
    }

    if (empty()) {
        head = nullptr;
    }
    return dado;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return size() == 0u;
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Indice invalido ou Lista vazia!");
    }
    Node* current = node_of_index(index);
    return current->data();
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Indice invalido ou Lista vazia!");
    }
    Node* current = node_of_index(index);
    return current->data();
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    auto current = head;
    while (index < size()) {
        if (current->data() == data) {
            break;
        }
        current = current->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

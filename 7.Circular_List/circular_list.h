//! Copyright [2021] <BEATRIZ VALIO WEISS>
//! Nota desse codigo 100/100

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ exceptions

namespace structures {

template<typename T>
//! Classe CircularList
class CircularList {
 public:
    //! construtor padrao
    CircularList();
    //! construtor padrao
    ~CircularList();

    //! metodo limpa a lista
    void clear();

    //! metodo insere na ultima posicao
    void push_back(const T& data);
    //! metodo insere na ultima posicao
    void push_front(const T& data);
    //! metodo insere em determinada posicao
    void insert(const T& data, std::size_t index);
    //! metodo insere ordenadamente
    void insert_sorted(const T& data);

    //! metodo consulta um indice (com checagem de limites)
    T& at(std::size_t index);
    //! metodo retorna elemento de determinado indice
    const T& at(std::size_t index) const;

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
    //! metodo procura determinado elemento e retorna o indice
    std::size_t find(const T& data) const;

    //! metodo retorna tamanho atual
    std::size_t size() const;

 private:
    class Node {   // Elemento
     public:
        explicit Node(const T &data) {
            data_ = data;
            next_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {   // getter: dado
            return data_;
        }

        const T& data() const {   // getter const: dado
            return data_;
        }

        void data(const T& data) {   // setter: dado
            data_ = data;
        }

        Node* next() {   // getter: próximo
            return next_;
        }

        const Node* next() const {   // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    // último node da lista
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    // node anterior ao index
    Node* before_index(std::size_t index) const {
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        return it;
    }

    // inserir na posicao polimorfico
    void insert(const T& data, Node* before);

    Node* head{nullptr};
    std::size_t size_{0u};
};

}   // namespace structures

#endif

//-----------------------------------------------------------------------------

template<typename T>
structures::CircularList<T>::CircularList() {
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty())
        pop_front();
}
template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* novo = new Node(head->data(), head->next());
        if (novo == nullptr)
            throw std::out_of_range("Lista cheia!");

        head->next(novo);
        head->data(data);
        head = novo;
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* novo = new Node(data);
    if (novo == nullptr) {
        throw std::out_of_range("Lista cheia!");
    } else if (empty()) {
        head = novo;
        head->next(head);
    } else {
        novo->data(head->data());
        novo->next(head->next());
        head->next(novo);
        head->data(data);
    }
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Indice invalido!");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        Node* novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Lista cheia!");
        }
        Node* ant = before_index(index);
        Node* prox = ant->next();
        novo->next(prox);
        ant->next(novo);
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node* current = head;
        std::size_t position = size();
        for (auto i = 0u; i < size(); ++i) {
            if (!(data > current->data())) {
                position = i;
                break;
            }
            current = current->next();
        }
        if (position == 0) {
            push_front(data);
        } else if (position == size_) {
            push_back(data);
        } else {
            insert(data, position);
        }
    }
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Indice invalido ou lista vazia!");
    } else {
        Node* current;
        if (index == 0) {
            current = head;
        } else {
            current = before_index(index)->next();
        }
        return current->data();
    }
}

template<typename T>
const T& structures::CircularList<T>::at(std::size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("Indice invalido ou lista vazia!");
    } else {
        Node* current;
        if (index == 0) {
            current = head;
        } else {
            current = before_index(index)->next();
        }
        return current->data();
    }
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista vazia");
    } else if (index >= size()) {
        throw std::out_of_range("Indice invalido!");
    } else if (index == 0) {
        return pop_front();
    } else {
        Node* ant_aux = before_index(index);
        Node* aux = ant_aux->next();
        T data = aux->data();
        ant_aux->next(aux->next());
        size_--;
        delete aux;
        return data;
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista vazia!");
    } else {
        Node* aux;
        T data = head->data();
        if (size_ == 1) {
            aux = head;
            head = nullptr;
        } else {
            aux = head->next();
            head->next(aux->next());
            head->data(aux->data());
        }
        size_--;
        delete aux;
        return data;
    }
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    pop(find(data));
}


template<typename T>
bool structures::CircularList<T>::empty() const {
    return size() == 0;
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    Node* current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}

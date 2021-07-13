// Copyright [2021] <BEATRIZ VALIO WEISS>
// Nota desse codigo 98/100

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ Exceptions

namespace structures {
template <typename T>
//! Classe ArrayQueue
class ArrayList {
 public:
    //! construtor padrao
    ArrayList();
    //! construtor com parametro
    explicit ArrayList(std::size_t max_size);
    //! destrutor padrao
    ~ArrayList();

    //! metodo limpa a lista
    void clear();
    //! metodo insere na ultima posicao
    void push_back(const T &data);
    //! metodo insere na primeira posicao
    void push_front(const T &data);
    //! metodo insere em determinada posicao
    void insert(const T &data, std::size_t index);
    //! metodo insere ordenadamente
    void insert_sorted(const T &data);
    //! metodo remove de determinada posicao
    T pop(std::size_t index);
    //! metodo remove da ultima posicao
    T pop_back();
    //! metodo remove da primeira posicao
    T pop_front();
    //! metodo verifica se existe e remove determinado elemento
    void remove(const T &data);
    //! metodo verifica se esta cheio
    bool full() const;
    //! metodo verifica se esta vazio
    bool empty() const;
    //! metodo verifica se existe determinado elemento
    bool contains(const T &data) const;
    //! metodo procura determinado elemento e retorna o indice
    std::size_t find(const T &data) const;
    //! metodo retorna tamanho atual
    std::size_t size() const;
    //! metodo retorna tamanho maximo
    std::size_t max_size() const;
    //! metodo consulta e retorna elemento de determinada posicao
    T &at(std::size_t index);
    //! metodo consulta elemento com sobrecarga de operador
    T &operator[](std::size_t index);
    //! metodo retorna elemento de determinada posicao
    const T &at(std::size_t index) const;
    //! metodo consulta elemento com sobrecarga de operador
    const T &operator[](std::size_t index) const;

 private:
    T *contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}   // namespace structures

#endif

//-----------------------------------------------------------------------------

template <typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = 0;
}

template <typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
}

template <typename T>
structures::ArrayList<T>::~ArrayList() {
    delete[] contents;
}

template <typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template <typename T>
void structures::ArrayList<T>::push_back(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia!");
    } else {
        contents[size_] = data;
        size_++;
    }
}

template <typename T>
void structures::ArrayList<T>::push_front(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia!");
    } else {
        for (size_t i = size(); i > 0; i--) {
            contents[i] = contents[i - 1];
        }
        contents[0] = data;
        size_++;
    }
}

template <typename T>
void structures::ArrayList<T>::insert(const T &data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("lista cheia!");
    } else {
        if (index >= 0 && index < size_) {
            for (size_t i = size_; i > index; i--) {
                contents[i] = contents[i - 1];
            }
            contents[index] = data;
            size_++;
        } else {
            throw std::out_of_range("indice invalido!");
        }
    }
}

template <typename T>
void structures::ArrayList<T>::insert_sorted(const T &data) {
    if (full()) {
        throw std::out_of_range("lista cheia!");
    } else {
        for (std::size_t i = 0; i < size_; i++) {
            if (data < contents[i]) {
                insert(data, i);
                return;
            }
        }
        if (empty()) {
            contents[0] = data;
            size_++;
            return;
        } else {
            push_back(data);
        }
    }
}

template <typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty())     {
        throw std::out_of_range("lista vazia!");
    } else {
        if (index > 0 && index < size_) {
            T aux = contents[index];
            for (size_t i = index; i < size_ - 1; i++) {
                contents[i] = contents[i + 1];
            }
            size_--;
            return aux;
        } else {
            throw std::out_of_range("indice invalido!");
        }
    }
}

template <typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        T aux = contents[size_ - 1];
        size_--;
        return aux;
    }
}

template <typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        T aux = contents[0];
        for (size_t i = 0; i < size_; i++) {
            contents[i] = contents[i + 1];
        }
        size_--;
        return aux;
    }
}

template <typename T>
void structures::ArrayList<T>::remove(const T &data) {
    if (empty()) {
        throw std::out_of_range("A lista esta vazia!");
    } else {
        std::size_t index = find(data);
        if (index != size()) {
            for (size_t i = index; i < size() - 1; i++) {
                contents[i] = contents[i + 1];
            }
            size_--;
        } else {
            throw std::out_of_range("elemento nao esta na lista!");
        }
    }
}

template <typename T>
bool structures::ArrayList<T>::full() const {
    return (size() == max_size());
}

template <typename T>
bool structures::ArrayList<T>::empty() const {
    return (size() == 0);
}

template <typename T>
bool structures::ArrayList<T>::contains(const T &data) const {
    size_t index = find(data);
    return index != size();
}

template <typename T>
std::size_t structures::ArrayList<T>::find(const T &data) const {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else {
        for (std::size_t i = 0; i < size(); i++)
            if (contents[i] == data)
                return i;
    }
    return size();
}

template <typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template <typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template <typename T>
T &structures::ArrayList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("indice invalido!");
    } else {
        return contents[index];
    }
}

template <typename T>
T &structures::ArrayList<T>::operator[](std::size_t index) {
    return at(index);
}

template <typename T>
const T &structures::ArrayList<T>::at(std::size_t index) const {
    if (empty()) {
        throw std::out_of_range("lista vazia!");
    } else if (index < 0 || index > size_ - 1) {
        throw std::out_of_range("indice invalido!");
    } else {
        return contents[index];
    }
}

template <typename T>
const T &structures::ArrayList<T>::operator[](std::size_t index) const {
    return at(index);
}

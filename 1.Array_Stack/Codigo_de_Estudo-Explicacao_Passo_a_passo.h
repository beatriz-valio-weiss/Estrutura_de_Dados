// Copyright [2021] <BEATRIZ VALIO WEISS>
// Nota desse codigo 91/100

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>   // std::size_t
#include <stdexcept> // C++ exceptions

namespace structures
{
    //!Nome padronizado pelo programador devido ao nome da disciplina

    template <typename T>
    //! CLASSE PILHA
    class ArrayStack
    {
    public:
        //! construtor simples
        ArrayStack();
        //! construtor com parametro tamanho
        explicit ArrayStack(std::size_t max);
        //! destrutor
        ~ArrayStack();
        //! metodo empilha
        void push(const T &data);
        //! metodo desempilha
        T pop();
        //! metodo retorna o topo
        T &top();
        //! metodo limpa pilha
        void clear();
        //! metodo retorna tamanho
        std::size_t size();
        //! metodo retorna capacidade maxima
        std::size_t max_size();
        //! verifica se esta vazia
        bool empty();
        //! verifica se esta cheia
        bool full();

    private:
        T *contents;           //! nome do vetor
        int top_;              //! nome da variavel do ultimo valor alocado (-1, max_size_ - 1) = (vazia, cheia)
        std::size_t max_size_; //! quantidade de elementos do vetor

        static const auto DEFAULT_SIZE = 10u;
    };

} // namespace structures

#endif

//-----------------------------------------------------------------------------
//! Implementacao em arquivo unico por conta do VPL

template <typename T>
structures::ArrayStack<T>::ArrayStack()
{
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T>
structures::ArrayStack<T>::ArrayStack(std::size_t max)
{
    // Serve para unsigned int (tamanho sem sinal)
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template <typename T>
structures::ArrayStack<T>::~ArrayStack()
{
    // Desaloca o vetor
    delete[] contents;
}

template <typename T>
void structures::ArrayStack<T>::push(const T &data)
{
    // Codigo de empilhamento
    if (full())
    {
        throw std::out_of_range("pilha cheia");
    }
    else
    {
        top_++;
        contents[top_] = data;
    }
}

template <typename T>
T structures::ArrayStack<T>::pop()
{
    // Codigo de desempilhamento
    if (empty())
    {
        throw std::out_of_range("pilha vazia");
    }
    else
    {
        T aux;
        // Variavel aux eh para evitar alocar memoria atoa, entao utiliza-se a mesma variavel para todas as vezes que for desempilhar usando uma alocacao soh
        aux = contents[top_];
        top_--;
        return aux;
    }
}

template <typename T>
T &structures::ArrayStack<T>::top()
{
    // Retorna o topo (ultimo elemento) do vetor
    if (empty())
    {
        throw std::out_of_range("pilha vazia");
    }
    else
    {
        return contents[top_];
    }
}

template <typename T>
void structures::ArrayStack<T>::clear()
{
    // Limpa o topo (ultimo elemento) do vetor
    top_ = -1;
}

template <typename T>
std::size_t structures::ArrayStack<T>::size()
{
    // Retorna o tamanho do vetor
    return top_ + 1;
}

template <typename T>
std::size_t structures::ArrayStack<T>::max_size()
{
    // Retorna o tamanho maximo do vetor
    return max_size_;
}

template <typename T>
bool structures::ArrayStack<T>::empty()
{
    // Retorna se o vetor esta vazio
    if (top_ == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
    // Maneira clean code de implementar: return (top_ == -1)
}

template <typename T>
bool structures::ArrayStack<T>::full()
{
    // Retorna se o vetor esta cheio
    if (size() == max_size())
    {
        return true;
    }
    else
    {
        return false;
    }
    // Maneira clean code de implementar: return (top_ == static_cast<int>(max_size() - 1))
}

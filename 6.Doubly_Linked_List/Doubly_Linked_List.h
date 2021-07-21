//! Copyright [2021] <BEATRIZ VALIO WEISS>
// Nota desse codigo 100/100

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>   // std::size_t
#include <stdexcept> // C++ Exceptions

namespace structures
{

    //! Classe Lista Duplamente Encadeada
    template <typename T>
    class DoublyLinkedList
    {
    public:
        //! metodo construtor padrao
        DoublyLinkedList();
        //! metodo destrutor
        ~DoublyLinkedList();
        //! metodo limpar lista
        void clear();

        //! metodo inserir no fim
        void push_back(const T &data);
        //! metodo inserir no inicio
        void push_front(const T &data);
        //! metodo inserir na posicao
        void insert(const T &data, std::size_t index);
        //! metodo inserir em ordem
        void insert_sorted(const T &data);

        //! metodo retirar da posicao
        T pop(std::size_t index);
        //! metodo retirar do fim
        T pop_back();
        //! metodo retirar do inicio
        T pop_front();
        //! metodo remover dado especifico
        void remove(const T &data);

        //! metodo verifica lista vazia
        bool empty() const;
        //! metodo verifica se contem dado
        bool contains(const T &data) const;

        //! metodo acessar um elemento na posicao index
        // checando limites
        T &at(std::size_t index);
        //! metodo getter constante um elemento na posicao index
        const T &at(std::size_t index) const;

        //! metodo retorna posicao do dado
        std::size_t find(const T &data) const;
        //! metodo retorna tamanho da lista
        std::size_t size() const;

    private:
        class Node
        { // Elemento
        public:
            explicit Node(const T &data)
            {
                data_ = data;
                next_ = nullptr;
                prev_ = nullptr;
            }

            Node(const T &data, Node *next)
            {
                data_ = data;
                next_ = next;
                prev_ = nullptr;
            }

            Node(const T &data, Node *prev, Node *next)
            {
                data_ = data;
                prev_ = prev;
                next_ = next;
            }

            T &data()
            { // getter: dado
                return data_;
            }

            const T &data() const
            { // getter const: dado
                return data_;
            }

            Node *prev()
            {
                return prev_;
            }

            const Node *prev() const
            {
                return prev_;
            }

            void prev(Node *node)
            {
                prev_ = node;
            }

            Node *next()
            { // getter: próximo
                return next_;
            }

            const Node *next() const
            { // getter const: próximo
                return next_;
            }

            void next(Node *node)
            { // setter: próximo
                next_ = node;
            }

        private:
            T data_;
            Node *prev_;
            Node *next_;
        };

        Node *end()
        { // último node da lista
            auto it = head;
            for (auto i = 1u; i < size(); ++i)
            {
                it = it->next();
            }
            return it;
        }

        Node *current(std::size_t index)
        { // node do indice
            Node *it = head;
            for (std::size_t i = 0; i < size(); ++i)
            {
                if (i == index)
                {
                    return it;
                }
                it = it->next();
            }
            return it;
        }

        Node *head{nullptr};
        Node *tail{nullptr};
        std::size_t size_{0u};
    };

} // namespace structures

#endif

//-----------------------------------------------------------------------------

template <typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList()
{
}

template <typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList()
{
    clear();
}

template <typename T>
void structures::DoublyLinkedList<T>::clear()
{
    while (size() != 0)
    {
        pop_front();
    }
}

template <typename T>
void structures::DoublyLinkedList<T>::push_back(const T &data)
{
    insert(data, size_);
}

template <typename T>
void structures::DoublyLinkedList<T>::push_front(const T &data)
{
    Node *novo = new Node(data, head);
    if (novo == nullptr)
    {
        delete novo;
        throw std::out_of_range("lista cheia!");
    }
    else
    {
        if (head != nullptr)
        {
            head->prev(novo);
        }
        else
        {
            tail = novo;
        }
        head = novo;
        size_++;
    }
}

template <typename T>
void structures::DoublyLinkedList<T>::insert(const T &data, std::size_t index)
{
    Node *novo = new Node(data);
    Node *anterior;
    if (novo == nullptr)
    {
        delete novo;
        throw std::out_of_range("lista cheia!");
    }
    else if (index > size_)
    {
        delete novo;
        throw std::out_of_range("indice invalido!");
    }
    else if (index == 0)
    {
        delete novo;
        push_front(data);
    }
    else
    {
        anterior = current(index - 1);
        novo->next(anterior->next());
        anterior->next(novo);
        novo->prev(anterior);
        if (novo->next() != nullptr)
        {
            novo->next()->prev(novo);
        }
        if (index == size_)
        {
            tail = novo;
        }
        size_++;
    }
}

template <typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T &data)
{
    Node *anterior;
    if (empty())
    {
        push_front(data);
    }
    else
    {
        anterior = head;
        for (std::size_t i = 0; i != size_; i++)
        {
            if (anterior->data() > data)
            {
                insert(data, i);
                break;
            }
            else if (i == (size_ - 1))
            {
                push_back(data);
                break;
            }
            else
            {
                anterior = anterior->next();
            }
        }
    }
}

template <typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index)
{
    Node *aux, *anterior, *posterior;
    T dado;
    if (empty())
    {
        throw("lista vazia");
    }
    else if (index < 0 || index > size_ - 1)
    {
        throw std::out_of_range("indice invalido!");
    }
    else if (index == 0)
    {
        dado = pop_front();
    }
    else
    {
        aux = current(index);
        posterior = aux->next();
        anterior = aux->prev();
        if (anterior != nullptr)
        {
            anterior->next(posterior);
        }
        if (posterior != nullptr)
        {
            posterior->prev(anterior);
        }
        if (index == (size_ - 1))
        {
            tail = anterior;
        }
        dado = aux->data();
        delete aux;
        size_--;
    }
    return dado;
}

template <typename T>
T structures::DoublyLinkedList<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("lista vazia!");
    }
    else
    {
        T dado = pop(size_ - 1);
        return dado;
    }
}

template <typename T>
T structures::DoublyLinkedList<T>::pop_front()
{
    Node *aux;
    if (empty())
    {
        throw std::out_of_range("lista vazia!");
    }
    else
    {
        aux = head;
        head = head->next();
        T dado = aux->data();
        delete aux;
        size_--;
        return dado;
    }
}

template <typename T>
void structures::DoublyLinkedList<T>::remove(const T &data)
{
    if (empty())
    {
        throw std::out_of_range("lista vazia!");
    }
    else
    {
        std::size_t index = find(data);
        pop(index);
    }
}

template <typename T>
bool structures::DoublyLinkedList<T>::empty() const
{
    return size() == 0;
}

template <typename T>
bool structures::DoublyLinkedList<T>::contains(const T &data) const
{
    Node *aux;
    if (empty())
    {
        throw std::out_of_range("lista vazia");
    }
    else
    {
        aux = head;
        for (std::size_t i = 0; i != size_; i++)
        {
            if (aux->data() == data)
            {
                return true;
            }
            aux = aux->next();
        }
        return false;
    }
}

template <typename T>
T &structures::DoublyLinkedList<T>::at(std::size_t index)
{
    Node *it;
    if (index > size())
    {
        throw std::out_of_range("indice invalido!");
    }
    else if (empty())
    {
        throw std::out_of_range("lista vazia!");
    }
    else
    {
        it = current(index);
        return it->data();
    }
}

template <typename T>
const T &structures::DoublyLinkedList<T>::at(std::size_t index) const
{
    Node *it;
    if (index > size())
    {
        throw std::out_of_range("indice invalido!");
    }
    else if (empty())
    {
        throw std::out_of_range("lista vazia!");
    }
    else
    {
        it = current(index);
        return it->data();
    }
}

template <typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T &data) const
{
    Node *aux;
    if (empty())
    {
        throw std::out_of_range("lista vazia");
    }
    else
    {
        aux = head;
        for (std::size_t i = 0; i != size_; i++)
        {
            if (aux->data() == data)
            {
                return i;
            }
            aux = aux->next();
        }
    }
    return size_;
}

template <typename T>
std::size_t structures::DoublyLinkedList<T>::size() const
{
    return size_;
}

#ifndef CUSTOMLINKEDLIST_H
#define CUSTOMLINKEDLIST_H

#include <functional>

template <typename T>
class LinkedList
{
public:

    struct Node
    {
        T m_value;
        Node* m_pNext = nullptr;
    };

    ~LinkedList()
    {
        while (m_pHead != nullptr)
        {
            PopFront();
        }
    }

    void PushFront(T value)
    {
        Node* pOld = m_pHead;

        m_pHead = new Node{value, pOld};
    }

    void InsertAfter(Node* pNode, const T& value)
    {
        if(pNode == nullptr)
        {
            PushFront(value);

            return;
        }

        Node* pNewnode = new Node{value, pNode->m_pNext};

        pNode->m_pNext = pNewnode;
    }

    void RemoveAfter(Node* pNode)
    {
        if(pNode == nullptr)
        {
            return;
        }

        Node* pNextNode = pNode->m_pNext;

        if(pNextNode != nullptr)
        {
            pNode->m_pNext = pNextNode->m_pNext;

            delete pNextNode;
        }
    }

    void Remove(Node* pNode)
    {
        if(pNode == nullptr)
        {
            return;
        }

        if(pNode == m_pHead)
        {
            PopFront();

            return;
        }


        Node* pBeforeNode = m_pHead;

        while(pBeforeNode->m_pNext != pNode)
        {
            pBeforeNode = pBeforeNode->m_pNext;

            if(pBeforeNode == nullptr) //Защита от бесконечного цикла
            {
                return;
            }
        }

        RemoveAfter(pBeforeNode);
    }

    void PopFront()
    {
        if(m_pHead == nullptr)
        {
            return;
        }

        Node* pNewHead = m_pHead->m_pNext;

        delete m_pHead;

        m_pHead = pNewHead;
    }

    Node* GetHead()
    {
        return m_pHead;
    }

    const Node* GetHead() const
    {
        return m_pHead;
    }

    size_t GetSize() const
    {
        size_t nSize = 0;

        Node* pNode = m_pHead;

        while(pNode != nullptr)
        {
            pNode = pNode->m_pNext;

            ++nSize;
        }

        return nSize;
    }

    Node* Find(const T& value)
    {
        Node* pNode = m_pHead;

        while (pNode != nullptr)
        {
            const T currentVal = pNode->m_value;

            if(currentVal == value)
            {
                break;
            }

            pNode = pNode->m_pNext;
        }

        return pNode;
    }


    void SortBySelection(const std::function<bool(const T&, const T&)>& predicate)
    {
        LinkedList<T>::Node* pHead = this->GetHead();

        LinkedList<T>::Node* a = nullptr,
                                *b = nullptr,
                                *p = nullptr,
                                *pHeaderNode = nullptr;

        for(LinkedList<T>::Node* pCurrentNode = pHead; pCurrentNode != nullptr; )
        {
            a = pCurrentNode;
            pCurrentNode = pCurrentNode->m_pNext;
            b = pHeaderNode;

            for(p = nullptr; (b != nullptr) && predicate(b->m_value, a->m_value); )
            {
                p = b;
                b = b->m_pNext;
            }

            if(p == nullptr)
            {
                a->m_pNext = pHeaderNode;
                pHeaderNode       = a;
            }
            else
            {
                a->m_pNext = b;
                p->m_pNext = a;
            }
        }

        if(pHeaderNode != nullptr)
        {
            m_pHead = pHeaderNode;
        }
    }

private:
    Node* m_pHead = nullptr;
};

#endif // CUSTOMLINKEDLIST_H

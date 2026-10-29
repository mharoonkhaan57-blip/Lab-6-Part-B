#ifndef LAB06_PART_B_CIRCULAR_LIST_H
#define LAB06_PART_B_CIRCULAR_LIST_H

/* Name: M.Haroon-Ur-Rasheed Khan | Reg. No: Ai-9 | Subject: DSA | Sec: A */
// Lab 06 Part B: Circular featured-book display

#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct FeaturedNode
{
    int id;
    string title;
    FeaturedNode* next;

    FeaturedNode(int bookID, const string& bookTitle)
        : id(bookID), title(bookTitle), next(nullptr) {}
};

class FeaturedBooks
{
private:
    FeaturedNode* tail;
    FeaturedNode* current;
    int count;

    FeaturedNode* first() const
    {
        return tail == nullptr ? nullptr : tail->next;
    }

    FeaturedNode* getNodeAt(int index) const
    {
        FeaturedNode* node = first();
        while (index-- > 0)
            node = node->next;
        return node;
    }

    void clear()
    {
        while (count > 0)
            delete Remove();
    }

public:
    FeaturedBooks() : tail(nullptr), current(nullptr), count(0) {}

    FeaturedBooks(const FeaturedBooks& other)
        : tail(nullptr), current(nullptr), count(0)
    {
        FeaturedNode* node = other.first();
        for (int i = 0; i < other.count; i++)
        {
            InsertAt(new FeaturedNode(node->id, node->title), count);
            node = node->next;
        }
    }

    FeaturedBooks& operator=(const FeaturedBooks& other)
    {
        if (this != &other)
        {
            clear();
            FeaturedNode* node = other.first();
            for (int i = 0; i < other.count; i++)
            {
                InsertAt(new FeaturedNode(node->id, node->title), count);
                node = node->next;
            }
        }
        return *this;
    }

    ~FeaturedBooks() { clear(); }

    bool IsEmpty() const { return count == 0; }
    bool IsNotEmpty() const { return count > 0; }

    void Insert(FeaturedNode* book)
    {
        if (book == nullptr)
            return;

        if (tail == nullptr)
        {
            tail = book;
            book->next = book;
            current = book;
        }
        else
        {
            book->next = tail->next;
            tail->next = book;
        }
        count++;
    }

    FeaturedNode* Remove()
    {
        if (tail == nullptr)
            return nullptr;

        FeaturedNode* firstBook = tail->next;
        if (firstBook == tail)
        {
            tail = nullptr;
            current = nullptr;
        }
        else
        {
            tail->next = firstBook->next;
            if (current == firstBook)
                current = firstBook->next;
        }

        firstBook->next = nullptr;
        count--;
        return firstBook;
    }

    void InsertAt(FeaturedNode* book, int index)
    {
        if (book == nullptr)
            return;
        if (count == 0)
        {
            Insert(book);
            return;
        }
        if (index < 0)
            index = ((index % count) + count) % count;
        else if (index > count)
            index %= count;

        if (index == 0)
        {
            Insert(book);
            return;
        }

        book->next = tail->next;
        if (index == count)
        {
            tail->next = book;
            tail = book;
        }
        else
        {
            FeaturedNode* previous = getNodeAt(index - 1);
            book->next = previous->next;
            previous->next = book;
        }
        count++;
    }

    FeaturedNode* RemoveAt(int index)
    {
        if (count == 0)
            return nullptr;
        index = ((index % count) + count) % count;
        if (index == 0)
            return Remove();

        FeaturedNode* previous = getNodeAt(index - 1);
        FeaturedNode* removed = previous->next;
        previous->next = removed->next;
        if (removed == tail)
            tail = previous;
        if (current == removed)
            current = removed->next;
        removed->next = nullptr;
        count--;
        return removed;
    }

    void Swap(int firstIndex, int secondIndex)
    {
        if (count == 0)
            return;
        firstIndex = ((firstIndex % count) + count) % count;
        secondIndex = ((secondIndex % count) + count) % count;
        if (firstIndex == secondIndex)
            return;

        FeaturedNode* firstBook = getNodeAt(firstIndex);
        FeaturedNode* secondBook = getNodeAt(secondIndex);
        swap(firstBook->id, secondBook->id);
        swap(firstBook->title, secondBook->title);
    }

    void Sort()
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                FeaturedNode* firstBook = getNodeAt(i);
                FeaturedNode* secondBook = getNodeAt(j);
                if (firstBook->id > secondBook->id)
                {
                    swap(firstBook->id, secondBook->id);
                    swap(firstBook->title, secondBook->title);
                }
            }
        }
    }

    void Reverse()
    {
        if (count < 2)
            return;

        FeaturedNode* oldTail = tail;
        FeaturedNode* oldFirst = tail->next;
        FeaturedNode* previous = oldTail;
        FeaturedNode* node = oldFirst;

        while (node != oldTail)
        {
            FeaturedNode* next = node->next;
            node->next = previous;
            previous = node;
            node = next;
        }

        oldTail->next = previous;
        tail = oldFirst;
    }

    void MoveNext()
    {
        if (current != nullptr)
            current = current->next;
    }

    void Print() const
    {
        if (count == 0)
        {
            cout << "No featured books.\n";
            return;
        }

        FeaturedNode* node = first();
        for (int i = 0; i < count; i++)
        {
            cout << node->id << " - " << node->title;
            if (node == current)
                cout << " [CURRENT]";
            cout << '\n';
            node = node->next;
        }
    }
};

#endif

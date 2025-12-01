/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     */
     size_t mysize = hashes::hash(key, size);
     std::pair<K, V> myPair (key, value);
     table[mysize].push_front(myPair);
     elems++;
     if (shouldResize()) {
        resizeTable();
     }

}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    size_t mysize = hashes::hash(key, size);

    typename std::list<std::pair<K, V>>::iterator it = table[mysize].begin();
    while (it != table[mysize].end()) {
        if (it->first == key) {
            table[mysize].erase(it);
            elems--;
            return;
        }
        it++;
    }
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    //(void) key; // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    size_t mysize = hashes::hash(key, size);

    typename std::list<std::pair<K, V>>::const_iterator it;
    for (it = table[mysize].begin(); it != table[mysize].end(); it++) {
        if (it->first == key) {
            return it->second;
        }
    }

    /**
     * @todo: Implement this function.
     */

    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    size_t myNewSize = findPrime(size * 2);
    std::list<std::pair<K, V>>* myNewTable = new std::list<std::pair<K, V>>[myNewSize];

    for (size_t i = 0; i < size; i++) {
        typename std::list<std::pair<K, V>>::iterator it;
        for (it = table[i].begin(); it != table[i].end(); it++) {
            K const& key = it->first;
            V const& value = it->second;

            size_t newOne = hashes::hash(key, myNewSize);
            std::pair<K, V> myPair(key, value);
            myNewTable[newOne].push_front(myPair);
        }
    }

    delete[] table;
    table = myNewTable;
    size = myNewSize;

    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
}

template <typename T>
Node<T>::Node(T key) : key(key) {}

template <typename T>
T Node<T>::get_key() const
{
    return key;
}
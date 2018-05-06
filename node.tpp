template <typename I, typename K>
Node<I, K>::Node(I id, K key) : id(id), key(key) {}

template <typename I, typename K>
I Node<I, K>::get_id() const
{
    return id;
}

template <typename I, typename K>
K Node<I, K>::get_key() const
{
    return key;
}
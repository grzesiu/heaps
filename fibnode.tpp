template <typename T>
Fibnode<T>::Fibnode(T key) : Node<T>::Node(key) {}

template <typename T>
bool Fibnode<T>::is_marked() const
{
    return this->marked;
}
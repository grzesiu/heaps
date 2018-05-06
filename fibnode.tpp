template <typename I, typename K>
Fibnode<I, K>::Fibnode(I id, K key) : Node<I, K>::Node(id, key) {}

template <typename I, typename K>
bool Fibnode<I, K>::is_marked() const
{
    return this->marked;
}
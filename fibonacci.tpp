template <typename T>
Fibonacci<T>::Fibonacci() : root(nullptr) {}

template <typename T>
Fibonacci<T>::Fibonacci(std::function<bool(T const &, T const &)> comp) : root(nullptr)
{
}

template <typename T>
bool Fibonacci<T>::empty() const
{
    return false;
}

template <typename T>
unsigned int Fibonacci<T>::size() const
{
    return n;
}

template <typename T>
const T Fibonacci<T>::top() const
{
}

template <typename T>
void Fibonacci<T>::push(T val)
{
    Node *node = new Node(val);
}

template <typename T>
const T Fibonacci<T>::pop()
{
}

template <typename T>
void Fibonacci<T>::decrease_key(Node &node, T key)
{
}

template <typename T>
Fibonacci<T>::Node::Node(T key) : key(key) {}

template <typename T>
bool Fibonacci<T>::Node::is_marked() const
{
}

template <typename T>
bool Fibonacci<T>::Node::get_value() const
{
}

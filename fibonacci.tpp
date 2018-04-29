template <typename T>
Fibonacci<T>::Fibonacci()
{
}

template <typename T>
Fibonacci<T>::Fibonacci(std::function<bool(T const &, T const &)> comp)
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
}

template <typename T>
const T &Fibonacci<T>::top() const
{
}

template <typename T>
void Fibonacci<T>::push(const T &val)
{
}

template <typename T>
void Fibonacci<T>::pop()
{
}

template <typename T>
void Fibonacci<T>::decrease_key(Node &node, T key)
{
}

template <typename T>
Fibonacci<T>::Node::Node(T key)
{
}

template <typename T>
bool Fibonacci<T>::Node::is_marked() const
{
}

template <typename T>
bool Fibonacci<T>::Node::get_value() const
{
}

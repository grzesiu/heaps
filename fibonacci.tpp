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
void Fibonacci<T>::push(Node *node)
{
    if (root == nullptr)
    {
        root = node->left = node->right = node;
    }
    else
    {
        Node *root_right = root->right;
        root->right = node;
        root_right->left = node;
        node->right = root_right;
        node->left = root;

        if (node->key < root->key)
        {
            node = root;
        }
    }
}

template <typename T>
const T Fibonacci<T>::pop()
{
}

template <typename T>
void Fibonacci<T>::decrease_key(Node *node, T key)
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

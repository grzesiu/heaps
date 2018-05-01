template <typename T>
Dary<T>::Dary(std::vector<T> nodes, unsigned int d) : nodes(nodes), d(d) {}

template <typename T>
bool Dary<T>::empty() const {}

template <typename T>
unsigned int Dary<T>::size() const {}

template <typename T>
T Dary<T>::top() const {}

template <typename T>
void Dary<T>::push(T val) {}

template <typename T>
void Dary<T>::pop() {}
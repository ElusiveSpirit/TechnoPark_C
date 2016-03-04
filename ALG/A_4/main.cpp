#include "iostream"

int main() {
    std::cout << "Hello world" << std::endl;
    return 0;
}


class Deq {
public:
    Deq( int size );
    ~Deq() { delete[] buffer; };

    void pushBack( int );
    void pushFront( int );
    int popBack();
    int popFront();

    bool isEmpty() const { return head == tail; };

private:
    int *buffer;
    int bufferSize;
    int head;
    int tail;
};

Deq::Deq( int size ) :
    bufferSize(size),
    head( 0 ),
    tail( 0 )
{
    buffer = new int[bufferSize];
}

Deq::pushBack( int number ) {
    assert( ( tail + 1 ) % bufferSize != head );
    buffer[tail] = a;
    tail = ( tail + 1 ) % bufferSize;
}

Deq::pushFront( int number ) {
    if (--head == -1) head = bufferSize - 1;
    if (head == tail) {
        head = ( head + 1 ) % bufferSize;
        return;
    }
    buffer[head] = number;
}

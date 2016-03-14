class Stack {
public:
    Stack();
    Stack( char size );
    ~Stack() { free(buffer); };

    // Методы доступа
    void push( char );
    char pop();

    bool isEmpty() const { return top == -1; };

private:
    // Расширяет выделенную под массив память
    // 0 - OK
    // 1 - error
    int expandBuffer();

    // Приватные переменные
    char *buffer;
    char bufferSize;
    char top;

#define DEFAULT_DEQ_SIZE 2
};

void Stack::push( char ch ) {
    if ( top + 1 == bufferSize )
        if (expandBuffer() == 1)
            return;
    buffer[++top] = ch;
}

char Stack::pop() {
    if ( top == -1 )
        return 0;

    return buffer[top--];
}

int Stack::expandBuffer() {
    char *pTemp = (char *)realloc(buffer, bufferSize * 2 * sizeof(char));
    if (pTemp == NULL) {
        return 1;
    }
    buffer = pTemp;
    bufferSize *= 2;
    return 0;
}

Stack::Stack() :
    bufferSize( DEFAULT_DEQ_SIZE ),
    top( -1 )
{
    buffer = (char *)malloc(DEFAULT_DEQ_SIZE * sizeof(char));
}

Stack::Stack( char size ) :
    bufferSize( size ),
    top( -1 )
{
    buffer = (char *)malloc(size * sizeof(char));
}

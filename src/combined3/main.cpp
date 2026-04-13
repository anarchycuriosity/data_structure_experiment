#include "head.h"
int main()
{
    std::vector<int> test1 = {1, 2, 3, 4, 5};
    Queue q(test1);
    Stack st;
    int sort_count = 0;
    // get(q, st, pop, ins, sort_count);
    get(q, st, sort_count);
    std::cout << sort_count;
}
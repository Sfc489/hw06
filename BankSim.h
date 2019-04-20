#ifndef HW06_BANKSIM_H
#define HW06_BANKSIM_H

#include <iostream>

class BankQueue {
public:
    int currentTime;

    bool teller;

    bool isEmpty() const;

    bool enqueue(int newEntry);

    bool dequeue();

    int peekFront();

    void arrivalEvent();

    friend std::ostream& operator<<(std::ostream& os, const BankQueue& bankQueue);
};

#endif //HW06_BANKSIM_H

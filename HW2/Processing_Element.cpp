#include "Processing_Element.h"

//----------------------vvvvv put your code here vvvvv------------------------------

void Processing_Element::Reset() {
    if (reset) {
        dataCount = 0;
        sumCount = 0;
    }
}

void Processing_Element::ReqFromNI() {
    if (dataCount != 8) {
        PE_ack_in = 1;
    } else {
        PE_ack_in = 0;
    }
}

void Processing_Element::ReceiveData() {
    dataBuffer[dataCount] = Data_in;
    dataCount += 1;
}

void Processing_Element::PartialSum() {
    if (dataCount >= 4) {
        sumBuffer[sumCount] = dataBuffer[0] * dataBuffer[1] + dataBuffer[2] * dataBuffer[3];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 7; j++) {
                dataBuffer[j] = dataBuffer[j + 1];
            }
        }
        sumCount += 1;
        dataCount -= 4;
    }
}

void Processing_Element::ReqToNI() {
    PE_req_out = 1;
}

void Processing_Element::AckFromNI() {
    if (PE_ack_out == 1) {
        Data_out = sumBuffer[sumCount - 1];
        sumCount -= 1;
    }
}

//----------------------^^^^^ put your code here ^^^^^------------------------------
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
        sumBuffer[sumCount] = (sc_lv<DATA_LENGTH>)((sc_int<DATA_LENGTH>)dataBuffer[0] * (sc_int<DATA_LENGTH>)dataBuffer[1] + (sc_int<DATA_LENGTH>)dataBuffer[2] * (sc_int<DATA_LENGTH>)dataBuffer[3]);
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
    if (sumCount != 0) {
        PE_req_out = 1;
    }
}

void Processing_Element::AckFromNI() {
    if (PE_ack_out == 1) {
        Data_out = sumBuffer[sumCount - 1];
        sumCount -= 1;
    }
}

//----------------------^^^^^ put your code here ^^^^^------------------------------
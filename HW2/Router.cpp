#include "Router.h"

//----------------------vvvvv put your code here vvvvv------------------------------

void Router::Reset() {
    if (reset) {
        northEn = 0;
        westEn = 0;
        southEn = 0;
        eastEn = 0;
        localEn = 0;
    }
}

void Router::TransPacket() {
    if (North_in && northEn < 2) {
        packetBuffer[northEn] = North_in;
        northEn += 1;
    }
    if (West_in && westEn < 2) {
        packetBuffer[westEn + 2] = West_in;
        westEn += 1;
    }
    if (South_in && southEn < 2) {
        packetBuffer[westEn + 4] = South_in;
        southEn += 1;
    }
    if (East_in && eastEn < 2) {
        packetBuffer[eastEn + 6] = East_in;
        eastEn += 1;
    }
}

void Router::TransFlag() {
    if (!temp) {
        for (int i = 0; i < 8; i++) {
            if (packetBuffer[i].range(25,22) == "0101") {
                L_req_out = 1;
                temp = packetBuffer[i];
                packetBuffer[i] = 0;
                if (i < 2) {
                    northEn -= 1;
                } else if (i < 4) {
                    westEn -= 1;
                } else if (i < 6) {
                    southEn -= 1;
                } else {
                    eastEn -= 1;
                }
                break;
            }
        }
    }
}

void Router::TransToLocal() {
    if (L_ack_out) {
        Local_out = temp;
    }
}

void Router::ReceiveSignal() {
    if (L_req_in && localEn < 8) {
        L_ack_in = 1;
    }
}

void Router::ReceiveLocalPacket() {
    dataBuffer[localEn] = Local_in;
    localEn += 1;
}

void Router::TransPacketToNorth() {
    for (int i = 0; i < 8; i++) {
        if (packetBuffer[i].range(25,22) == "0100") {
            North_out = packetBuffer[i];
            packetBuffer[i] = 0;
            if (i < 2) {
                northEn -= 1;
            } else if (i < 4) {
                westEn -= 1;
            } else if (i < 6) {
                southEn -= 1;
            } else {
                eastEn -= 1;
            }
            break;
        }
    }
}

void Router::TransPacketToWest() {
    for (int i = 0; i < 8; i++) {
        if (packetBuffer[i].range(25,22) == "1001") {
            West_out = packetBuffer[i];
            packetBuffer[i] = 0;
            if (i < 2) {
                northEn -= 1;
            } else if (i < 4) {
                westEn -= 1;
            } else if (i < 6) {
                southEn -= 1;
            } else {
                eastEn -= 1;
            }
            break;
        }
    }
}

void Router::TransPacketToSouth() {
    for (int i = 0; i < 8; i++) {
        if (packetBuffer[i].range(25,22) == "0110") {
            South_out = packetBuffer[i];
            packetBuffer[i] = 0;
            if (i < 2) {
                northEn -= 1;
            } else if (i < 4) {
                westEn -= 1;
            } else if (i < 6) {
                southEn -= 1;
            } else {
                eastEn -= 1;
            }
            break;
        }
    }
}

void Router::TransPacketToEast() {
    for (int i = 0; i < 8; i++) {
        if (packetBuffer[i].range(25,22) == "0001") {
            East_out = packetBuffer[i];
            packetBuffer[i] = 0;
            if (i < 2) {
                northEn -= 1;
            } else if (i < 4) {
                westEn -= 1;
            } else if (i < 6) {
                southEn -= 1;
            } else {
                eastEn -= 1;
            }
            break;
        }
    }
}

//----------------------^^^^^ put your code here ^^^^^------------------------------
#include "Router.h"

//----------------------vvvvv put your code here vvvvv------------------------------

void Router::Reset() {
    if (reset) {
        northEn = 0;
        westEn = 0;
        southEn = 0;
        eastEn = 0;
        localEn = 0;
        tempEn = true;
        northC = westC = southC = eastC = false;
    }
}

void Router::ReceiveNorthPacket() {
    if (northEn < 2) {
        packetBuffer[northEn] = North_in;
        northEn += 1;
    }
}

void Router::ReceiveWestPacket() {
    if (westEn < 2) {
        packetBuffer[westEn + 2] = West_in;
        westEn += 1;
    }
}

void Router::ReceiveSouthPacket() {
    if (southEn < 2) {
        packetBuffer[southEn + 4] = South_in;
        southEn += 1;
    }
}

void Router::ReceiveEastPacket() {
    if (eastEn < 2) {
        packetBuffer[eastEn + 6] = East_in;
        eastEn += 1;
    }
}

void Router::ShowReceivePacket() {
    cout << "North In:\t" << North_in << endl;
    cout << "West In:\t" << West_in << endl;
    cout << "South In:\t" << South_in << endl;
    cout << "East In:\t" << East_in << endl;
}

void Router::ShowPacketInMemory() {
    cout << "Packet Buffer:\n";
    cout << "Dest_Y\tDest_X\n";
    for (int i = 0; i < 8; i++) {
        cout << packetBuffer[i].range(25,24) << "\t" << packetBuffer[i].range(23,22) << endl;
    }
    cout << "--------------\n";
    cout << "  En Count:   \n";
    cout << northEn << endl;
    cout << westEn << endl;
    cout << southEn << endl;
    cout << eastEn << endl;
    cout << "--------------\n";
}

void Router::TransFlag() {
    if (tempEn) {
        for (int i = 0; i < 8; i++) {
            if (packetBuffer[i].range(25,22) == "0101") {
                L_req_out = 1;
                temp = packetBuffer[i];
                if (i % 2 != 0) {
                    packetBuffer[i] = packetBuffer[i + 1];
                    packetBuffer[i + 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                } else {
                    packetBuffer[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
                }
                tempEn = false;
                if (i < 2) {
                    northEn = (northEn > 0) ? northEn - 1 : 0;
                } else if (i < 4) {
                    westEn = (westEn > 0) ? westEn - 1 : 0;
                } else if (i < 6) {
                    southEn = (southEn > 0) ? southEn - 1 : 0;
                } else {
                    eastEn = (eastEn > 0) ? eastEn - 1 : 0;
                }
                break;
            }
        }
    }
    cout << "Data\t" << temp << "\nFlag\t" << L_req_out << endl;
}

void Router::TransToLocal() {
    cout << "Get Signal From NI" << endl;
    Local_out = temp;
    temp = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    tempEn = true;
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
        if (packetBuffer[i].range(23,22) == "00") {
            North_out = packetBuffer[i];
            northC = true;
            if (i % 2 != 0) {
                packetBuffer[i] = packetBuffer[i + 1];
                packetBuffer[i + 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            } else {
                packetBuffer[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            }
            if (i < 2) {
                northEn = (northEn > 0) ? northEn - 1 : 0;
            } else if (i < 4) {
                westEn = (westEn > 0) ? westEn - 1 : 0;
            } else if (i < 6) {
                southEn = (southEn > 0) ? southEn - 1 : 0;
            } else {
                eastEn = (eastEn > 0) ? eastEn - 1 : 0;
            }
            break;
        }
    }
}

void Router::TransPacketToWest() {
    sendData = false;
    for (int i = 0; i < 8; i++) {
        if ((packetBuffer[i].range(25,24) == "10" || packetBuffer[i].range(25,24) == "11") && (packetBuffer[i].range(23,22) == "00" || packetBuffer[i].range(23,22) == "01")) {
            sendData = true;
            westC = true;
            West_out = packetBuffer[i];
            if (i % 2 != 0) {
                packetBuffer[i] = packetBuffer[i + 1];
                packetBuffer[i + 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            } else {
                packetBuffer[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            }
            if (i < 2) {
                northEn = (northEn > 0) ? northEn - 1 : 0;
            } else if (i < 4) {
                westEn = (westEn > 0) ? westEn - 1 : 0;
            } else if (i < 6) {
                southEn = (southEn > 0) ? southEn - 1 : 0;
            } else {
                eastEn = (eastEn > 0) ? eastEn - 1 : 0;
            }
            break;
        }
    }
    if (!sendData && localEn != 0) {
        West_out = dataBuffer[0];
        westC = true;
        for (int i = 0; i < localEn - 1; i++) {
            dataBuffer[i] = dataBuffer[i + 1];
        }
        dataBuffer[localEn - 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        localEn -= 1;
    }
}

void Router::TransPacketToSouth() {
    for (int i = 0; i < 8; i++) {
        if ((packetBuffer[i].range(23,22) == "10" || packetBuffer[i].range(23,22) == "11")) {
            South_out = packetBuffer[i];
            southC = true;
            if (i % 2 != 0) {
                packetBuffer[i] = packetBuffer[i + 1];
                packetBuffer[i + 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            } else {
                packetBuffer[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            }
            if (i < 2) {
                northEn = (northEn > 0) ? northEn - 1 : 0;
            } else if (i < 4) {
                westEn = (westEn > 0) ? westEn - 1 : 0;
            } else if (i < 6) {
                southEn = (southEn > 0) ? southEn - 1 : 0;
            } else {
                eastEn = (eastEn > 0) ? eastEn - 1 : 0;
            }
            break;
        }
    }
}

void Router::TransPacketToEast() {
    for (int i = 0; i < 8; i++) {
        if (packetBuffer[i].range(25,24) == "00" && packetBuffer[i].range(23,22) != "00") {
            East_out = packetBuffer[i];
            eastC = true;
            if (i % 2 != 0) {
                packetBuffer[i] = packetBuffer[i + 1];
                packetBuffer[i + 1] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            } else {
                packetBuffer[i] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            }
            if (i < 2) {
                northEn = (northEn > 0) ? northEn - 1 : 0;
            } else if (i < 4) {
                westEn = (westEn > 0) ? westEn - 1 : 0;
            } else if (i < 6) {
                southEn = (southEn > 0) ? southEn - 1 : 0;
            } else {
                eastEn = (eastEn > 0) ? eastEn - 1 : 0;
            }
            break;
        }
    }
}

void Router::ClearSendPacket() {
    if (northC) {
        North_out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        northC = false;
    }
    if (westC) {
        West_out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        westC = false;
    }
    if (southC) {
        South_out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        southC = false;
    }
    if (eastC) {
        East_out = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        eastC = false;
    }
}

//----------------------^^^^^ put your code here ^^^^^------------------------------
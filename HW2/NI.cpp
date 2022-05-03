#include "NI.h"

//----------------------vvvvv put your code here vvvvv------------------------------

void Network_Interface::Reset() {
    if (reset) {
        flitFromRouter = 0;
        flitToRouter = 0;
        dataFromPE = 0;
        dataToPE = 0;
        reqRouterEn = false;
    }
}

void Network_Interface::AckToRouter() { // Receive L_req_in signal, if buffer is not full, then send L_ack_in
    cout << "Get Request Signal From Router" << endl;
    if (flitFromRouter < 4) {
        L_ack_in = 1;
        reqRouterEn = true;
    }
}

void Network_Interface::ReceiveFlitFromRouter() {
    // if (reqRouterEn) {
    flitBuffer[flitFromRouter] = Flit_in;
    flitFromRouter += 1;
    reqRouterEn = false;
    // }
    // cout << "Flit Stack Count\n";
    // cout << flitFromRouter << endl;
    // cout << "Flit Buffer\n";
    // for (int i = 0; i < 4; i++) {
    //     cout << flitBuffer[i] << endl;
    // }
    // cout << "-----------\n";
}

void Network_Interface::ReqToRouter() { // Send L_req_out signal, if router is not full, then receive L_ack_out
    if (flitToRouter != 0) {
        L_req_out = 1;
    }
}

void Network_Interface::SendFlitToRouter() {
    if (L_ack_out) {
        Flit_out = flitBuffer[4];
        for (int i = 4; i < 4 + flitToRouter - 1; i++) {
            flitBuffer[i] = flitBuffer[i + 1];
        }
    }
}

void Network_Interface::AckToPE() { // Receive PE_req_in signal, if buffer is not full, then send PE_ack_in
    if (dataFromPE < 4) {
        PE_ack_in = 1;
    }
}

void Network_Interface::ReceiveDataFromPE() {
    dataBuffer[4 + dataFromPE] = Data_out;
    dataFromPE += 1;
}

void Network_Interface::ReqToPE() { // Send PE_req_out signal, if PE is not full, then receive PE_ack_out
    if (dataToPE != 0) {
        PE_req_out = 1;
    }
}

void Network_Interface::SendDataToPE() {
    if (PE_ack_out) {
        Data_in = dataBuffer[0];
        for (int i = 0; i < dataToPE - 1; i++) {
            dataBuffer[i] = dataBuffer[i + 1];
        }
    }
}

void Network_Interface::PacketDataToFlit() {
    if (dataFromPE == 4 && flitToRouter < 4) {
        flitBuffer[flitToRouter].range(21, 0) = dataBuffer[4];
        flitBuffer[flitToRouter].range(25,22) = "1001";
        flitBuffer[flitToRouter].range(29,26) = "0101";
        flitBuffer[flitToRouter].range(31,30) = "01";
        flitToRouter += 1;
    }
}

void Network_Interface::UnpackFlitToData() {
    if (dataToPE < 4) {
        dataBuffer[dataToPE] = flitBuffer[0].range(21, 0);
        dataToPE += 1;
        for (int i = 0; i < flitFromRouter - 1; i++) {
            flitBuffer[i] = flitBuffer[i + 1];
        }
    }
}

//----------------------^^^^^ put your code here ^^^^^------------------------------
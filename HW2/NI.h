#include "systemc.h"
#include "config.h"
#include <iostream>

using namespace std;

SC_MODULE( Network_Interface ) {
	
	sc_in_clk clk;
	sc_in < bool > reset;
	sc_in < sc_lv<FLIT_LENGTH> > Flit_in;
	sc_out < sc_lv<FLIT_LENGTH> > Flit_out;
	sc_out < sc_lv<DATA_LENGTH> > Data_in;
	sc_in < sc_lv<DATA_LENGTH> > Data_out;

	sc_in < bool > L_req_in, L_ack_out;
	sc_out < bool > L_ack_in, L_req_out;
	
	sc_in < bool > PE_req_in, PE_ack_out;
	sc_out < bool > PE_ack_in, PE_req_out;

	sc_lv<FLIT_LENGTH> flitBuffer[8]; // 0~3 index receive data from router, 4~7 index send data to router
	sc_lv<DATA_LENGTH> dataBuffer[8]; // 0~3 index send data from PE, 4~7 index receive from PE
	
	int flitFromRouter, flitToRouter, dataFromPE, dataToPE;
	bool reqRouterEn;

	void Reset();
	void AckToRouter(); // Receive L_req_in signal, if buffer is not full, then send L_ack_in
	void ReceiveFlitFromRouter();
	void ReqToRouter(); // Send L_req_out signal, if router is not full, then receive L_ack_out
	void SendFlitToRouter();
	void AckToPE(); // Receive PE_req_in signal, if buffer is not full, then send PE_ack_in
	void ReceiveDataFromPE();
	void ReqToPE(); // Send PE_req_out signal, if router is not full, then receive PE_ack_out
	void SendDataToPE();
	void PacketDataToFlit(); // Process data into flit packet
	void UnpackFlitToData(); // Process flit packet into data

	//----------------------vvvvv put your code here vvvvv------------------------------
    SC_CTOR( Network_Interface ) {
		SC_METHOD(Reset);
		sensitive << reset.pos();
		SC_METHOD(AckToRouter);
		sensitive << L_req_in;
		SC_METHOD(ReceiveFlitFromRouter);
		sensitive << Flit_in;
		SC_METHOD(ReqToRouter);
		sensitive << clk.pos();
		SC_METHOD(SendFlitToRouter);
		sensitive << L_ack_out;
		SC_METHOD(AckToPE);
		sensitive << PE_req_in;
		SC_METHOD(ReceiveDataFromPE);
		sensitive << Data_out;
		SC_METHOD(ReqToPE);
		sensitive << clk.pos();
		SC_METHOD(SendDataToPE);
		sensitive << PE_ack_out;
		SC_METHOD(PacketDataToFlit);
		sensitive << clk.pos();
		SC_METHOD(UnpackFlitToData);
		sensitive << clk.pos();
    }
	//----------------------^^^^^ put your code here ^^^^^------------------------------
};

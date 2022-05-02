#include "systemc.h"
#include "config.h"
#include <iostream>
#include <vector>

using namespace std;

SC_MODULE( Router ) {
	
	sc_in_clk clk;
	sc_in < bool > reset;
	sc_in < sc_lv<FLIT_LENGTH> > East_in, West_in, North_in, South_in, Local_in;
	sc_out < sc_lv<FLIT_LENGTH> > East_out, West_out, North_out, South_out, Local_out;
	
	sc_in < bool > L_req_in, L_ack_out;
	sc_out < bool > L_ack_in, L_req_out;
	
	sc_lv<FLIT_LENGTH> packetBuffer[8];
	sc_lv<FLIT_LENGTH> dataBuffer[8];
	sc_lv<FLIT_LENGTH> temp;

	int northEn, westEn, southEn, eastEn, localEn;

	void Reset();
	void TransPacket();
	void TransPacketToNorth();
	void TransPacketToWest();
	void TransPacketToSouth();
	void TransPacketToEast();
	void TransFlag();
	void TransToLocal();
	void ReceiveSignal();
	void ReceiveLocalPacket();

	//----------------------vvvvv put your code here vvvvv------------------------------
    SC_CTOR( Router ) {
		SC_METHOD(Reset);
		sensitive << reset.pos();
		SC_METHOD(TransPacket);
		sensitive << North_in << West_in << South_in << East_in;
		SC_METHOD(TransFlag);
		sensitive << clk.pos();
		SC_METHOD(TransToLocal);
		sensitive << L_ack_out;
		SC_METHOD(ReceiveSignal);
		sensitive << L_req_in;
		SC_METHOD(ReceiveLocalPacket);
		sensitive << Local_in;
		SC_METHOD(TransPacketToNorth);
		sensitive << clk.pos();
		SC_METHOD(TransPacketToWest);
		sensitive << clk.pos();
		SC_METHOD(TransPacketToSouth);
		sensitive << clk.pos();
		SC_METHOD(TransPacketToEast);
		sensitive << clk.pos();
    }
	//----------------------^^^^^ put your code here ^^^^^------------------------------
};

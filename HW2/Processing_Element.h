#include "systemc.h"
#include "config.h"
#include <iostream>

using namespace std;

SC_MODULE( Processing_Element ) {
	
	sc_in_clk clk;
	sc_in < bool > reset;
	sc_in < sc_lv<DATA_LENGTH> > Data_in;
	sc_out < sc_lv<DATA_LENGTH> > Data_out;
	
	sc_in < bool > PE_req_in, PE_ack_out;
	sc_out < bool > PE_ack_in, PE_req_out;

	sc_lv<DATA_LENGTH> dataBuffer[8];
	sc_lv<DATA_LENGTH> sumBuffer[8];

	int dataCount, sumCount;
	
	void Reset();
	void ReqFromNI();
	void ReceiveData();
	void PartialSum();
	void ReqToNI();
	void AckFromNI();

	//----------------------vvvvv put your code here vvvvv------------------------------
    SC_CTOR( Processing_Element ) {
		SC_METHOD(Reset);
		sensitive << reset.pos();
		SC_METHOD(ReqFromNI);
		sensitive << PE_req_in;
		SC_METHOD(ReceiveData);
		sensitive << Data_in;
		SC_METHOD(PartialSum);
		sensitive << clk.pos();
		SC_METHOD(ReqToNI);
		sensitive << clk.pos();
		SC_METHOD(AckFromNI);
		sensitive << PE_ack_out;
    }
	//----------------------^^^^^ put your code here ^^^^^------------------------------
};

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
	
	//----------------------vvvvv put your code here vvvvv------------------------------
    SC_CTOR( Network_Interface ) {
		
    }
	//----------------------^^^^^ put your code here ^^^^^------------------------------
};

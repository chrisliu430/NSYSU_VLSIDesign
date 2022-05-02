#include "systemc.h"
#include "config.h"
#include "iostream"

using namespace std;

SC_MODULE( Pattern ) {
	
	sc_in_clk clock;
	sc_in < bool > reset;
	sc_out < sc_lv<FLIT_LENGTH> > East_in, West_in, North_in, South_in;
	
	sc_lv < FLIT_LENGTH > East_temp, West_temp, North_temp, South_temp;
	ifstream pat_din;
	
	void pattern();
	
	SC_CTOR( Pattern )
	{
		pat_din.open( "./input_2.txt", ios::in );
		SC_METHOD( pattern );
		sensitive << clock.neg();
	}
};


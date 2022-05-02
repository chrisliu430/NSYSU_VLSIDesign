#include "systemc.h"
#include "config.h"
#include <iostream>
#include <stdio.h>

using namespace std;

SC_MODULE( Monitor ) {	

	sc_in_clk clock;
	sc_in < bool > reset;
	sc_in < sc_lv<FLIT_LENGTH> > East_out, West_out, North_out, South_out;
	
	void monitor();
	
	SC_CTOR( Monitor )
	{	
		sc_report_handler::set_actions (SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_, SC_DO_NOTHING);
		
		SC_METHOD( monitor );
		sensitive << clock.pos();
	}
};


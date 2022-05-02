#include "Monitor.h"

string Get_Flit_type( sc_lv<2> data ) {
	if ( data.to_string() == HEAD )
		return "HEAD";
	else if ( data.to_string() == BODY )
		return "BODY";
	else if ( data.to_string() == TAIL )
		return "TAIL";
	
	return data.to_string() + data.to_string();
}

string Get_i( sc_lv<4> data ) {
	
	string rtn = "( ";
	
	if ( data.range(3, 2) == "XX" )
		rtn += "X, ";
	else if ( data.range(3, 2) == "ZZ" )
		rtn += "Z, ";
	else {
		char buffer [50];
		sprintf( buffer, "%d", data.range(3, 2).to_uint() );
		string str = string(buffer);
		rtn += str + ", ";
	}
	if ( data.range(1, 0) == "XX" )
		rtn += "X )";
	else if ( data.range(1, 0) == "ZZ" )
		rtn += "Z )";
	else {
		char buffer [50];
		sprintf( buffer, "%d", data.range(1, 0).to_uint() );
		string str = string(buffer);
		rtn += str + " )";
	}
	return rtn;
}

void Monitor::monitor() {

	cout << "North_out| TYPE: ";
	cout << Get_Flit_type( North_out.read().range(31,30) );
	cout << ", Src: ";
	cout << Get_i( North_out.read().range(29,26) );
	cout << ", Dest: ";
	cout << Get_i( North_out.read().range(25,22) );
	cout << ", Data: ";
	cout << North_out.read().range(21,0);
	cout << " | ";
	cout << North_out.read().range(21,0).to_ulong();
	cout << endl;
	
	cout << "West_out | TYPE: ";
	cout << Get_Flit_type( West_out.read().range(31,30) );
	cout << ", Src: ";
	cout << Get_i( West_out.read().range(29,26) );
	cout << ", Dest: ";
	cout << Get_i( West_out.read().range(25,22) );
	cout << ", Data: ";
	cout << West_out.read().range(21,0);
	cout << " | ";
	cout << West_out.read().range(21,0).to_ulong();
	cout << endl;
	
	cout << "South_out| TYPE: ";
	cout << Get_Flit_type( South_out.read().range(31,30) );
	cout << ", Src: ";
	cout << Get_i( South_out.read().range(29,26) );
	cout << ", Dest: ";
	cout << Get_i( South_out.read().range(25,22) );
	cout << ", Data: ";
	cout << South_out.read().range(21,0);
	cout << " | ";
	cout << South_out.read().range(21,0).to_ulong();
	cout << endl;
	
	cout << "East_out | TYPE: ";
	cout << Get_Flit_type( East_out.read().range(31,30) );
	cout << ", Src: ";
	cout << Get_i( East_out.read().range(29,26) );
	cout << ", Dest: ";
	cout << Get_i( East_out.read().range(25,22) );
	cout << ", Data: ";
	cout << East_out.read().range(21,0);
	cout << " | ";
	cout << East_out.read().range(21,0).to_ulong();
	cout << endl;
	
	cout << endl << endl;
}



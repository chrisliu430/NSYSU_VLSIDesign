#include <Pattern.h>

void Pattern::pattern() {
	
	if ( reset.read() )
		return;
		
	for ( int i = 0 ; i < 32 ; i++ )
		pat_din >> North_temp[31-i];
		
	for ( int i = 0 ; i < 32 ; i++ )
		pat_din >> West_temp[31-i];
		
	for ( int i = 0 ; i < 32 ; i++ )
		pat_din >> South_temp[31-i];
		
	for ( int i = 0 ; i < 32 ; i++ )
		pat_din >> East_temp[31-i];
		
	North_in.write(North_temp);
	West_in.write(West_temp);
	South_in.write(South_temp);
	East_in.write(East_temp);
}
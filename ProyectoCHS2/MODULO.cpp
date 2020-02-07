#include"MODULO.h"


void uart::registros(){

	if(rst.read()){
		ST = 0; 
		cont1 = cont2 = 0;
		return;
	}else{
		ST = nST;
		rx_buffer = new_rx_buffer;
		cont1 = new_cont1;
		cont2 =new_cont2;
	}
	fire.write( !fire.read() );
}

void uart::FSM(){

	bool bit; 

	nST = ST;					// ASIGNACIONES POR DEFECTO
	new_rx_buffer = rx_buffer;
	new_cont1 = cont1;
	new_cont2 = cont2;
	rx_valid.write( false );

	bit = rx.read();

	switch(ST){
	case 0: // IDLE			

		// completar según diagrama de estados


		break;
	default: // RECIBIR
		
		
		// completar según diagrama de estados


	};

	rx_data.write( new_rx_buffer(8, 1) );		// correcto, dejar así

}

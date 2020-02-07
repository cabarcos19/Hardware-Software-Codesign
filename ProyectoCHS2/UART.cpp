#include"UART.h"


void uart::registros(){

	if(rst.read()){
		ST = 0; 
		cont1 = 0;
		cont2 = 0;
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
		if (bit == 1)
			new_cont1 = 0;

		else if (bit == 0 && cont1 < 8)
			++new_cont1;
		else if (bit == 0 && cont1 == 8) {
			new_cont1 = 0;
			new_cont2 = 0;
			nST = ST + 1;
		}
		break;

	case 1: // RECIBIR
		
		if (cont1 < 15)
			++new_cont1;
		else if (cont1 == 15 && cont2 < 8) {
			new_cont1 = 0;
			new_rx_buffer |= (bit << new_cont2);//añade rx a rx_buffer
			++new_cont2;
		}
		else if (cont1 == 15 && cont2 == 8) {
			rx_valid.write(true);
			rx_data.write(new_rx_buffer(8, 1));
			nST = 0;
			new_rx_buffer = 0;
			return;
		}
		break;
	};

	rx_data.write( new_rx_buffer(8, 1) );		// correcto, dejar así

}

#include "systemc.h"
#include "UART.h"
#include "consumidor.h"
#include "productor.h"



class top : public sc_module
{
public:
	sc_in<bool> clk, rst; 

	sc_signal<sc_uint<8>> Qrx_data;
	sc_signal<bool> Qrx, Qrx_valid;

	productor *datosEntrada;
	consumidor *salidaResultados;
	uart *instModulo;


	SC_CTOR(top) // COMPLETA LAS ASIGNACIONES DE RELOJES PARA CADA MÓDULO
	{

		datosEntrada = new productor("datosEntrada");
		salidaResultados  = new consumidor("salidaResultados", "resultados.txt");
		instModulo = new uart("instModulo");

		datosEntrada->clk		( clk );
		datosEntrada->rst		(rst);
		datosEntrada->rx		(Qrx);

		instModulo->clk			( clk );
		instModulo->rst			( rst ); 
		instModulo->rx			( Qrx );
		instModulo->rx_valid	( Qrx_valid );
		instModulo->rx_data		( Qrx_data );

		salidaResultados->clk		( clk );
		salidaResultados->rst		(rst);
		salidaResultados->rx_valid	(Qrx_valid );
		salidaResultados->rx_data	(Qrx_data );
	}

};



int sc_main(int nargs, char* vargs[]){

	sc_clock clk ("clk", 1, SC_NS);
	sc_signal <bool> rst;

	top principal("top");

	principal.clk( clk );
	principal.rst( rst );
	rst.write(true);
	sc_start(5, SC_NS);
	rst.write(false);

	sc_start();
	while (1) {}
	return 0;

}


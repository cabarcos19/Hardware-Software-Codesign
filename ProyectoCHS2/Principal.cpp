#include "systemc.h"

#include "MODULO.h"
#include "consumidor.h"
#include "productor.h"



class top : public sc_module
{
public:
	sc_in<bool> clk, rst; 

	sc_signal< sc_int<32> >	QdinReal, QdinImg, QdoutReal, QdoutImg; 
	sc_signal<bool>			Qready_in, Qready_out, Qwe;	
	sc_signal< sc_uint<8> >	Qaddr_in, Qaddr_out, Qmask;
	sc_signal< sc_int<32> >	Qdout;

	productor *datosEntrada;
	consumidor *salidaResultados;
	filtro *instModulo;


	SC_CTOR(top) // COMPLETA LAS ASIGNACIONES DE RELOJES PARA CADA MÓDULO
	{

		datosEntrada = new productor("datosEntrada");
		salidaResultados  = new consumidor("salidaResultados", "resultados.txt");
		instModulo = new filtro("instModulo");

		datosEntrada->clk		( clk );
		datosEntrada->rst		(rst);
		datosEntrada->dinReal	(QdinReal);
		datosEntrada->dinImg	(QdinImg);
		datosEntrada->mask		(Qmask);
		datosEntrada->ready_in	(Qready_in);
		datosEntrada->addr_in	(Qaddr_in);


		instModulo->clk			(clk);
		instModulo->rst			(rst);

		instModulo->addr_in		(Qaddr_in);
		instModulo->addr_out	(Qaddr_out);
		instModulo->dinReal		(QdinReal);
		instModulo->dinImg		(QdinImg);
		instModulo->mask		(Qmask);
		instModulo->ready_in	(Qready_in);
		instModulo->ready_out	(Qready_out);
		instModulo->we			(Qwe);
		instModulo->doutReal	(QdoutReal);
		instModulo->doutImg		(QdoutImg);



		salidaResultados->clk		(clk );
		salidaResultados->rst		(rst);
		salidaResultados->addr_out	(Qaddr_out );
		salidaResultados->ready_out	(Qready_out );
		salidaResultados->we		(Qwe );
		salidaResultados->doutReal	(QdoutReal );
		salidaResultados->doutImg	(QdoutImg );

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

	return 0;

}


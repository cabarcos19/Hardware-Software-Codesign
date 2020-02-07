#include "systemc.h"

#include "fifo.h"
#include "consumidor.h"
#include "fft_L1.h"
#include "productor.h"



class top : public sc_module
{
	public:
		// DECLARA AQUÍ LAS COLAS QUE NECESITES
	fifo_T<sc_int<32>>  *QdinReal;
	fifo_T<bool> *Qready_in;
	fifo_T<sc_uint<8>>	*Qaddr_in; //8 bits sin signo+
	fifo_T<sc_uint<8>>	*Qaddr_out; //8 bits sin signo
	fifo_T<bool> *Qready_out; //bool
	fifo_T<sc_int<32>>	*QdoutReal;//32 bits con signo
	fifo_T<sc_int<32>> *QdoutImg;//32 bits con signo

	productor *datosEntrada;
	consumidor *salidaResultados;
	fft_L1 *instFftL1;



	SC_CTOR(top) // the module constructor
	{


		datosEntrada = new productor("datosEntrada", "testL1_in.txt" );
		salidaResultados  = new consumidor("salidaResultados", "testL1_out.txt");
		instFftL1 = new fft_L1("instFftL1");
		// INSTACIA AQUÍ TU MÓDULO 


		// INSTACIA AQUÍ LAS COLAS QUE NECESITES
		QdinReal = new fifo_T<sc_int<32>>("QdinReal", 4);
		Qready_in = new fifo_T<bool> ("Qready_in",1);
		Qaddr_in = new fifo_T<sc_uint<8>>("Qaddr_in",4);  //8 bits sin signo
		Qaddr_out = new fifo_T<sc_uint<8>>("Qaddr_out",4);  //8 bits sin signo
		Qready_out = new fifo_T<bool>("Qready_out",1);  //bool
		QdoutReal = new fifo_T<sc_int<32>>("QdoutReal",4); //32 bits con signo
		QdoutImg = new fifo_T<sc_int<32>>("QdoutImg",4); //32 bits con signo	

		// CONECTA LAS COLAS 

		datosEntrada->dinReal( *QdinReal);
		datosEntrada->ready_in( *Qready_in);


		salidaResultados->addr_in( *Qaddr_in);
		salidaResultados->addr_out( *Qaddr_out);
		salidaResultados->ready_out(*Qready_out);
		salidaResultados->doutReal(*QdoutReal);
		salidaResultados->doutImg(*QdoutImg);


		
		instFftL1->dinReal(*QdinReal);
		instFftL1->ready_in(*Qready_in);
		instFftL1->addr_in(*Qaddr_in);
		instFftL1->addr_out(*Qaddr_out);
		instFftL1->ready_out(*Qready_out);
		instFftL1->doutReal(*QdoutReal);
		instFftL1->doutImg(*QdoutImg);


	}

};


int sc_main(int nargs, char* vargs[]){

	top principalIntra("top");
	sc_start();

	return 0;

}

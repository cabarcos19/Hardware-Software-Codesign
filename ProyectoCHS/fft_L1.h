#ifndef fft_L1_H
#define fft_L1_H

#include "systemc.h"
#include "fifo.h"

SC_MODULE(fft_L1) {
public:

	sc_port<read_if_T<sc_int<32>>> dinReal; 
	sc_port<read_if_T<bool>> ready_in;
	sc_port<write_if_T<sc_uint<8>>>	addr_in; //8 bits sin signo
	sc_port<write_if_T<sc_uint<8>>>	addr_out; //8 bits sin signo
	sc_port<write_if_T<bool>> ready_out; //bool
	sc_port<write_if_T<sc_int<32>>>	doutReal;//32 bits con signo
	sc_port<write_if_T<sc_int<32>>>	doutImg;//32 bits con signo


	void convertir();

	SC_CTOR(fft_L1) {
		cout << "fft_L1_  :" << name() << endl;
		SC_THREAD(convertir);
	}
};

#endif
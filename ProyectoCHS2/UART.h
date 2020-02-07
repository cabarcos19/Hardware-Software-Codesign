#ifndef UART_H
#define UART_H

#include "systemc.h"

SC_MODULE (uart) {
public:
sc_in<bool>	clk;
sc_in<bool> rst;
sc_in<bool>	rx;
sc_out<bool> rx_valid;
sc_out< sc_uint<8>> rx_data;

  void FSM();
  void registros();


  SC_CTOR(uart) {
	cout<<"uart: "<<name()<<endl;
    SC_METHOD(registros);
	sensitive << clk.pos();
    SC_METHOD(FSM);
	sensitive << fire << rx;

  }
private: 
	sc_signal<bool> fire; 
	sc_uint<2> ST, nST;
	sc_uint<9> rx_buffer, new_rx_buffer;
	sc_uint<4> cont1, new_cont1;
	sc_uint<5> cont2, new_cont2;
	


}; 


#endif
#ifndef PRODUCTOR_H
#define PRODUCTOR_H

#include "systemc.h"
#include "fifo.h"
#include <stdio.h>


SC_MODULE (productor) {
public:
sc_port<write_if_T<sc_int<32>>> dinReal;//32 bits con signo 
sc_port<write_if_T<bool>> ready_in;

SC_HAS_PROCESS(productor);

  void producir();

productor(sc_module_name name_, char *fileName) : sc_module(name_){

	cout<<"productor: " << name() << "  " << fileName << endl;
	fichero = fopen(fileName, "rt");
	if( !fichero ){
		cerr << "No se puede abrir el fichero de entrada: " << fileName << endl;
		return;
	}
    SC_THREAD(producir);
}

private:
	FILE *fichero;

}; 


#endif
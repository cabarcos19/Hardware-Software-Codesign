#include "fft_L1.h"


void fft_L1::convertir() {
	
	int i;
	sc_uint<8> dir0,dir1;
	sc_int<32> real0, real1,resReal0,resReal1,resImg0,resImg1;
	bool valid_in;
	while(1)
		for (i = 0; i < 256; i += 4) {
			ready_in->read(valid_in);
			if (valid_in) {
				dir0 = i;
				dir1 = i + 2;

				dinReal->read(real0);//lectura memoria
				dinReal->read(real1);//lectura memoria

				resReal0 = real0 + real1; //calcular 1 fase
				resImg0 = 0;

				resReal1 = real0 - real1;// calcular 1 fase
				resImg1 = 0;

				doutReal->write(resReal0);
				doutImg->write(resImg0);// escritura memoria
				addr_in->write(dir0);
				addr_out->write(dir0);

				doutReal->write(resReal1);
				doutImg->write(resImg1);// escritura memoria
				addr_in->write(dir1);
				addr_out->write(dir1);
				ready_out->write(true);
			}
			ready_in->read(valid_in);
			if (valid_in) {
				dir0 = i + 1;
				dir1 = i + 3;
				dinReal->read(real0);//lectura memoria
				dinReal->read(real1);//lectura memoria

				resReal0 = real0; // optimizables
				resImg0 = -real1; // por su sencillez

				resReal1 = real0;
				resImg1 = real1;

				doutReal->write(resReal0);
				doutImg->write(resImg0);// escritura memoria
				addr_in->write(dir0);
				addr_out->write(dir0);
				
				doutReal->write(resReal1);
				doutImg->write(resImg1);// escritura memoria
				addr_in->write(dir1);
				addr_out->write(dir1);
				ready_out->write(true);
			}
			
		}
	
}

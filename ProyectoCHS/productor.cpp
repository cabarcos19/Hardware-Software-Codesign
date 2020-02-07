#include"productor.h"


void productor::producir(){

	int i;						// declara más variables si te hacen falta
	//sc_ ...						// declara aquí las variables con tipos de SystemC que necesites
	int leido1, leido2;		// variables temporales para leer de fichero.
	for(i=0; i<256 ; ++i){

		fscanf( fichero, "%d %d", &leido1, &leido2);  // adapta esta línea a tu fichero de entrada

		dinReal->write( leido1 );		// adapta esto a los puertos de salida de tu productor
		dinReal->write( leido2 );		// adapta esto a los puertos de salida de tu productor
		ready_in->write(true);
	}
	
	fclose(fichero);

	// DEJAMOS QUE SIGA CORRIENDO CUANDO YA NO TENGAMOS MÁS DATOS QUE SUMINISTRAR
	while(true){		
		wait(SC_ZERO_TIME);

	}

}

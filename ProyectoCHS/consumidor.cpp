#include"consumidor.h"

void consumidor::consumir(){

	int i;						// declara más variables si te hacen falta
	sc_uint<8> res1, res2,res3,res6;			// declara aquí las variables con tipos de SystemC que necesites
	sc_int<32>	res4, res5, res7, res8;						// recuerda que para leer de un puerto necesitas que 							// el tipo de la variable coincida con el tipo del puerto
	int leido1, leido2, leido3, leido4, leido5,leido6, leido7, leido8;		// variables temporales para leer de fichero.
	bool valid_out;

	for (i = 0; i < 256; ++i) {
		ready_out->read(valid_out);
		if (valid_out) {
			fscanf(fichero, "%d %d ", &leido1, &leido2);  // adapta esta línea a tu fichero de entrada
			fscanf(fichero, "%d %d", &leido3, &leido4);
			fscanf(fichero, "%d %d", &leido5, &leido6);
			fscanf(fichero, "%d %d", &leido7, &leido8);
			addr_in->read(res1);		// adapta esto a los puertos de entrada de tu consumidor
			addr_in->read(res2);		// adapta esto a los puertos de entrada de tu consumidor

			addr_out->read(res3);
			addr_out->read(res6);

			doutReal->read(res4);
			doutReal->read(res7);

			doutImg->read(res5);
			doutImg->read(res8);

			if (leido1 != res1.to_uint())		// comprueba que todo ha ido bien
				printf("Error en resultado addr_in 1, iteracion %d   %d <> %d \n", i, leido1, res1.to_uint());
			// haz lo mismo para todos los resultados que produzca tu módulo
			// según el tipo de dato puedes necesitar .to_int(), .to_uint(), o ninguno (p.e. si es bool)

			if (leido2 != res2.to_uint())		// comprueba que todo ha ido bien
				printf("Error en resultado addr_in 2, iteracion %d   %d <> %d \n", i, leido2, res2.to_uint());

			if (leido3 != res3.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado addr_out 1, iteracion %d   %d <> %d \n", i, leido3, res3.to_uint());

			if (leido4 != res4.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado dOutReal 1, iteracion %d   %d <> %d \n", i, leido4, res4.to_int());

			if (leido5 != res5.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado dOutImg 1, iteracion %d   %d <> %d \n", i, leido5, res5.to_int());

			if (leido6 != res6.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado addr_out 2, iteracion %d   %d <> %d \n", i, leido6, res6.to_uint());

			if (leido7 != res7.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado dOutReal 2, iteracion %d   %d <> %d \n", i, leido7, res7.to_int());

			if (leido8 != res8.to_int())		// comprueba que todo ha ido bien
				printf("Error en resultado dOutImg 2, iteracion %d   %d <> %d \n", i, leido8, res8.to_int());

		}
	}
	fclose(fichero);
	printf("Simulacion terminada\n"); 
	sc_stop(); 
}
/*
 Este archivo contiene la función main del lado el cliente. Toma como argumento la dirección del servidor (host). 
 Crea el cliente con la función clnt_create cuyos parámetros son: dirección del servidor, número y versión de programa 
 y protocolo de red (host, SUMA_PROG, SUMA_VERS, "udp"). Y hace la llamada al procedimiento suma_1 del stub suma_clnt.c
 */

#include "suma.h"


void
suma_prog_1(char *host, int a, int b)
{
	CLIENT *clnt;
	int  *result_1;
	dupla_int  suma_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, SUMA_PROG, SUMA_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	suma_1_arg.a=a;
	suma_1_arg.b=b;

	result_1 = suma_1(&suma_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	else{
		printf("a + b = %d\n",*result_1);	
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	int a,b;

	
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	
	printf("Suma de dos valores (a+b)\n");
	printf("Ingresa el valor a: ");
	scanf("%d",&a);
	printf("Ingresa el valor b: ");
	scanf("%d",&b);

	host=argv[1];
	suma_prog_1 (host,a,b);
exit (0);
}

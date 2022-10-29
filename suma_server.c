/*
 Este el es código en donde implementaremos el procedimiento remoto.
 */

#include "suma.h"

int *
suma_1_svc(dupla_int *argp, struct svc_req *rqstp)
{
	static int  result;

	result=argp->a+argp->b;
	printf("Se ha invocado remotamente el procedimiento\n");
	printf("Primer numero (a): %d\nSegundo numero (b): %d\n\n",argp->a,argp->b);
	printf("Resultado suma =  %d\n\n",result);

	return &result;
}

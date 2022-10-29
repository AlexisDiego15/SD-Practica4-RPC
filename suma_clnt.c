/*
 Esta es la funci�n stub del cliente que implementa la funci�n suma_1, 
 serializa (marshalling) el par�metro, llama al procedimiento remoto, 
 y devuelve el resultado. Todo ello mediante el procedimiento clnt_call.
 */

#include <memory.h> /* for memset */
#include "suma.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
suma_1(dupla_int *argp, CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, SUMA,
		(xdrproc_t) xdr_dupla_int, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

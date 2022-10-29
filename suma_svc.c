/*
Este es el programa servidor, se implementa el procedimiento principal (la funci�n main), y es aqu� en donde se registra el servicio. 
La funci�n llamada suma_prog_1 contiene un statement switch para todos los procedimientos remotos soportados por este programa 
y esta versi�n. Adem�s del procedimiento nulo, la �nica entrada en la sentencia switch es SUMA, esto establece un puntero a funci�n
 (local) a la funci�n de servidor, suma_1_svc. M�s tarde, en el procedimiento, la funci�n se invoca con el par�metro unmarshalled y 
 la informaci�n del solicitante.
 */

#include "suma.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
suma_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		dupla_int suma_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case SUMA:
		_xdr_argument = (xdrproc_t) xdr_dupla_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) suma_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (SUMA_PROG, SUMA_VERS);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, SUMA_PROG, SUMA_VERS, suma_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (SUMA_PROG, SUMA_VERS, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, SUMA_PROG, SUMA_VERS, suma_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (SUMA_PROG, SUMA_VERS, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}

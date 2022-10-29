/*
 Este es el archivo de cabecera que incluiremos en nuestro c�digo de cliente y c�digo servidor. 
 Define la estructura dupla_int, define SUMA_PROG, s�mbolos (0x23451111, nuestro n�mero de programa) 
 y SUMA_VERS (1, nuestro n�mero de versi�n). Adem�s, define una funci�n para checar la consistencia 
 del par�metro enviado (xdr_intpair), la interfaz del cliente (suma_1) y la interfaz para la funci�n 
 de servidor que vamos a tener que escribir (suma_1_svc).
 */

#ifndef _SUMA_H_RPCGEN
#define _SUMA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct dupla_int {
	int a;
	int b;
};
typedef struct dupla_int dupla_int;

#define SUMA_PROG 0x23451111
#define SUMA_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define SUMA 1
extern  int * suma_1(dupla_int *, CLIENT *);
extern  int * suma_1_svc(dupla_int *, struct svc_req *);
extern int suma_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define SUMA 1
extern  int * suma_1();
extern  int * suma_1_svc();
extern int suma_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_dupla_int (XDR *, dupla_int*);

#else /* K&R C */
extern bool_t xdr_dupla_int ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_SUMA_H_RPCGEN */

/*
 El archivo suma_xdr.c no siempre se genera, depende de los parámetros utilizados para procedimientos remotos.
  En esta práctica sí se generó, así que este archivo contiene código para reunir parámetros para la estructura intpair.
  Utiliza XDR (External Data Representation) para convertir los dos enteros a un formato estándar.
 */

#include "suma.h"

bool_t
xdr_dupla_int (XDR *xdrs, dupla_int *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;
	return TRUE;
}

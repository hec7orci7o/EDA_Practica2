#***************************************************************************
# File:   	Makefile
# Authores: Pablo Lacueva(799134) & Hector Toral(798095)
# Date:   	dic 2020
# Coms:   	
#         	Ejecutar 'make' para compilar
#         	Ejecutar 'make clean'para limpiar (borra lo que genere)
#***************************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # para compilar
#---------------------------------------------------------
EJECUTABLE = practica2
MAIN = practica2

COLECCION = colecciones
PILA = pila
DATO = puntos2D
#---------------------------------------------------------
# opciones de compilación
CPPFLAGS=-std=c++11 # opciones compilación
#---------------------------------------------------------
${MAIN}: ${MAIN}.o ${DATO}.o ${COLECCION}.h ${PILA}.h
	$(CC)  ${MAIN}.o ${DATO}.o ${COLECCION}.h ${PILA}.h -o ${EJECUTABLE} $(CPPFLAGS)
#---------------------------------------------------------
${MAIN}.o:
	$(CC) ${MAIN}.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
${DATO}.o: ${DATO}.cpp
	$(CC) ${DATO}.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
clean:
	$(RM) ${MAIN}
	$(RM) *.o
	$(RM) salida.txt
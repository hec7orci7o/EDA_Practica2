#***************************************************************************
# File:   	Makefile
# Authores: Pablo Lacueva & Hector Toral
# Date:   	dic 2020
# Coms:   	
#         	Ejecutar 'make' para compilar
#         	Ejecutar 'make clean'para limpiar (borrar lo que genere)
#***************************************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # para compilar
#---------------------------------------------------------
# opciones de compilación
CPPFLAGS=-std=c++11 # opciones compilación
#---------------------------------------------------------
practica2: practica2.o puntos2D.o colecciones.h pila.h
	$(CC)  practica2.o puntos2D.o colecciones.h pila.h -o practica2 $(CPPFLAGS)
#---------------------------------------------------------
practica2.o:
	$(CC) practica2.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
puntos2D.o: puntos2D.cpp
	$(CC) puntos2D.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
clean:
	$(RM) practica2
	$(RM) *.o
	$(RM) salida.txt
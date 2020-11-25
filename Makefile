#***************************************************************************
# File:   	Makefile
# Authores: Pablo Lacueva & Hector Toral
# Date:   	25/11/2020
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
practica2: practica2.o puntos2D.o colecciones.h
	$(CC)  practica2.o puntos2D.o colecciones.h -o practica2 $(CPPFLAGS)
#---------------------------------------------------------
practica2.o:
	$(CC) practica2.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
puntos2D.o: puntos2D.cpp
	$(CC) puntos2D.cpp -c $(CPPFLAGS)
#---------------------------------------------------------
clean:
	$(RM) practica2
	$(RM) practica2 practica2.o
	$(RM) puntos2D.o
	$(RM) colecciones.o
	$(RM) salida.txt
/*
 * enfermedad.h
 *
 * Copyright  (C) Juan F. Huete y Carlos Cano
*/
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream>
#include <algorithm>
using namespace std;


//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad, enfermedad::setName, enfermedad::setID, enfermedad::setDatabase, enfermedad::getName,
 * enfermedad::getID, enfermedad::getDatabase, enfermedad::operator=, enfermedad::toString, enfermedad::operator==,
 * enfermedad::operator!=, enfermedad::operator<, enfermedad::nameContains
 * \n Descripción: contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP
 * (nombre de la enfermedad, id, BD que provee el id)
 *
 * @author Elena María Gómez Ríos
 */

class enfermedad {
private:
   // Función de abstracción: FA(e) = e es una enfermedad concreta name, ID, database
   // Invariante de Representación: IR(e) = (e.name debe de estar en minúscula)
   /**Nombre de la enfermedad.
    * @pre Almacenar completo en minúscula.
   */
   string  name;
   /** ID único para la enfermedad
   */
   string  ID;
   /** Base de datos que provee el ID
   */
   string  database;

public:
   /**@brief Constructor de enfermedad por defecto.
	*/
   enfermedad (); //Constructor de enfermedad por defecto

   /**@brief Constructor parametrizado de la clase.
		@param[in] name nombre de la enfermedad. Almacenar completo en minúscula.
      @param[in] ID ID único para la enfermedad.
      @param[in] database Base de datos que provee el ID.
	*/
   enfermedad (const string & name, const string & ID, const string & database);

   /** @brief Establece el nombre de la enfermedad.
		 @param[in] name nombre de la enfermedad. Almacenar completo en minúscula.
	*/
   void setName(const string & name);

   /** @brief Establece el ID de la enfermedad.
		 @param[in] ID ID único para la enfermedad.
	*/
   void setID(const string & ID);

   /** @brief Establece la base de Datos de la enfermedad.
		 @param[in] database Base de datos que provee el ID.
	*/
   void setDatabase(const string & database);

   /** @brief Obtiene el nombre de la enfermedad.
		 @return nombre de la enfermedad.
	*/
   string getName( ) const;

   /** @brief Obtiene el ID de la enfermedad
		 @return ID de la enfermedad.
	*/
   string getID( ) const;

   /** @brief Obtiene la base de datos de la enfermedad.
		 @return base de datos que provee el ID de la enfermedad.
	*/
   string getDatabase( ) const;

   /** @brief operador de asignación
		 @param[in] e enfermedad a copiar.
       @return copia de la enfermedad.
	*/
   enfermedad & operator=(const enfermedad & e);

   /** @brief Muestra el valor de los atributos de la clase enfermedad.
		 @return Devuelve un string con los atributos de la clase enfermedad.
	*/
   string toString() const;

// Operadores relacionales
   /** @brief Compara si son iguales dos enfermedades.
       @param[in] e enfermedad a comparar.
       @return Devuelve true si son iguales y false si no lo son.
   */
   bool operator==(const enfermedad & e) const;

   /** @brief Compara si son distintas dos enfermedades.
       @param[in] e enfermedad a comparar.
       @return Devuelve true si son distintas y false si no lo son.
   */
   bool operator!=(const enfermedad & e) const;

   /** @brief Compara si una enfermedad es mayor que otra, comparando por orden alfabético por el campo name.
		 @param[in] e enfermedad a comparar.
		 @return Devuelve true si e es mayor que el que lo llama. False en otro caso.
	*/
   bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name.

   /** @brief Comprueba si una cadena de caracteres está incluido en el nombre de la enfermedad.
		 @param[in] str string a comprobar.
		 @return Devuelve true si el nombre de la enfermedad contiene a str.
	*/
   bool nameContains(const string & str) const;   //Devuelve True si str está incluido en el nombre de la enfermedad,
                                 //aunque no se trate del nombre completo. No debe ser sensible a mayúsculas/minúsculas.

};

   /** @brief Imprime enfermedad con todos sus campos.
       @param[in] os flujo.
	    @param[in] e enfermedad a mostrar.
	    @return La enfermedad por salida estandar.
   */
   ostream& operator<< ( ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)

#include "enfermedad.hxx" // Incluimos la implementacion.


#endif

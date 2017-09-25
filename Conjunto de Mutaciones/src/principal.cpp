#include "mutacion.h"
#include "enfermedad.h"
#include "conjunto.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>


using namespace std;
using namespace std::chrono;

   /** @brief lee un fichero de mutaciones, linea a linea
	@param[in] s nombre del fichero
   @param[in,out] cm objeto tipo conjunto sobre el que se almacenan las mutaciones
	@return true si la lectura ha sido correcta, false en caso contrario
	*/

bool load(conjunto &  cm, const string & s) {
   ifstream fe;
   string cadena;

   cout << "Abrimos "<< s << endl;
   fe.open(s.c_str(), ifstream::in);
   if (fe.fail()){
      cerr << "Error al abrir el fichero " << s << endl;
   }
   else {
      //leo la cabecera del fichero (líneas que comienzan con #)
      do{
         getline(fe,cadena,'\n');
      }while (cadena.find("#")==0 && !fe.eof());

      //leo la tabla de mutaciones, una línea cada vez
      while ( !fe.eof() ){
         //cout << "leo:: "<< cadena << endl;
         // Invoco el constructor de mutación que recibe una cadena completa, la parsea y crea la mutación.
         mutacion mut = mutacion(cadena);
         // Insertar mutación en el conjunto
         cm.insert(mut);
         getline(fe,cadena,'\n');
      }
      fe.close();
      return true;
   } // else
   fe.close();
   return false;
}



int main(int argc, char *argv[]){

   conjunto conjuntoMutaciones;
   string query_str;
   conjunto::const_iterator itf,iti;
   pair<conjunto::value_type,bool> mutacion;

   //Cargar las mutaciones en vectorSNPs
   load(conjuntoMutaciones, "./data/clinvar_20160831.vcf");

   //Imprimir número de elementos almacenados en conjuntoMutaciones
   cout << "Lectura del fichero finalizada. Mutaciones cargadas: "<<conjuntoMutaciones.size()<<endl;

   //Imprimir cuántas mutaciones están asociadas al cromosoma 1:
   itf = conjuntoMutaciones.lower_bound("2", 1);
   iti = conjuntoMutaciones.cbegin();
   cout << "--------------------------------------------------------------------------------------"<< endl;
   cout << "Mutaciones asociadas a Chr 1: "<< endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   while (iti != itf){
      cout<<*iti<< endl;
      iti++;
   }
   cout << "--------------------------------------------------------------------------------------"<< endl;

   // ¿Existe la mutación con ID "rs147165522"? Imprimir la mutación y las enfermedades asociadas
   cout << "¿Existe la mutación con ID rs147165522? Imprimir la mutación y las enfermedades asociadas: "<< endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   mutacion = conjuntoMutaciones.find("rs147165522");
   if (mutacion.second){
      cout << mutacion.first;
   }else
      cout << "No existe la mutación con ID rs147165522."<< endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;


   // ¿Existe la mutación en chr/pos "14"/67769578? Imprimir la mutación y las enfermedades asociadas
   cout << "¿Existe la mutación en chr/pos 14/67769578? Imprimir la mutación y las enfermedades asociadas: "<< endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   mutacion = conjuntoMutaciones.find("14",67769578);
   if (mutacion.second){
      cout << mutacion.first;
   }else
      cout << "No existe la mutación en chr/pos 14/67769578."<< endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;

   // ¿Cómo podríamos calcular el número de mutaciones del cromosoma 3? (utiliza lower_bound / upper_bound)
   iti = conjuntoMutaciones.lower_bound("3", 1);
   itf = conjuntoMutaciones.lower_bound("4", 1);

   cout << "Número de mutaciones del cromosoma 3: "<<itf-iti<<" mutaciones."<<endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   // Analiza la eficiencia teórica y empírica de las operaciones find, insert y erase S
   high_resolution_clock::time_point tantes,tdespues;
   duration<double> tiempo_transcurrido;

   random_shuffle(conjuntoMutaciones.begin(),conjuntoMutaciones.end()); //Desordenamos el vector
   conjunto conjuntoEficiencia;
   //Eficiencia de insert
   cout << "Eficiencia del método insert: "<<endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   conjunto::iterator it=conjuntoMutaciones.begin();
   for (int i=1000; i<130000; i+=5000){
      tantes = high_resolution_clock::now();
      conjuntoEficiencia.insert(*it);
      tdespues = high_resolution_clock::now();
      it++;

      tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
      cout << i << " " << tiempo_transcurrido.count() << endl;
   }
   cout << "--------------------------------------------------------------------------------------"<< endl;

   //Eficiencia de find
   cout << "Eficiencia del método find: "<<endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   for (int i=1000; i<130000; i+=5000){
      tantes = high_resolution_clock::now();
      conjuntoEficiencia.find("rs0000000");
      tdespues = high_resolution_clock::now();

      tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
      cout << i << " " << tiempo_transcurrido.count() << endl;
   }
   cout << "--------------------------------------------------------------------------------------"<< endl;

   //Eficiencia de erase
   cout << "Eficiencia del método erase: "<<endl;
   cout << "--------------------------------------------------------------------------------------"<< endl;
   for (int i=1000; i<130000; i+=5000){
      tantes = high_resolution_clock::now();
      conjuntoEficiencia.erase("rs0000000");
      tdespues = high_resolution_clock::now();

      tiempo_transcurrido  = duration_cast<duration<double> >(tdespues - tantes);
      cout << i << " " << tiempo_transcurrido.count() << endl;
   }

   return 0;
}

/** @brief fichero de implementacion de la clase enfermedad

*/
#include "enfermedad.h"

Enfermedad::Enfermedad(){
  name="";
  ID="";
  database="";
}

Enfermedad::Enfermedad(const string & name, const string & ID, const string & database){
   string nameaux = name;
   transform( nameaux.begin(), nameaux.end(), nameaux.begin(), ::tolower );
   this->name = nameaux;
   this->ID = ID;
   this->database = database;
}

void Enfermedad::setName(const string & name){
   string nameaux = name;
   transform( nameaux.begin(), nameaux.end(), nameaux.begin(), ::tolower );
   this->name = nameaux;
}
void Enfermedad::setID(const string & ID){
   this->ID = ID;
}
void Enfermedad::setDatabase(const string & database){
   this->database = database;
}

string Enfermedad::getName( ) const{
   return name;
}
string Enfermedad::getID( ) const{
   return ID;
}
string Enfermedad::getDatabase( ) const{
   return database;
}

Enfermedad & Enfermedad::operator=(const Enfermedad & e){
   if (this != &e){
      name=e.name;
      ID=e.ID;
      database=e.database;
   }

   return *this;
}
string Enfermedad::toString() const{
   return "Nombre: "+name+" - ID: "+ID+" - Database: "+database;
}

bool Enfermedad::operator==(const Enfermedad & e) const{
   return (name==e.name && ID==e.ID && database==e.database);
}

bool Enfermedad::operator!=(const Enfermedad & e) const{
   return !(name==e.name && ID==e.ID && database==e.database);
}

bool Enfermedad::operator<(const Enfermedad & e) const{
   return (name<e.name);
}

bool Enfermedad::operator>(const Enfermedad & e) const{
   return (name>e.name);
}

bool Enfermedad::nameContains(const string & str) const{
   string strMinus = str;
   transform(strMinus.begin(), strMinus.end(), strMinus.begin(), ::tolower);
   size_t found = name.find(strMinus);
   return (found != string::npos);
}

ostream& operator<< ( ostream& os, const Enfermedad & e){
   os << "Nombre: "<<e.getName()<<endl ;
   os << "ID: "<<e.getID()<<endl;
   os << "Base de datos: "<<e.getDatabase()<<endl;
   return os;
 }

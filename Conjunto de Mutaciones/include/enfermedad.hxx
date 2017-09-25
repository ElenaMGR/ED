/** @brief fichero de implementacion de la clase enfermedad

*/
enfermedad::enfermedad(){
  name="";
  ID="";
  database="";
}

enfermedad::enfermedad(const string & name, const string & ID, const string & database){
   this->name = name;
   this->ID = ID;
   this->database = database;
}

void enfermedad::setName(const string & name){
   this->name = name;
}
void enfermedad::setID(const string & ID){
   this->ID = ID;
}
void enfermedad::setDatabase(const string & database){
   this->database = database;
}

string enfermedad::getName( ) const{
   return name;
}
string enfermedad::getID( ) const{
   return ID;
}
string enfermedad::getDatabase( ) const{
   return database;
}

enfermedad & enfermedad::operator=(const enfermedad & e){
   if (this != &e){
      name=e.name;
      ID=e.ID;
      database=e.database;
   }

   return *this;
}
string enfermedad::toString() const{
   return "Nombre: "+name+" - ID: "+ID+" - Database: "+database;
}

bool enfermedad::operator==(const enfermedad & e) const{
   return (name==e.name && ID==e.ID && database==e.database);
}

bool enfermedad::operator!=(const enfermedad & e) const{
   return !(name==e.name && ID==e.ID && database==e.database);
}

bool enfermedad::operator<(const enfermedad & e) const{
   return (name<e.name);
}

bool enfermedad::nameContains(const string & str) const{
   string strMinus = str;
   transform(strMinus.begin(), strMinus.end(), strMinus.begin(), ::tolower);
   size_t found = name.find(strMinus);
   return (found != string::npos);
}

ostream& operator<< ( ostream& os, const enfermedad & e){
   os << "Nombre: "<<e.getName()<<endl ;
   os << "ID: "<<e.getID()<<endl;
   os << "Base de datos: "<<e.getDatabase()<<endl;
   return os;
 }

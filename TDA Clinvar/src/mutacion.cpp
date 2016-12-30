/** @brief fichero de implementacion de la clase mutacion

*/
#include "mutacion.h"
#include <assert.h>
Mutacion::Mutacion(){
   ID="";
   chr="";
   pos=0;
   common=false;
}

Mutacion::Mutacion(const Mutacion& m){
   ID=m.ID;
   chr=m.chr;
   pos=m.pos;
   ref_alt=m.ref_alt;
   genes=m.genes;
   common=m.common;
   caf=m.caf;
   enfermedades=m.enfermedades;
   clnsig=m.clnsig;
}

Mutacion::Mutacion(const string & str){
   pos=0;
   common=false;
   // Partimos el string cada vez que encontremos el caracter "\t"
   Enfermedad e;
   string gen, aux, aux2;
   vector<string> info, nombre, id, db;
   istringstream is(str);
   string auxstr;
   vector<string> campos;
   while (getline(is,auxstr,'\t')){
      campos.push_back(auxstr);
   }

   //Leemos el identificador del cromosoma
   chr = campos[0];

   //Leemos el identificador de la posición dentro del cromosoma
   pos = stoi(campos[1]);

   //Leemos el identificador del SNP/mutación
   ID = campos[2];

   //Leemos la(s) base(s) en el genoma de referencia y alternativa(s) posible(s)
   ref_alt.push_back(campos[3]);

   gen = campos[4];
   istringstream is1(gen);
   while (getline(is1,auxstr,',')){
      info.push_back(auxstr);
   }

   for (int i = 0; i<info.size();i++){
      ref_alt.push_back(info[i]);
   }

   //Leemos la información
   gen = campos[7];
   istringstream is2(gen);
   info.clear();
   while (getline(is2,auxstr,';')){
      info.push_back(auxstr);
   }

   for (int i = 0; i < info.size() ; i++){
      // Leemos los gen(es) asociado(s) al SNP
      if (info[i].find("GENEINFO=") != string::npos){
         aux = info[i].substr(9, info[i].size()-9);

         istringstream is3(aux);
         while (getline(is3,auxstr,'|')){
            aux2 = auxstr.substr(0, auxstr.size());
            istringstream is16(aux2);
            while (getline(is16, auxstr, ',')){
               genes.push_back(auxstr);
            }

         }
      }

      //Leemos la frecuencia de cada base del SNP en la población
      else if (info[i].find("CAF=") != string::npos){
         aux = info[i].substr(4, info[i].size()-4);

         istringstream is4(aux);
         while (getline(is4,auxstr,',')){
            try {
               caf.push_back(stof(auxstr));

            }
            catch (const std::invalid_argument& ia) {
               caf.push_back(0);
            }
         }
      }

      //Leemos el indicador de si el SNP es común en la población
      else if (info[i].find("COMMON=") != string::npos){
         if ((info[i].substr(7, info[i].size()-7)) == "1")
            common = true;
         else
            common = false;
      }

      //Leemos las enfermedades asociadas al SNP
      //Nombre de la enfermedad
      else if (info[i].find("CLNDBN=") != string::npos){
         aux = info[i].substr(7, info[i].size()-7);

         istringstream is5(aux);
         while (getline(is5,auxstr,'|')){

            aux2 = auxstr.substr(0, auxstr.size());

            istringstream is6(aux2);
            while (getline(is6,auxstr,',')){
               nombre.push_back(auxstr);
            }
         }
      }

      //ID de la enfermedad
      else if (info[i].find("CLNDSDBID=") != string::npos){
         aux = info[i].substr(10, info[i].size()-10);

         istringstream is7(aux);
         while (getline(is7,auxstr,'|')){

            aux2 = auxstr.substr(0, auxstr.size());

            istringstream is8(aux2);
            while (getline(is8,auxstr,',')){
               id.push_back(auxstr);
            }
         }
      }

      //Base de datos de la enfermedad
      else if (info[i].find("CLNDSDB=") != string::npos){
         aux = info[i].substr(8, info[i].size()-8);

         istringstream is9(aux);
         while (getline(is9,auxstr,'|')){

            aux2 = auxstr.substr(0, auxstr.size());

            istringstream is10(aux2);
            while (getline(is10,auxstr,',')){
               db.push_back(auxstr);
            }
         }
      }


      //Leemos la relevancia clínica del SNP para cada enfermedad
      else if (info[i].find("CLNSIG=") != string::npos){
         aux = info[i].substr(7, info[i].size()-7);

         istringstream is11(aux);
         while (getline(is11,auxstr,'|')){

            aux2 = auxstr.substr(0, auxstr.size());

            istringstream is12(aux2);
            while (getline(is12,auxstr,',')){
               clnsig.push_back(stoi(auxstr));
            }

         }
      }

   }

   // Guardo las enfermedades
   for (int i=0; i<db.size(); i++){
      e.setName(nombre[i]);
      if (i < id.size())
         e.setID(id[i]);
      else
         e.setID("");
      if (i < db.size())
         e.setDatabase(db[i]);
      else
         e.setDatabase("");
      enfermedades.push_back(e);
   }

   if (caf.size()==0){
      caf.push_back(1);
   }

}

void Mutacion::setID(const string & id){
   ID=id;
}
void Mutacion::setChr(const string & chr){
   this->chr=chr;
}
void Mutacion::setPos(const unsigned int & pos){
   this->pos=pos;
}
void Mutacion::setRef_alt(const std::vector<string> & ref_alt){
   this->ref_alt=ref_alt;
}
void Mutacion::setGenes (const std::vector<string> & genes){
   this->genes=genes;
}
void Mutacion::setCommon (const bool & common){
   this->common=common;
}
void Mutacion::setCaf (const std::vector<float> & caf){
   this->caf=caf;
}
void Mutacion::setEnfermedades (const std::vector<Enfermedad> & enfermedades){
   this->enfermedades=enfermedades;
}
void Mutacion::setClnsig (const std::vector<int> & clnsig){
   this->clnsig=clnsig;
}

string Mutacion::getID( ) const{
   return ID;
}
string Mutacion::getChr( ) const{
   return chr;
}
unsigned int Mutacion::getPos( ) const{
   return pos;
}
const vector<string> & Mutacion::getRef_alt () const{
   return ref_alt;
}
const vector<string> & Mutacion::getGenes () const{
   return genes;
}
bool Mutacion::getCommon () const{
   return common;
}
const vector<float> & Mutacion::getCaf () const{
   return caf;
}
const vector<Enfermedad> & Mutacion::getEnfermedades () const{
   return enfermedades;
}
const vector<int> & Mutacion::getClnsig () const{
   return clnsig;
}


Mutacion & Mutacion::operator=(const Mutacion & m){
   if (this != &m){
      ID=m.ID;
      chr=m.chr;
      pos=m.pos;
      ref_alt=m.ref_alt;
      genes=m.genes;
      common=m.common;
      caf=m.caf;
      enfermedades=m.enfermedades;
      clnsig=m.clnsig;
   }

   return *this;
}


bool Mutacion::operator==(const Mutacion & m) const{
   return (ID==m.getID() && chr==m.getChr() && pos==m.getPos() );
   /*&& ref_alt==m.getRef_alt() &&
            genes==m.getGenes() && common==m.getCommon() && caf==m.getCaf() && enfermedades==m.getEnfermedades() &&
            clnsig==m.getClnsig());
*/
}

bool Mutacion::operator<(const Mutacion & m) const{
   //"1"<"2"<"3"<...<"22"<"X"<"Y"<"MT"
   // Para poder comparar el campo chr, lo que voy a hacer es pasarlo a int, y a los valores, "X", "Y" y "MT",
   // asignarle los valores 23,24,25
   int chrcomp, mchrcomp;
   if (chr=="X"){
      chrcomp=23;
   }else if (chr=="Y"){
      chrcomp=24;
   }
   else if (chr=="MT"){
      chrcomp=25;
   }else{
      chrcomp = stoi(chr);
   }


   if (m.getChr()=="X"){
      mchrcomp=23;
   }else if (m.getChr()=="Y"){
      mchrcomp=24;
   }
   else if (m.getChr()=="MT"){
      mchrcomp=25;
   }else{
      mchrcomp = stoi(m.getChr());
   }



   if (chrcomp!=mchrcomp)
      return (chrcomp<mchrcomp);
   else
      return pos<m.getPos();

}

bool Mutacion::operator>(const Mutacion & m) const{
   //"1"<"2"<"3"<...<"22"<"X"<"Y"<"MT"
   // Para poder comparar el campo chr, lo que voy a hacer es pasarlo a int, y a los valores, "X", "Y" y "MT",
   // asignarle los valores 23,24,25
   int chrcomp, mchrcomp;
   if (chr=="X"){
      chrcomp=23;
   }else if (chr=="Y"){
      chrcomp=24;
   }
   else if (chr=="MT"){
      chrcomp=25;
   }else{
      chrcomp = stoi(chr);
   }


   if (m.getChr()=="X"){
      mchrcomp=23;
   }else if (m.getChr()=="Y"){
      mchrcomp=24;
   }
   else if (m.getChr()=="MT"){
      mchrcomp=25;
   }else{
      mchrcomp = stoi(m.getChr());
   }



   if (chrcomp!=mchrcomp)
      return (chrcomp>mchrcomp);
   else
      return pos>m.getPos();

}

ostream& operator<< ( ostream& os, const Mutacion& m){
   os << "Identificador del SNP/mutación: "<<m.getID()<<endl ;
   os << "Identificador del cromosoma: "<<m.getChr()<<endl;
   os << "Identificador de la posición dentro del cromosoma: "<<m.getPos()<<endl;
   os << "Base del genoma de referencia: "<<m.getRef_alt()[0]<<endl ;
   os << "Bases alternativas: ";
   for (int i=1; i<m.getRef_alt().size() ;i++){
      os <<m.getRef_alt()[i]<<" ";
   }
   os << endl;
   os << "Genes asociados al SNP: ";
   for (int i=0; i<m.getGenes().size();i++){
      os <<m.getGenes()[i]<<" ";
   }
   os << endl;
   os << "Indicador de si el SNP es común en la población: "<<m.getCommon()<<endl ;
   os << "Frecuencia de cada base del SNP en la población: ";
   for (int i=0; i<m.getCaf().size();i++){
      os <<m.getCaf()[i]<<" ";
   }
   os << endl;
   os << "Relevancia clínica del SNP para cada enfermedad: ";
   for (int i=0; i<m.getClnsig().size();i++){
      os <<m.getClnsig()[i]<<" ";
   }
   os << endl;
   os << "Enfermedades: "<<endl;
   for (Enfermedad e : m.getEnfermedades()){
      os <<e;
   }
   os << endl;
   return os;
}

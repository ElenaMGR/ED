
#include "clinvar.h"

using namespace std;


int main(int argc, char *argv[]){
   Clinvar bd;
   bd.load("./datos/clinvar_20160831.vcf");
   int cont = 1;
   Clinvar::iterator it;
   Clinvar::gen_iterator itg;
   Clinvar::enfermedad_iterator ite;

   for (it=bd.begin();it!=bd.end();it++){
      cout << *it << endl;
   }
   cont=1;
   for (itg=bd.gbegin(); itg!=bd.gend();itg++){
      cout << *itg << endl;
      cout<<cont++<<endl;
   }
   cont=1;
   for (ite=bd.ebegin(); ite!=bd.eend();ite++){
      cout << (*ite).first << endl;
      cout << (*ite).second << endl;
      cout<<cont++<<endl;
   }

   it = bd.find_Mut("rs786201005");
   if (it==bd.end()){
      cout<<"No encontrado"<<endl;
   }else{
      cout<<"Encontrado"<<endl;
      cout<<*it<<endl;
   }
   Mutacion mut = *it;
   vector<Enfermedad> enf = bd.getEnfermedades(mut);
   for (Enfermedad e: enf){
      cout<<e<<endl;
   }

   if (bd.erase("rs786201005"))
      cout<<"Borrada correctamente"<<endl;
   it = bd.find_Mut("rs786201005");
   if (it==bd.end()){
      cout<<"No encontrado"<<endl;
   }else{
      cout<<"Encontrado"<<endl;
   }

   ite = bd.find_Enf("CN221808:616126");
   if (ite==bd.eend()){
      cout<<"No encontrado"<<endl;
   }else{
      cout<<"Encontrado"<<endl;
   }
   ite = bd.find_Enf("CN2218126");
   if (ite==bd.eend()){
      cout<<"No encontrado"<<endl;
   }else{
      cout<<"Encontrado"<<endl;
   }


   list<Clinvar::IDenf> lista = bd.getEnfermedades("cancer");
   list<Clinvar::IDenf>::iterator itlist = lista.begin();
   while(itlist!= lista.end()){
      cout<<*itlist<<endl;
      itlist++;
   }

   set<Clinvar::IDmut> setmut;
   setmut = bd.getMutacionesEnf("CN221808:616126");
   set<Clinvar::IDmut>::iterator itset = setmut.begin();
   cout<<"Lista de ID de mutación asociadas a enfermedad"<<endl;
   while(itset!= setmut.end()){
      cout<<*itset<<endl;
      itset++;
   }
   setmut.clear();
   setmut = bd.getMutacionesGen("ISG15:9636");
   itset = setmut.begin();
   cout<<"Lista de ID de mutación asociadas a gen"<<endl;
   while(itset!= setmut.end()){
      cout<<*itset<<endl;
      itset++;
   }

   it = bd.lower_bound("1", 1022225);
   cout<<*it<<endl;
   it =  bd.upper_bound("1", 1022225);
   cout<<*it<<endl;

   itg = bd.gbegin();
   cout<<*itg<<endl;
   itg = bd.gend();
   --itg;
   cout<<*itg<<endl;

   set<Mutacion,ProbMutaciones> muta = bd.topKMutaciones(10,"cancer");
   set<Mutacion,ProbMutaciones>::iterator itaux=muta.begin();
   while(itaux != muta.end()){
      cout<<*itaux<<endl;
      itaux++;
   }
   cout<<muta.size()<<endl;

}

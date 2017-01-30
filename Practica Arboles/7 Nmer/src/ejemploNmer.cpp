#include <iostream>
#include <string>
#include "Nmer.h"

using namespace std;

int main(){
   Nmer prueba,uno,dos,tres,cuatro,cinco,seis,siete,ocho,nueve,diez;
   prueba.loadSerialized("../datos/cadenaSimple.srl");
   prueba.list_Nmer();
   cout << prueba.size() << " " << prueba.length() << endl;

   cout<<"Prefix"<<endl;
   Nmer prueba2;
   prueba2 = prueba.Prefix("A");
   prueba2.list_Nmer();

   cout<<"Union"<<endl;
   prueba2.loadSerialized("../datos/cadenaSimple.srl");
   prueba = prueba.Union(prueba2);
   prueba.list_Nmer();

   cout<<"containsString"<<endl;
   bool esta = prueba.containsString("GG");
   if (esta)
      cout<<"La cadena está"<<endl;
   else
      cout<<"La cadena no está"<<endl;

   cout<<"included"<<endl;
   prueba2.loadSerialized("../datos/cadenabosTaurus.srl");
   //prueba2.list_Nmer();
   esta = prueba.included(prueba2);
   if (esta)
      cout<<"Incluido"<<endl;
   else
      cout<<"No incluido"<<endl;

   cout<<"sequenceADN"<<endl;
   prueba.sequenceADN(4,"ACTAGCGGATCT");

   cout<<"rareNmer"<<endl;
   prueba.loadSerialized("../datos/cadenaSimple.srl");
   set<pair<string,int>,OrdenCre> res = prueba.rareNmer(2);
   set<pair<string,int>,OrdenCre>::iterator it = res.begin();
   while (it != res.end()){
      cout<<(*it).first<<" ";
      cout<<(*it).second<<endl;
      it++;
   }
   cout<<res.size()<<endl;

   cout<<"commonNmer"<<endl;
   set<pair<string,int>,OrdenDecre> res2 = prueba.commonNmer(3);
   set<pair<string,int>,OrdenDecre>::iterator it2 = res2.begin();
   while (it2 != res2.end()){
      cout<<(*it2).first<<" ";
      cout<<(*it2).second<<endl;
      it2++;
   }
   cout<<res2.size()<<endl;

   cout<<"level"<<endl;
   res = prueba.level(2);
   it = res.begin();
   while (it != res.end()){
      cout<<(*it).first<<" ";
      cout<<(*it).second<<endl;
      it++;
   }
   cout<<res.size()<<endl;

   cout<<"distancia"<<endl;
   prueba.Distance(prueba2);

   cout<<"leemos desde le fichero los 10 txt"<<endl;
   uno.loadFichero("../datos/1.txt");
   dos.loadFichero("../datos/2.txt");
   tres.loadFichero("../datos/3.txt");
   cuatro.loadFichero("../datos/4.txt");
   cinco.loadFichero("../datos/5.txt");
   seis.loadFichero("../datos/6.txt");
   siete.loadFichero("../datos/7.txt");
   ocho.loadFichero("../datos/8.txt");
   nueve.loadFichero("../datos/9.txt");
   diez.loadFichero("../datos/10.txt");




   return 0;
}

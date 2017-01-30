#include <iostream>
#include <string>
#include <vector>
#include "Nmer.h"

using namespace std;

int main(){
   Nmer prueba,uno,dos,tres,cuatro,cinco,seis,siete,ocho,nueve,diez;
   float distancia;
   prueba.loadSerialized("../datos/cadenaSimple.srl");
   prueba.list_Nmer();
   cout << prueba.size() << " " << prueba.length() << endl;
   vector<Nmer> ficheros;

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
   distancia = prueba.Distance(prueba2);
   cout<<"Distancia entre prueba y prueba2: "<<distancia<<endl;

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

   ficheros.push_back(uno);
   ficheros.push_back(dos);
   ficheros.push_back(tres);
   ficheros.push_back(cuatro);
   ficheros.push_back(cinco);
   ficheros.push_back(seis);
   ficheros.push_back(siete);
   ficheros.push_back(ocho);
   ficheros.push_back(nueve);
   ficheros.push_back(diez);

   for (unsigned int i=0; i<ficheros.size(); i++){
      for (unsigned int j=0; j<ficheros.size(); j++){
         if (i!=j){
            distancia = ficheros[i].Distance(ficheros[j]);
            cout<<"Distancia entre el archivo "<<i+1<<" y el archivo "<<j+1<<": "<<distancia<<endl;
         }
      }
   }


   return 0;
}

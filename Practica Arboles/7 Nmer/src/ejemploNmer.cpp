#include <iostream>
#include <string>
#include "Nmer.h"

using namespace std;

int main(){
   Nmer prueba;
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

   return 0;
}

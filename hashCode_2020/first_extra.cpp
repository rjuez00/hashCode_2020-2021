#include <bits/stdc++.h>

using namespace std;


struct libreria {
  long long lid;
  long long sign_up_time; // sign up time
  long long books_per_day; // books per day
  vector <long long> book_ids;
  long long nbooks;

  double score1;
  long double priority;
  long double priority_up_to_date;


  long long time_to_last;
  long long time_day_zero;
  long long tiempo_gratis;
  short unsigned flag;

};



vector <long long> puntuaciones;

long long dias=0;


vector<long long> intersection(vector<long long> &v1,
                                      vector<long long> &v2){
    vector<long long> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

bool compar_punt(const long long& p1, const long long& p2) {
  return puntuaciones[p1] > puntuaciones[p2];
}

int main (void){
  long long n, cantidad_libraries, daysforscanning;
  int temp;
  vector <libreria> librerias;
  
  
  cin >> n >> cantidad_libraries >> daysforscanning;
  
  for(int i =0; i<n; ++i){
    cin >> temp;
    puntuaciones.push_back(temp);
  }

  
  //parsing input and calculating first puntuations
    for(int i=0; i<cantidad_libraries; ++i){
      libreria mylib;
      cin >> mylib.nbooks >> mylib.sign_up_time >> mylib.books_per_day;
      long long ttt, sum=0;
      mylib.lid = i;
      for(int j=0; j<mylib.nbooks; ++j) {

        cin >> ttt;
        mylib.book_ids.push_back(ttt);
        sum+=puntuaciones[ttt];
      }

      sort(mylib.book_ids.begin(), mylib.book_ids.end(), compar_punt);

      mylib.time_to_last = mylib.nbooks/mylib.books_per_day;
      
      mylib.time_day_zero = min(mylib.time_to_last, daysforscanning-mylib.sign_up_time);
      mylib.tiempo_gratis= -mylib.time_to_last + daysforscanning - mylib.sign_up_time;
      sum/=mylib.nbooks;
      sum*=mylib.books_per_day;
      mylib.score1=sum;
      mylib.priority = mylib.score1*mylib.time_day_zero/mylib.sign_up_time;

      librerias.push_back(mylib);

    }
    vector <libreria> orden_librerias;
    long long signing_up=0;
    long long signing_remaining;
  


  //first library to add
    for(int i=0; i<cantidad_libraries;++i) {
      if(librerias[i].priority>librerias[signing_up].priority) signing_up=i;
    }
    signing_remaining=librerias[signing_up].sign_up_time;
    orden_librerias.push_back(librerias[signing_up]);
    librerias.erase(librerias.begin()+signing_up);
    cantidad_libraries--;


  //selecting next library to insert
    for(long iterador=cantidad_libraries; cantidad_libraries>=0; cantidad_libraries--){
      
      if(dias>daysforscanning)break;
      unordered_set <long long> alreadyscanned;
      // guardar en el alreadyscanned los libros ya escaneados
      for(auto nowlibscanned: orden_librerias){
        for(auto book: nowlibscanned.book_ids){
          alreadyscanned.insert(book);}}
      
      vector<long long> alreadyscanned_vec(alreadyscanned.size());
      copy(alreadyscanned.begin(), alreadyscanned.end(), alreadyscanned_vec.begin());
      
      //update score of the libraries with the actual state of scanned books
        for(long index = 0; index<cantidad_libraries; index++){
          libreria *newcandidate = &librerias[index];
          newcandidate->time_day_zero= min(newcandidate->time_to_last, daysforscanning -dias -newcandidate->sign_up_time);
          newcandidate->tiempo_gratis= -newcandidate->time_to_last + daysforscanning -dias - newcandidate->sign_up_time;
          newcandidate->priority = newcandidate->score1*newcandidate->time_day_zero/newcandidate->sign_up_time;
          vector <long long> interseccion_actual = intersection(alreadyscanned_vec, newcandidate->book_ids);
          newcandidate->priority_up_to_date = newcandidate->priority*(1 - (interseccion_actual.size()/newcandidate->book_ids.size()));

        }
      //choose the best library for scanning next
          signing_up=-1;
          long bestscoreyet=-1;

          for( long index=0; index< cantidad_libraries; index++){
            if(librerias[index].priority_up_to_date > bestscoreyet && librerias[index].tiempo_gratis<0) {
              signing_up = index;
              bestscoreyet = librerias[index].priority_up_to_date;
            }
          }

          //maybe everyone has free time now so lets check
          if(signing_up == -1){
          for( long index=0; index< cantidad_libraries; index++){
            if(librerias[index].priority_up_to_date > bestscoreyet) {
              signing_up = index;
              bestscoreyet = librerias[index].priority_up_to_date;
            }
          }
          }
        if(signing_up == -1) break;
      //TAKING THE SELECTED LIBRARY, DELETING IT FROM THE ORIGINAL VECTOR AND ADDING IT TO ORDRED
        dias+=librerias[signing_up].sign_up_time;
        orden_librerias.push_back(librerias[signing_up]);
        librerias.erase(librerias.begin()+signing_up);
    }

  //Output 
    cout << orden_librerias.size() << "\n";

    for(auto nowlib: orden_librerias){
      cout << nowlib.lid << " " << nowlib.book_ids.size() << "\n";
      //STARTING FROM THE HIGHEST SCORE WHICH IS AT THE END THATS WHY I REVERSE THE VECTOR
      for(auto nowbook: nowlib.book_ids){
        cout << nowbook << " ";
      }
      cout << "\n";
    }





}

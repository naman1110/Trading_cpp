#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>
#include <mutex>
#include <queue>
#include <thread>
#include <fstream>   // Alternate for fast CSV <fast-cpp-csv-parser/csv.h>
#include <sstream>

std::mutex dataMutex;

void calma(double &ma,double &maprev,const std::vector<double> &fields,int period){
      for(int i=0;i<period;i++){
        ma+=fields[i];
      }
      maprev=ma-fields[0]+fields[period];
      ma=ma/period;
      maprev=maprev/period;

}


int main() {
    std::ifstream file("NIFTY 50_Data.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1; // or handle the error in an appropriate way
    }

    std::string line;
    std::vector<double> fields;
    while (std::getline(file, line)) {
        
        std::string field;
        std::stringstream ss(line);
        int c=0;
        while (std::getline(ss, field, ',')) {
            c++;
            if (c==5){ std::string str=field.substr(1, field.size()-3);
                      double val=std::stod(str);
                      fields.push_back(val);}
                    }
      
    }
     file.close();
     double ma200=0,ma50=0,maprev200=0,maprev50=0;


         std::thread thread1(calma,std::ref(ma200),std::ref(maprev200),fields,200);
         std::thread thread2(calma,std::ref(ma50),std::ref(maprev50),fields,50);

         thread1.join();
         thread2.join();
         double manow=ma50-ma200;
         double maprev=maprev50-maprev200;

         if(manow>0&&maprev<0) std::cout<<"It's a buy signal from indicator but look out for more confirmations.";
         
         else std::cout<<"Look for price action";

   
    return 0;
}

// 9,21,50,100 are important Moving averages for traders.
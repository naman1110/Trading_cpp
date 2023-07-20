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

void calema(double &ema,double &emaprev,const std::vector<double> &fields,int period){
     
      double factor=2.0/(period+1);
      ema=fields[period-1];
      emaprev=fields[period];
      for(int i=period-1;i>=0;i--){
        ema=(fields[i]-ema)*factor+ema;
        emaprev=(fields[i+1]-emaprev)*factor+emaprev;

      }
}


int main() {
   //Date,Open,High,Low,Close,Adj Close,Volume
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
     double ema200=0,ema50=0,emaprev200=0,emaprev50=0;


         std::thread thread1(calema,std::ref(ema200),std::ref(emaprev200),fields,200);
         std::thread thread2(calema,std::ref(ema50),std::ref(emaprev50),fields,50);

         thread1.join();
         thread2.join();
         
         double emanow=ema50-ema200;
         double emaprev=emaprev50-emaprev200;

         if(emanow>0&&emaprev<0) std::cout<<"It's a buy signal from indicator but look out for more confirmations.";
         
         else std::cout<<"Look for price action"<<std::endl;

        

   
    return 0;
}

// 9,21,50,100 period are important Moving averages for traders.

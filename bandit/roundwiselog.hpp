#pragma once

#include "util.hpp"
#include "../arm/arm.hpp"
#include "../policy/policy.hpp"

namespace bandit{ 
class RoundwiseLog{
public:
  uint K, P, T, run;
  std::vector<std::vector<std::vector<double> > > roundwiseRewards;
  std::vector<std::vector<std::vector<double> > > roundwiseRegrets;
  RoundwiseLog(uint K, uint P, uint T): K(K), P(P), T(T) {
  
 roundwiseRewards =  std::vector<std::vector<std::vector<double> > >(K, std::vector <std::vector<double> >(T, std::vector<double>(P,0.0)));
 roundwiseRegrets =  std::vector<std::vector<std::vector<double> > >(K, std::vector <std::vector<double> >(T, std::vector<double>(P,0.0)));

//  roundwiseRegrets = std::vector<std::vector<std::vector<double>>>(K,std::vector<double>(T,0.0));
// roundwiseRewards = std::vector<std::vector<std::vector<double>>(K,std::vector<double>(T,0.0));
    run=0;
  }
  //start new run 
  void startRun(){
    run+=1;
  }
  // policy p at round t chose arm k and received reward r
  void record(uint p, uint t, uint k, double r, double regretDelta){
   roundwiseRewards[p][t][k]=r;    //shpaik
   roundwiseRegrets[p][t][k]=regretDelta;  //shpaik
   printf("in_in_record t:%d  k:%d reward %10.5f", t, k, roundwiseRewards[p][t][k]);
   printf("in_in_record  write t:%d  k:%d regret %10.5f", t, k, roundwiseRegrets[p][t][k]);
   
  }
};

class RoundwiseLogWriter{
public:
  static void logWrite(RoundwiseLog &log,
       std::vector<std::string> armNames, std::vector<std::string> policyNames,
      uint T, std::string filename, bool rewardPlot=true, bool regretPlot=true)

{
//    const uint K = armNames.size();
    const uint K = 2;
    // const uint P = policyNames.size();
   // const uint P = 2;
    const uint p = 2;


	uint k ;
    std::ofstream ofs( filename );
    ofs << "#averaged result over " << log.run << " trials" << std::endl;
    for(uint i=0;i<K;++i){
      ofs << "#arm" << i << " " << armNames[i] << std::endl;
    }
    
    //  uint p=1;
// for(uint p=0;p<P;++p){
      ofs << "#policy " << p << " " << policyNames[p] << std::endl;
//    }
    ofs.setf(std::ios::fixed, std::ios::floatfield);



    ofs << "#results:" << std::endl;
    ofs << "#T" ; 
 
  for(uint i=0; i<K;++i){
      if(rewardPlot){
        ofs << " reward" << i;
      }
      if(regretPlot){
        ofs << " regret" << i ;
      }
  
    //ofs << std::endl; 

}
    ofs << std::endl; 
    
 // std::vector<std::vector<std::vector<double> > > cumulatedRewards(K,0.0);
 // roundwiseRegrets = std::vector<std::vector<std::vector<double>>>(T,std::vector<double>(K,0.0));
 //    std::vector<std::vector<double>> cumulatedRegrets(P,K, 0.0);
//	 uint p =7;
 

 // for(uint p=0;p<P;++p){ 

  for(uint t=0;t< 1300;++t){
      ofs << (t+1);
      printf("\n aaat: %d policy :%d", t,p);
 //    getchar(); 


      for (uint k =0; k <K ; ++k){
// cumulate 할필요없음  
//		cumulatedRewards[p][t]+=log.roundwiseRewards[p][t][k];
//       	cumulatedRegrets[p][t]+=log.roundwiseRegrets[p][t][k];

      // if(rewardPlot){
      // ofs << std::setprecision(2) << " " << cumulatedRewards[p][k];
         ofs << std::setprecision(9) << " " << log.roundwiseRewards[p][t][k];
       
    printf(" in log write t:%d  k:%d reward %10.5f", t, k, log.roundwiseRewards[p][t][k]);
         // getchar();
       //jj }
       // if(regretPlot){
          ofs << std::setprecision(9) << " " << log.roundwiseRegrets[p][t][k];
          printf("     regret write : %10.5f", log.roundwiseRegrets[p][t][k]);
	  // getchar();
       //jj  }
       //ofs << std::endl;

       // getchar();

      }
 
          ofs << std::endl;
  } //for T
 
 
// }; // for P

};

}; 
}//namespace

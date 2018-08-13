#pragma once
//shpaik 0401

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//shpaik using C lanuage
#include <stdio.h>
#include "util.hpp"
#include "../arm/arm.hpp"
#include "../policy/policy.hpp"
#include "../bandit/roundwiselog.hpp"

namespace bandit{

typedef std::shared_ptr<Arm> ArmPtr;
typedef std::shared_ptr<Policy> PolicyPtr;

template<class Log = RoundwiseLog>
class Simulator{
  std::vector<ArmPtr>    arms;
  std::vector<PolicyPtr> policies;
  uint optimalArm;
public:
  Simulator(const std::vector<ArmPtr> &arms, const std::vector<PolicyPtr> &policies):
    arms(arms), policies(policies) {
    std::vector<double> expectedRewards(arms.size(), 0.0);
   
    for(uint i=0;i<arms.size();++i){
          expectedRewards[i] = arms[i]->getExpectedReward();
	  printf ("\n in Simualtor expectd Reward %d = [%10.5f]", i, expectedRewards[i]);
		// getchar();
    }

    optimalArm = vectorMaxIndex(expectedRewards);
    printf ("\n optimalArm  %d ", optimalArm);


}
  void debugPrint(){
    for(uint i=0;i<arms.size();++i){
      std::cout << arms[i]->toString() << std::endl;
    }  
    for(uint p=0;p<policies.size();++p){
      std::cout << policies[p]->toString() << std::endl;
    }  
  }

// exec와 run을 합친 버전임 

  void run(Log &log, const uint T){
      log.startRun();
      uint t;
      float matrix[9000][2];
      ifstream read;
      ofstream write;
  // char* srcFile = "s.txt";
      read.open("ss2_input.txt",ios::in);
      write.open("scopy.txt");
      printf ("\n aaaasssssut");
 	 
	if(!read)
     {
      cout  << "open fail"  << endl;
   } 

  if (read.is_open()) {
  
   
     for(uint t=0; t< 1300 ; ++t){
      printf ("\n bbbsssssut");
      printf ("\n T=%d", T);
      printf ("\n t=%d", t);
        //getchar();
//	printf ("\n sinput.txt  T=%d,  t= %d", T,t);

        // for(uint p=0;p<policies.size();++p) {
      uint p =4; // policy 번호를 써줄것  ; 
 //        execSingleRound(log, p, t);
    
        uint arm = policies[p]->selectNextArm();
        printf (" arm: %5d,   T :%5d", arm,t);
	 
        double reward = arms[arm]->pull();
       	    
	printf ("\n  in for t %5d", t);  
        // getchar();
        for (int j=0 ; j < 2 ; ++j){        

		 read >> matrix[t][j];


		// int temp_rtt = atoi(line); 
		//int temp_rtt = std::stoi(matrix[i][j]); 
		float temp_rtt = matrix[t][j]; 
            	// for(i=0 ; i < sizeof(read);i++)
           	// {
    		 //get tchar();         
	    	printf ("\n t= %d, j= %d, temp_rtt : %f", t,j,temp_rtt);
    		// getchar();         
                double  reward = 1.0 / double(temp_rtt) ;
                printf ("\n reward : %10.5f", reward);
                cout << reward <<endl;
    	//	 getchar();         
// while	}  

       	        printf ("\n before updatge state reward : %10.5f", reward);
                 policies[p]->updateState(arm, reward); 
  printf ("\n execSingleRound after policis" );

    		double optimalExpectedReward = arms[optimalArm]->getExpectedReward();
  
       //		double armExpectedReward  = arms[arm]->getExpectedReward();
 		double armExpectedReward   = reward;
    		double regret = optimalExpectedReward - armExpectedReward;
		printf(" optimalRW: %lf", optimalExpectedReward);
		printf(" armReward: %lf", armExpectedReward);
		printf(" regret: %lf",regret);
		// getchar();
		log.record(p, t, j, reward, regret);
  		}

//       };

       };
  
  // read.close();


};    //read open 되면 

  read.close();

};  //execSingle... 의 

};//  // Simulator
} //namespace

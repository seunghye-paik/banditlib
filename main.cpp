#include <iostream>

#include "bandit/util.hpp"
#include "arm/arm.hpp"
#include "arm/arm_bernoulli.hpp"
#include "arm/arm_normal.hpp"
#include "policy/policy.hpp"
#include "policy/policy_egreedy.hpp"
#include "policy/policy_ucb.hpp"
#include "policy/policy_ucbv.hpp"
#include "policy/policy_klucb.hpp"
#include "policy/policy_moss.hpp"
#include "policy/policy_random.hpp"
#include "policy/policy_dmed.hpp"
#include "policy/policy_ts.hpp"
#include "bandit/simulator.hpp"
#include "cmdline.h"

using namespace std;
using namespace bandit;

void example1(const uint T, const uint RunNum){
  const uint K = 10; // =arms.size();
  const uint P =8;  //=policies.size()
  RoundwiseLog log(K, P, T) ;
  vector<ArmPtr> arms;
  vector<PolicyPtr> policies;
  cout << "Simulating " << RunNum << " runs." << endl;
  
printf( "\n  in example1  T= %d,  RunNumb = %d", T, RunNum);
  
  //getchar();
  for(uint run=0;run<RunNum;++run){
    cout << "run=" << run << endl;
    arms.clear(); 
     double rtt =400;
   arms.push_back( ArmPtr(new BernoulliArm(0.075)) );
   arms.push_back( ArmPtr(new BernoulliArm(0.01)) );
  arms.push_back( ArmPtr(new BernoulliArm(0.05)) );
  arms.push_back( ArmPtr(new BernoulliArm(0.02)) );
   arms.push_back( ArmPtr(new BernoulliArm(0.02)) );
  arms.push_back( ArmPtr(new BernoulliArm(0.088)) );
  arms.push_back( ArmPtr(new BernoulliArm(0.05)) );
 arms.push_back( ArmPtr(new BernoulliArm(0.01)) );
  arms.push_back( ArmPtr(new BernoulliArm(0.01)) );
 arms.push_back( ArmPtr(new BernoulliArm(0.01)) );
  
  if(K != arms.size()){
      cout << "arm size does not match" << endl;
      abort();
    }
  policies.clear();
 
  policies.push_back( PolicyPtr(new RandomPolicy(K)) );
     printf( "\n  in RandomPolicy");
  
  policies.push_back( PolicyPtr(new EGreedyPolicy(K)) );
      printf( "\n  in EGreedyPolicy");
   policies.push_back( PolicyPtr(new UCBPolicy(K)) );
        printf( "\n  in UCBPolicy");
   policies.push_back( PolicyPtr(new MOSSPolicy(K)) );
 	printf( "\n  in MOSSolicy");  
  policies.push_back( PolicyPtr(new UCBVPolicy(K)) );
	printf( "\n  in UCBVPolicy");

   //j 
   policies.push_back( PolicyPtr(new KLUCBPolicy(K)) );
     printf( "\n  in  KLUUCBPolicy");
   policies.push_back( PolicyPtr(new DMEDBinaryPolicy(K)) );
      	printf( "\n  in  DMEDBinaryPolicy");
  
    policies.push_back( PolicyPtr(new ThompsonBinaryPolicy(K)) );
     printf( "\n  in  ThompsonBinayPolicy");

  if(P != policies.size()){
      cout << "policy size does not match" << endl;
      abort();
    }
    Simulator<RoundwiseLog> sim(arms, policies);
    sim.run(log, T);
  }

  vector<string> armNames;
  for(uint i=0;i<arms.size();++i){
    armNames.push_back( arms[i]->toString() );
  }  
  vector<string> policyNames;
  for(uint p=0;p<policies.size();++p){
    policyNames.push_back( policies[p]->toString() );
  }
 RoundwiseLogWriter::logWrite(log, armNames, policyNames, T, "out/ucbv_out.txt", true, true);
}

int main(int argc, char *argv[]){
  cmdline::parser a;
  a.add<uint>("runnum", 'r', "run number", false, 1);
  a.add<uint>("roundnum", 't', "round number", false, 1300);
  a.parse_check(argc, argv);
  const uint RunNum = a.get<uint>("runnum"), T=a.get<uint>("roundnum");

  printf( "\n  in Main  T= %d   RunNumb =%d", T, RunNum);
  example1(T, RunNum);

  return 0;
}

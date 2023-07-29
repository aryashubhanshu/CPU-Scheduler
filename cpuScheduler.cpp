#include<bits/stdc++.h> 
#include <fstream>
#include<iomanip>
#include <cstdlib>
using namespace std;



class Process{
	public:
		int pId, arr_time, bur_time, comp_time, tAr_time, res_time, wait_time;
		int exec_before;  
		int remaining_time;
		
		Process(){
			exec_before=0;
			pId=0;
			arr_time=0;
			tAr_time=0;
			bur_time=0;
			res_time=-1;
			wait_time=0;
			comp_time=0;
			remaining_time=0;
			cout << "Process constructor called!" << endl;
		}
		
		//initialising the process_id, arrival time and burst time
		void initialisation(int pId, float arr_time, float bur_time){
			this->arr_time = arr_time;
			this->bur_time = bur_time;
			this->pId = pId;
			this->remaining_time=bur_time;
		}

		//initialising the completion time 
		//turnAround and waiting time calculation
		void completion(float comp_time=0){
			this->comp_time = comp_time;
			tAr_time = comp_time - arr_time;
			wait_time = tAr_time - bur_time;
		}
		
		//response time calculation
		void response(int t){
			if(res_time == -1)res_time = t - arr_time;
		}
};


class Process_Creator{
	private:
		float arr_time;
		float bur_time;
		
	public:
		Process* arr = new Process[200];
	
		Process_Creator(){
		for(int i=0;i<200;i++){
			arr_time = rand()%200+1;
			bur_time = rand()%5+1;
			arr[i].initialisation(i,arr_time,bur_time);
			cout<< "Arrival Time: "arr_time<<" Burst Time: "<<bur_time<< " "<<endl;
		}
		cout << "Process_Creator constructor called! "<< endl;
		}
};


class Scheduler{
	private:
		int runQ[50]={0}; //running queue 
		int readyQ[200]={0};  //processes id which are ready to get executed
		int top=-1;  // indicate the top element of readyQ .just like front in runQ.
		int front;  //the top element in runQ
		int start_exec_time=-1;  //stores the time when the runnning process started its execution 
		
	public:
		ofstream out;
		Process_Creator myProcess;
		Scheduler(){
			cout << "Scheduler constructor called! " << endl;
			front=-1;	
		}

		int enqueue(int pId,int t){
			if(front==49) return 0;
			else{
				cout<< "enqueued" << endl;
				front++;
				runQ[front]=pId;
				if(front==0){
					start_exec_time=t;
					out.open("Status.txt",ios_base::app);
					out << setw(20) << t;
					out << setw(20) << myProcess.arr[runQ[0]].pId;
					out << setw(20) << "arrived";
					out << endl;
					out.close();
					myProcess.arr[runQ[0]].response(t);
				}
				return 1;
			}
		}
		
		int dequeue(int t){
			if(front==-1) return 0;
			else{
				cout << "dequeued" << endl;
				
				int p_executed=runQ[0];
				myProcess.arr[runQ[0]].completion(t);
				start_exec_time=t;
				for(int i=0;i<front;i++)runQ[i]=runQ[i+1];
				runQ[front]=0;
				front--;
				out.open("Status.txt",ios_base::app);
				out << setw(20) << t;
				out << setw(20) << myProcess.arr[p_executed].pId;
				out << setw(20) << "Exit";
				out << endl;
				if(front!=-1){
					out << setw(20) << t;
					out << setw(20) << myProcess.arr[runQ[0]].pId;
					out << setw(20) << "Arrived";
					out << endl;
					out.close();
					myProcess.arr[runQ[0]].response(t);
				}		
				myProcess.arr[p_executed].exec_before=-1;
				return 1;
			}
		}
		
		int FCFS(int t){
			cout << t<<" Millisecond Number" << endl;
			for(int i=0;i<200;i++){
				if(myProcess.arr[i].exec_before!=-1 && myProcess.arr[i].arr_time==t){
					top++;
					readyQ[top]=myProcess.arr[i].pId;
				}
			}
			
			if(front!=-1 && t-start_exec_time==myProcess.arr[runQ[0]].bur_time){
				if(dequeue(t)==0){}
			}else if(front!=-1){
				out.open("Status.txt",ios_base::app);
				out << setw(20) << t;
				out << setw(20) << myProcess.arr[runQ[0]].pId;
				out << setw(20) << "Running";
				out << endl;
				out.close();
			}
			if(top!=-1 && enqueue(readyQ[0],t)){
				for(int j=0;j<top;j++){
					readyQ[j]=readyQ[j+1];
				}
				readyQ[top]=0;
				top--;
			}
				
			return 0;
		}

		int RR(int t){

			int time_quantum, time=0, i, remain, temps=0;
			cout<<"Enter time quantum: ";
			cin>>time_quantum;

			for(int i=0;i<200;i++){
				if(myProcess.arr[i].exec_before!=-1 && myProcess.arr[i].arr_time==t){
					top++;
					readyQ[top]=myProcess.arr[i].pId;
				}
				myProcess.arr[i].remaining_time = myProcess.arr[i].bur_time;
			}

			if(front!=-1 && t-start_exec_time==myProcess.arr[runQ[0]].bur_time){
				if(dequeue(t)==0){}
			}else if(front!=-1){
				out.open("Status.txt",ios_base::app);
				out << setw(20) << t;
				out << setw(20) << myProcess.arr[runQ[0]].pId;
				out << setw(20) << "Running";
				out << endl;
				out.close();
			}

			if(top!=-1 && enqueue(readyQ[0],t)){
				for(int j=0;j<top;j++){
					readyQ[j]=readyQ[j+1];
					
					for(time=0,i=0;remain!=200;){
						if(myProcess.arr[i].remaining_time<=time_quantum && myProcess.arr[i].remaining_time > 0){
							time += myProcess.arr[i].remaining_time;
							myProcess.arr[i].remaining_time = 0;
							temps = 1;
						}else if(myProcess.arr[i].remaining_time > 0){
							myProcess.arr[i].remaining_time -= time_quantum;
							time += time_quantum;
						}

						if(myProcess.arr[i].remaining_time==0 && temps==1){
							remain--;
							myProcess.arr[i].wait_time += time - myProcess.arr[i].arr_time - myProcess.arr[i].bur_time;
							myProcess.arr[i].tAr_time += time - myProcess.arr[i].arr_time;
							temps = 0; 
						}

						if(i==199){
							i=0;
						}else if(myProcess.arr[i+1].arr_time <= time){
							i++;
						}else{
							i=0;
						}
					}
				}
				readyQ[top]=0;
				top--;	
			}

			return  0;
		}
};


class Simulator{
	Scheduler S;
	public:
		int timer=0,end=0;
		 
		void simulating(int sim_time,string sch_name){
			
			ofstream outf;
			outf.open("Status.txt");
			outf << setw(20) << "Millisecond" ;
			outf << setw(20) << "Process Id" ;
			outf << setw(20) << "Status" ;
			outf << endl;
			outf.close();
			for(timer=1;timer<=sim_time;timer++){
				if(sch_name=="fcfs")end=S.FCFS(timer);
				else if(sch_name=="rr")end=S.RR(timer);
				if(end==1)break;
			}
			
			outf.open("Processes.txt");
			outf << setw(20) << "Process Id" ;
			outf << setw(20) << "Arrival Time";
			outf << setw(20) << "Burst Time";
			outf << setw(20) << "Comp Time";
			outf << setw(20) << "  Turnaround Time";
			outf << setw(20) << "Waiting Time";
			outf << setw(20) << "Response Time";
			outf << endl;
			for(int i=0;i<200;i++){
				outf << setw(20) << S.myProcess.arr[i].pId ;
				outf << setw(20) << S.myProcess.arr[i].arr_time;
				outf << setw(20) << S.myProcess.arr[i].bur_time;
				outf << setw(20) << S.myProcess.arr[i].comp_time;
				outf << setw(20) << S.myProcess.arr[i].tAr_time;
				outf << setw(20) << S.myProcess.arr[i].wait_time;
				outf << setw(20) << S.myProcess.arr[i].res_time;
				outf << endl;
			}
			outf.close();
		}
};



int main(){

	int simulation_time;
	string algorithm;

	cout << "Enter Simulation time in Milli: ";
	cin >> simulation_time;
	cin.ignore();

	cout << "Enter the algorithm to be used: " << endl;
	cout << "1. FCFS(First Come First Serve)" << endl;
	cout << "2. RR (Round Robin) " << endl;
	cout << "Enter FCFS or RR " << endl;
	getline(cin,algorithm);
	transform(algorithm.begin(), algorithm.end(), algorithm.begin(), ::tolower);
	
	if(algorithm=="fcfs" || algorithm=="first come first serve"){
		Simulator sim;
		sim.simulating(simulation_time,"fcfs");
	}else if(algorithm=="rr" || algorithm=="round robin"){
		Simulator sim;
		sim.simulating(simulation_time,"rr");
	}

	return 0;
}

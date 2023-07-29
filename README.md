# CPU-Scheduler

			
The simulator contains 4 classes as mentioned in the assignment: <br>
1> Process: <br>
The data members of this class should store process id, arrival time in the ready queue, CPU burst time, completion time, turn around time, waiting time, and response time. The member functions of this class assigns values to the data members and prints them. A constructor is also used. A Member function called "initialisation" is present to initialize the process and member function "completion" and "response" are also present which calculates the values of completetion and turn around time and response time. 
<br>
2> Process_creator:<br>
This class creates 200 processes dynamically. And its constructor initializes the process with arrival time and burst time randomly. 
<br>
3> Scheduler:<br>
This class contains the codes of FCFS(First Comes First Serve) and RR(Round Robin) using appropriate algorithms. The class maintaines a ready queue and a running queue for the same.
<br>
4> Simulator:<br>
This class creates/calls the simulator object. <br>
This class also handles I/O proceses and creates status.txt and process.txt which prints the values as per said in the given assignment.
<br>
Finally the main function takes input for simulation time and the algorithm to call. Then, it calls the desired algorithm. And finally as an output status.txt and process.txt files will be created.
<br>
The output of FCFS algorithm is in the zip file with simulation time 5 ms.
<br>
<br>
The functions used:<br>
Scheduler class private data members are run queue and ready queue, top (indicating the top element of ready queue), front (indicating the first element in run queue), start_exec_time (stores the time when the running process started its execution).
<br>
The member functions enqueue and dequeue are present.<br>
enqueue function: The function prints the status of the current running process ie. if it is arrived or not.<br>

dequeue function: The function calculated the completion time by calling the Process class function completion and then printing in the status of process ie. Exit or Arrived and then it finally calls the response function which calculates the response time of the completed process.

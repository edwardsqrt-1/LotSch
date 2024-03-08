/* 
 * Creator: Edward Bierens
 * Date Due: 7 March 2024 
 * Language: C++
 * 
 * Description: This program simulates a scheduler where each process is given a ticket number,
 * and the scheduler comes up with a random ticket number to determine which process "wins" and
 * goes next. hence the name, Lottery Scheduler
 *	
 */

// Including universal libraries
#include <iostream>
#include <random>
#include <vector>

// Class to define a process, for this assignment only the ID, runtime, and ticket are the important attributes
class Process {
	
	private:
		int id; // Process ID
		unsigned int ticket; // The ticket variable needed for the scheduler
		
	public:
		Process(int pid); // Process Constructor 
		unsigned int getID() { return id; } // Gets the id of process
		unsigned int getTicket() { return ticket; } // Gets the ticket of the process
		void setTicket(unsigned int new_ticket) { ticket = new_ticket; } // Set a ticket for process
		int execute(); // Executes a process

};

// Process constructor
Process::Process(int pid) : id(pid) {} 

// Simulate a process running
int Process::execute() {
	
	std::cout << "Process with ID " << id << " has been selected to run!\n";
	std::cout << "Process with ID " << id << " complete!\n"; 
	return 0;
	
}


// Class to define a lottery scheduler
class LotteryScheduler {
	
	private:
		std::vector<Process> tasklist;
		std::vector<unsigned int> tickets_given;
		unsigned int task_count;
		
	public:
		LotteryScheduler() : task_count(0) {}
		void executeNextProcess();
		void addProcess(Process p);
		void removeProcess(int id);
		void runScheduler();
		
};

// Will execute the next process
void LotteryScheduler::executeNextProcess() {
	
	// Get a random index for the ticket list and choose the corresponding one
	int index = rand() % task_count;
	unsigned int ticket_chosen = tickets_given[index];
	
	// Find the process with the ticket and run it, then remove it
	int i;
	for (i = 0; i < task_count; i++) {
		if (tasklist[i].getTicket() == ticket_chosen) {
			tasklist[i].execute();
			removeProcess(tasklist[i].getID());
		}
	}

	
}

// Adds a new process
void LotteryScheduler::addProcess(Process p) {
	
	// Ensure no duplicate id exists
	for (int i = 0; i < task_count; i++) {
		
		if (tasklist[i].getID() == p.getID()) {
			std::cout << "Error: Process ID already exists! Process not added.\n";
			return;
		}
		
	}
	
	// Generate a ticket number (will use 4 digits)
	bool conflictingTicket;
	unsigned int ticket_gen;
	do {
		
		// Generate random ticket
		conflictingTicket = 0;
		ticket_gen = rand() % 9001 + 1000;
		
		// Ensure it does not conflict earlier ones
		for (int i = 0; i < task_count; i++ ) {
			
			if (tickets_given[i] == ticket_gen) {
				
				conflictingTicket = 1;
				break;
				
			}
			
		}
		
	} while (conflictingTicket);
	
	// Update scheduler values
	p.setTicket(ticket_gen);
	tasklist.push_back(p);
	tickets_given.push_back(ticket_gen);
	task_count++;
	
	
}


// Delete a process from the scheduler
void LotteryScheduler::removeProcess(int id) {
	

	// Delete process
	unsigned int ticket_to_delete;
	for (int i = 0; i < task_count; i++) {
		
		if (tasklist[i].getID() == id) {
			
			ticket_to_delete = tasklist[i].getTicket();
			tasklist.erase(tasklist.begin() + i);
			break;
		}
		
	}
	
	// Delete ticket + decrement number of tasks
	for (int i = 0; i < task_count; i++) {
		
		if (tickets_given[i] == ticket_to_delete) {
			
			tickets_given.erase(tickets_given.begin() + i);
			task_count--;
			return;
		}
		
	}
	
} 


// This mainly just runs all processes in scheduler. Nothing fancy.
void LotteryScheduler::runScheduler() { while (task_count != 0) executeNextProcess(); }

// Main program
int main(int argc, char* argv[]) {

	// Set up seed for random number generator
	srand(0);
	
	// Declare a lottery scheduler
	LotteryScheduler sch;
	
	// Fill up the scheduler with some processes
	for (int id = 10; id < 200; id += 2) sch.addProcess(Process(id));
	
	// Run the scheduler and exit
	sch.runScheduler();
	return 0;
	
}

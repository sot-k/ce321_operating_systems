/* schedule.c
 * This file contains the primary logic for the
 * scheduler.
 */
#include "schedule.h"
#include "macros.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define NEWTASKSLICE (NS_TO_JIFFIES(100000000))

/* Local Globals
 * rq - This is a pointer to the runqueue that the scheduler uses.
 * current - A pointer to the current running task.
 */
struct runqueue *rq;
struct task_struct *current;

/* External Globals
 * jiffies - A discrete unit of time used for scheduling.
 *			 There are HZ jiffies in a second, (HZ is
 *			 declared in macros.h), and is usually
 *			 1 or 10 milliseconds.
 */
extern long long jiffies;
extern struct task_struct *idle;

/*-----------------Initilization/Shutdown Code-------------------*/
/* This code is not used by the scheduler, but by the virtual machine
 * to setup and destroy the scheduler cleanly.
 */

 /* initscheduler
  * Sets up and allocates memory for the scheduler, as well
  * as sets initial values. This function should also
  * set the initial effective priority for the "seed" task
  * and enqueu it in the scheduler.
  * INPUT:
  * newrq - A pointer to an allocated rq to assign to your
  *			local rq.
  * seedTask - A pointer to a task to seed the scheduler and start
  * the simulation.
  */
void initschedule(struct runqueue *newrq, struct task_struct *seedTask)
{
	seedTask->next = seedTask->prev = seedTask;
	newrq->head = seedTask;
	newrq->nr_running++;

}

/* killschedule
 * This function should free any memory that
 * was allocated when setting up the runqueu.
 * It SHOULD NOT free the runqueue itself.
 */
void killschedule()
{
	return;
}


void print_rq () {
	struct task_struct *curr;

	printf("Rq: \n");
	curr = rq->head;
	if (curr)
		printf("%p", curr);
	while(curr->next != rq->head) {
		curr = curr->next;
		printf(", %p", curr);
	};
	printf("\n");
}

/*-------------Scheduler Code Goes Below------------*/
/* This is the beginning of the actual scheduling logic */

/* schedule
 * Gets the next task in the queue
 */
void schedule()
{
	static struct task_struct *nxt = NULL;
	struct task_struct *curr, *min_good_proc, *temp;
	unsigned long long min_goodness, max_waiting, min_burst;

//	printf("In schedule\n");
//	print_rq();

	current->need_reschedule = 0; /* Always make sure to reset that, in case *
								   * we entered the scheduler because current*
								   * had requested so by setting this flag   */

	if (rq->nr_running == 1) {
		context_switch(rq->head);
		nxt = rq->head->next;
	}
	else {
    
		curr = nxt;

		if (curr!=rq->head){
			curr->Latest_timestamp = sched_clock();//for a running process the latest
                            //timestamp is the time it is removed from the cpu
			curr->Burst = curr->Latest_timestamp - curr->Starting_cpu_timestamp; // Count Burst
			curr->Exp_burst = (curr->Burst + ALPHA * curr->Exp_burst)/(1 + ALPHA); // Count Exp_burst
		}
		else{ // if curr == init skip it
			curr = curr->next;
		}

		if (curr->next == NULL){ // if current node is out of list set curr the first node of the list
			curr = rq->head->next;
		}

		list_for_each(temp,rq->head){ //Update WaitingInRQ , Used for Logistics
			temp->WaitingInRQ = sched_clock() - temp->Latest_timestamp;
		}

		max_waiting = curr->WaitingInRQ;

		min_burst=curr->Exp_burst;

		list_for_each(temp,rq->head){
			if(temp->Exp_burst < min_burst ){ // Find MIN Burst
				min_burst = temp->Exp_burst;
			}
			if(temp->WaitingInRQ > max_waiting){ //Find MAX WaitingINRq
				max_waiting = temp->WaitingInRQ;
			}
		}
		


		list_for_each(temp,rq->head){ //Count Goodness for all processes
			temp->Goodness = ((1 + temp->Exp_burst)/(1 + min_burst))*((1 + max_waiting)/(1 + temp->WaitingInRQ));
		}

		min_goodness = curr->Goodness;
		min_good_proc = curr;

		list_for_each(temp,rq->head){
			if(temp->Goodness < min_goodness){ //Find MIN Goodness
				min_goodness = temp->Goodness;
				min_good_proc = temp;
			}
		}

		
		nxt = min_good_proc;
		if (nxt != current ){ //To correct the 'bug' with logistics when the same process runs after a context switch  
			min_good_proc->Starting_cpu_timestamp = sched_clock();
		}
		context_switch(min_good_proc);
	}
}


/* sched_fork
 * Sets up schedule info for a newly forked task
 */
void sched_fork(struct task_struct *p)
{
	p->time_slice = 100;
	p->Exp_burst = 0;
	p->Burst = 0;
}

/* scheduler_tick
 * Updates information and priority
 * for the task that is currently running.
 */
void scheduler_tick(struct task_struct *p)
{
	schedule();
}

/* wake_up_new_task
 * Prepares information for a task
 * that is waking up for the first time
 * (being created).
 */
void wake_up_new_task(struct task_struct *p)
{
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;

	p->Latest_timestamp = sched_clock();//dikomas//

	rq->nr_running++;
}

/* activate_task
 * Activates a task that is being woken-up
 * from sleeping.
 */
void activate_task(struct task_struct *p)
{
	p->next = rq->head->next;
	p->prev = rq->head;
	p->next->prev = p;
	p->prev->next = p;

	rq->nr_running++;
	p->Latest_timestamp = sched_clock();// for a process outside of
  // running queue the latest timestamp is the time it joins the queue
}

/* deactivate_task
 * Removes a running task from the scheduler to
 * put it to sleep.
 */
void deactivate_task(struct task_struct *p)
{
	p->prev->next = p->next;
	p->next->prev = p->prev;
	p->next = p->prev = NULL; /* Make sure to set them to NULL *
							   * next is checked in cpu.c      */

	rq->nr_running--;
}

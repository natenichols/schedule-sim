/** @file libscheduler.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libscheduler.h"
#include "../libpriqueue/libpriqueue.h"


/**
  Stores information making up a job to be scheduled including any statistics.

  You may need to define some global variables or a struct to store your job queue elements. 
*/
typedef struct _job_t
{
  int job_id;
  int job_priority;
} job_t;

typedef struct _core_t
{
  int core_id;
} core_t;

typedef struct _scheduler_t
{
  int cores;
  scheme_t scheme;
  priqueue_t job_queue;
  priqueue_t core_queue;
  int total_jobs_complete;
  float total_wait_time;
  float total_turnaround_time;
  float total_response_time;
} scheduler_t;

scheduler_t _scheduler;

/**
  Initalizes the scheduler.
 
  Assumptions:
    - You may assume this will be the first scheduler function called.
    - You may assume this function will be called once once.
    - You may assume that cores is a positive, non-zero number.
    - You may assume that scheme is a valid scheduling scheme.

  @param cores the number of cores that is available by the scheduler. These cores will be known as core(id=0), core(id=1), ..., core(id=cores-1).
  @param scheme  the scheduling scheme that should be used. This value will be one of the six enum values of scheme_t
*/
void scheduler_start_up(int cores, scheme_t scheme)
{
  _scheduler.cores = cores;
  _scheduler.scheme = scheme;
  _scheduler.total_response_time = 0;
  _scheduler.total_turnaround_time = 0;
  _scheduler.total_wait_time = 0;
  _scheduler.total_jobs_complete = 0;
  priqueue_init(&_scheduler.job_queue, NULL);
  priqueue_init(&_scheduler.core_queue, NULL);
  for (int i = cores - 1; i >= 0; i--) {
    core_t* tempCore = malloc(sizeof(core_t));
    tempCore->core_id = i;
    priqueue_offer(&_scheduler.core_queue, tempCore);
  }
}


/**
  Called when a new job arrives.
 
  If multiple cores are idle, the job should be assigned to the core with the
  lowest id.
  If the job arriving should be scheduled to run during the next
  time cycle, return the zero-based index of the core the job should be
  scheduled on. If another job is already running on the core specified,
  this will preempt the currently running job.
  Assumption:
    - You may assume that every job wil have a unique arrival time.

  @param job_number a globally unique identification number of the job arriving.
  @param time the current time of the simulator.
  @param running_time the total number of time units this job will run before it will be finished.
  @param priority the priority of the job. (The lower the value, the higher the priority.)
  @return index of core job should be scheduled on
  @return -1 if no scheduling changes should be made. 
 
 */
int scheduler_new_job(int job_number, int time, int running_time, int priority)
{
  job_t* j = malloc(sizeof(job_t));
  j->job_id = job_number;
  j->job_priority = priority;
  _scheduler.total_response_time += time;
  priqueue_offer(&_scheduler.job_queue, j);
	return -1;
}


/**
  Called when a job has completed execution.
 
  The core_id, job_number and time parameters are provided for convenience. You may be able to calculate the values with your own data structure.
  If any job should be scheduled to run on the core free'd up by the
  finished job, return the job_number of the job that should be scheduled to
  run on core core_id.
 
  @param core_id the zero-based index of the core where the job was located.
  @param job_number a globally unique identification number of the job.
  @param time the current time of the simulator.
  @return job_number of the job that should be scheduled to run on core core_id
  @return -1 if core should remain idle.
 */
int scheduler_job_finished(int core_id, int job_number, int time)
{
  priqueue_remove(&_scheduler.job_queue, &job_number);

  core_t* tempCore = malloc(sizeof(core_t));
  tempCore->core_id = core_id;
  priqueue_offer(&_scheduler.core_queue, &tempCore);

  job_t* new_job = priqueue_poll(&_scheduler.job_queue);
  if(new_job == NULL) {
    return -1;
  }
  // TODO: MODIFY TIME
  core_t* nextCore = priqueue_poll(&_scheduler.core_queue);
  return (nextCore->core_id == core_id) ? new_job->job_id : -1;
}


/**
  When the scheme is set to RR, called when the quantum timer has expired
  on a core.
 
  If any job should be scheduled to run on the core free'd up by
  the quantum expiration, return the job_number of the job that should be
  scheduled to run on core core_id.

  @param core_id the zero-based index of the core where the quantum has expired.
  @param time the current time of the simulator. 
  @return job_number of the job that should be scheduled on core cord_id
  @return -1 if core should remain idle
 */
int scheduler_quantum_expired(int core_id, int time)
{
	return -1;
}


/**
  Returns the average waiting time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average waiting time of all jobs scheduled.
 */
float scheduler_average_waiting_time()
{
	return (_scheduler.total_jobs_complete != 0) ? _scheduler.total_wait_time / _scheduler.total_jobs_complete : 0;
}


/**
  Returns the average turnaround time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average turnaround time of all jobs scheduled.
 */
float scheduler_average_turnaround_time()
{
	return (_scheduler.total_jobs_complete != 0) ? _scheduler.total_turnaround_time / _scheduler.total_jobs_complete: 0;
}


/**
  Returns the average response time of all jobs scheduled by your scheduler.

  Assumptions:
    - This function will only be called after all scheduling is complete (all jobs that have arrived will have finished and no new jobs will arrive).
  @return the average response time of all jobs scheduled.
 */
float scheduler_average_response_time()
{
	return (_scheduler.total_jobs_complete != 0) ? _scheduler.total_response_time / _scheduler.total_jobs_complete : 0;
}


/**
  Free any memory associated with your scheduler.
 
  Assumption:
    - This function will be the last function called in your library.
*/
void scheduler_clean_up()
{
  while(_scheduler.job_queue.head != _scheduler.job_queue.tail) {
    free(priqueue_poll(&_scheduler.job_queue));
  }
  while(_scheduler.core_queue.head != _scheduler.core_queue.tail) {
    free(priqueue_poll(&_scheduler.core_queue));
  }
  priqueue_destroy(&_scheduler.job_queue);
  priqueue_destroy(&_scheduler.core_queue);
}


/**
  This function may print out any debugging information you choose. This
  function will be called by the simulator after every call the simulator
  makes to your scheduler.
  In our provided output, we have implemented this function to list the jobs in the order they are to be scheduled. Furthermore, we have also listed the current state of the job (either running on a given core or idle). For example, if we have a non-preemptive algorithm and job(id=4) has began running, job(id=2) arrives with a higher priority, and job(id=1) arrives with a lower priority, the output in our sample output will be:

    2(-1) 4(0) 1(-1)  
  
  This function is not required and will not be graded. You may leave it
  blank if you do not find it useful.
 */
void scheduler_show_queue()
{
  printf("Jobs:\n");
  print_queue(&_scheduler.job_queue);
  printf("Cores:\n");
  print_queue(&_scheduler.core_queue);
}

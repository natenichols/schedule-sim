/** @file libscheduler.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
  float burst_time;
  int arrival_time;
  int hasBeenScheduled;
} job_t;

typedef struct _core_t
{
  int core_id;
} core_t;

typedef struct _core_job_t
{
  core_t* core;
  job_t*  job;
  int     time;
} core_job_t;

typedef struct _scheduler_t
{
  int cores;
  scheme_t scheme;

  priqueue_t job_queue;
  priqueue_t core_queue;

  priqueue_t active_queue;

  int total_jobs_complete;
  float total_wait_time;
  float total_turnaround_time;
  float total_response_time;
  float total_run_time;
  int    total_responses;
} scheduler_t;

scheduler_t _scheduler;

// Helper Functions
core_job_t* scheduler_update(int time);
char* getJobID(const void * job);
char* getCoreID(const void * core);
char* getActiveID(const void * active) ;
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
int fcfs(const void* one, const void* two) {
  int dif = (((job_t*)one)->arrival_time - ((job_t*)two)->arrival_time);
  if (dif == 0) {
    return (((job_t*)one)->job_id - ((job_t*)two)->job_id);
  }
  return dif;
}

int sjf(const void* one, const void* two) {
  int dif = (((job_t*)one)->burst_time - ((job_t*)two)->burst_time);
  if(dif == 0) {
    return (((job_t*)one)->arrival_time - ((job_t*)two)->arrival_time);
  }
  return dif;
}

int psjf(const void* one, const void* two) {
  int dif = (((job_t*)one)->burst_time - ((job_t*)two)->burst_time);
  if(dif == 0) {
    return (((job_t*)one)->arrival_time - ((job_t*)two)->arrival_time);
  }
  return dif;
}

int pri(const void* one, const void* two) {
  int dif = (((job_t*)one)->job_priority - ((job_t*)two)->job_priority);
  if(dif == 0) {
    return (((job_t*)one)->arrival_time - ((job_t*)two)->arrival_time);
  }
  return dif;
}

int ppri(const void* one, const void* two) {
  int dif = (((job_t*)one)->job_priority - ((job_t*)two)->job_priority);
  if(dif == 0) {
    return (((job_t*)one)->arrival_time - ((job_t*)two)->arrival_time);
  }
  return dif;
}

int rr(const void* one, const void* two) {
  return 1;
}


int (*active_cmp1(int(*comparer)(const void *, const void *)))(const void* one, const void* two) {
  return comparer;
}

int active_cmp(const void* one, const void* two) {
  return ((core_job_t*)one)->core->core_id - ((core_job_t*)two)->core->core_id;
}

int core_cmp(const void* one, const void* two) {
  return ((core_t*)one)->core_id - ((core_t*)two)->core_id;
}

void scheduler_start_up(int cores, scheme_t scheme)
{
  _scheduler.cores = cores;
  _scheduler.scheme = scheme;

  _scheduler.total_turnaround_time = 0;
  _scheduler.total_response_time = 0;
  _scheduler.total_responses = 0;
  _scheduler.total_run_time = 0;
  _scheduler.total_wait_time = 0;
  _scheduler.total_jobs_complete = 0;

  int (*cmp)(const void*, const void*);

  switch(scheme) {
    case FCFS:
      cmp = fcfs;
      break;
    case SJF:
      cmp = sjf;
      break;
    case PSJF:
      cmp = psjf;
      break;
    case PRI:
      cmp = pri;
      break;
    case PPRI:
      cmp = ppri;
      break;
    case RR:
      cmp = rr;
      break;
    default:
      return;
  }

  priqueue_init(&_scheduler.job_queue, cmp);
  priqueue_init(&_scheduler.core_queue, &core_cmp);
  if(_scheduler.scheme == PSJF || _scheduler.scheme == PPRI) {
    priqueue_init(&_scheduler.active_queue, (*active_cmp1)(cmp));
  }
  else {
    priqueue_init(&_scheduler.active_queue, &active_cmp);
  }

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
  // printf("New Job, size of coress is %d\n\n", priqueue_size(&_scheduler.core_queue) + priqueue_size(&_scheduler.active_queue) );
  _scheduler.total_turnaround_time -= time;
  _scheduler.total_run_time += running_time;

  job_t* j = malloc(sizeof(job_t));
  j->job_id = job_number;
  if(_scheduler.scheme == RR) {
    j->job_priority = -1;
  } else {
    j->job_priority = priority;
  }
  j->burst_time = running_time;
  j->arrival_time = time;
  j->hasBeenScheduled = 0;
  
  priqueue_offer(&_scheduler.job_queue, j);
  
  //printf("New Job %d offer: ", job_number);print_queue(&_scheduler.job_queue, &getJobID);

  if((_scheduler.scheme == PSJF || _scheduler.scheme == PPRI) && (priqueue_size(&_scheduler.core_queue) == 0)) {
      // print_queue(&_scheduler.active_queue, &getActiveID);
      int core_remove = ( (core_job_t*) priqueue_at(&_scheduler.active_queue, priqueue_size(&_scheduler.active_queue)-1))->core->core_id;
      if(scheduler_quantum_expired(core_remove, time) == job_number) {
        return core_remove;
      }
      return -1;
  }

  int newCore = -1;
  core_job_t* newActive;
  do {
    newActive = scheduler_update(time);
    if (newActive != NULL && newActive->job->job_id == job_number) newCore = newActive->core->core_id;
  } while(newActive != NULL);

	return newCore;
}

core_job_t* scheduler_update(int time)
{
  // printf("Update, size of cores is %d\n\n", priqueue_size(&_scheduler.core_queue) + priqueue_size(&_scheduler.active_queue) );
  
  if (priqueue_size(&_scheduler.job_queue) <= 0 || priqueue_size(&_scheduler.core_queue) <= 0) return NULL;
  
  core_job_t* newActive = malloc(sizeof(core_job_t));
  newActive->time = time;
  newActive->job = priqueue_poll(&_scheduler.job_queue);
  newActive->core = priqueue_poll(&_scheduler.core_queue);
  _scheduler.total_wait_time += time - newActive->job->arrival_time;

  priqueue_offer(&_scheduler.active_queue, newActive);
// printf("Update after, size of cores is %d\n\n", priqueue_size(&_scheduler.core_queue) + priqueue_size(&_scheduler.active_queue) );
    
	return newActive;
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
  _scheduler.total_jobs_complete++;
  _scheduler.total_turnaround_time += time;
  // TODO: MAKE THIS MORE EFFICIENT
  int index = 0;
  int size = priqueue_size(&_scheduler.active_queue);
  while (index < size && ((core_job_t*)priqueue_at(&_scheduler.active_queue, index))->core->core_id != core_id) {
    index++;
  }
  if (index >= size) return -1;

  core_job_t* finished = priqueue_remove_at(&_scheduler.active_queue, index);
  priqueue_offer(&_scheduler.core_queue, finished->core);

   if(finished->job->hasBeenScheduled == 0)
    _scheduler.total_response_time += finished->time - finished->job->arrival_time;

  free(finished);

  int newJob = -1;
  core_job_t* newActive;
  do {
    newActive = scheduler_update(time);
    if (newActive != NULL && newActive->core->core_id == core_id) newJob = newActive->job->job_id;
  } while(newActive != NULL);
return newJob;
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
  int index = 0;
  int size = priqueue_size(&_scheduler.active_queue);
  // printf("Attempting to expire core %d with queue size %d\n", core_id, size);
  while (index < size && ((core_job_t*)priqueue_at(&_scheduler.active_queue, index))->core->core_id != core_id) {
    index++;
  }
  // printf("Index found was %d\n", index);
  
  if (index >= size) return -1;

  core_job_t* preempted_active = priqueue_remove_at(&_scheduler.active_queue, index);
  if(preempted_active->job->hasBeenScheduled == 0 && (time - preempted_active->time) > 0) {
    _scheduler.total_response_time += preempted_active->time - preempted_active->job->arrival_time;
    preempted_active->job->hasBeenScheduled = 1;
  }
  preempted_active->job->burst_time -= (time - preempted_active->time);
  preempted_active->job->arrival_time = time;
  priqueue_offer(&_scheduler.job_queue, preempted_active->job);

  job_t* newJob = priqueue_poll(&_scheduler.job_queue);
  preempted_active->time = time;
  preempted_active->job = newJob;
  _scheduler.total_wait_time += time - preempted_active->job->arrival_time;

  priqueue_offer(&_scheduler.active_queue, preempted_active);
	return preempted_active->job->job_id;
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
  while(priqueue_size(&_scheduler.job_queue) != 0) {
    free(priqueue_poll(&_scheduler.job_queue));
  }
  while(priqueue_size(&_scheduler.core_queue) != 0) {
    free(priqueue_poll(&_scheduler.core_queue));
  }  
  while(priqueue_size(&_scheduler.active_queue) != 0) {
    free(priqueue_poll(&_scheduler.active_queue));
  }
  priqueue_destroy(&_scheduler.job_queue);
  priqueue_destroy(&_scheduler.core_queue);
  priqueue_destroy(&_scheduler.active_queue);
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
  print_queue(&_scheduler.active_queue, &getActiveID);
  print_queue(&_scheduler.job_queue, &getJobID);
  
}
char* getJobID(const void * job) {
  if (job != NULL) {
    int num = ((job_t*)job)->job_id;
    int priority = ((job_t*)job)->job_priority;
    char* str = malloc(sizeof(char)*((int)log10(num+2)) + sizeof(char)*((int)log10(priority+2))+ 2);
    sprintf(str, "%d(%d)", num, priority);
    return str;
  }
  return "";
}
char* getCoreID(const void * core) {
  if (core != NULL) {
    int num = ((core_t*)core)->core_id;
    char* str = malloc(sizeof(char)*((int)log10(num+2)));
    sprintf(str, "%d", num);
    return str;
  }
  return "";
}
char* getActiveID(const void * active) {
  return (active != NULL) ? getJobID(((core_job_t*) active)->job) : "";
}

/*
* 7/10/24
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.c"

int main(int argc, char **argv) 
{
   
    FILE *file;
    struct PQ pq;
    struct PQ id_pq;
    char line[256];
    
    struct Task *jobs;
    int jobs_size = 0;
    int jobs_max_size = 16;
    int index = 0;

    struct Task job;
    int job_finish_time;
    int job_wait_time;

    int cpu_time = 0;
    int is_cpu_free = 1;
    
    pq = PQ_new();
    id_pq = PQ_new(); 
    file = fopen(argv[argc-1], "r");
    jobs = malloc(sizeof(struct Task) * jobs_max_size);

    while (fgets(line, sizeof(line), file) != NULL)
    {
        struct Task task;
        char *field;

        field = strtok(line, ",");
        task.id = atoi(field); 
    
        field = strtok(NULL, ",");
        task.priority = atoi(field);

        field = strtok(NULL, ",");
        task.arrivalTime = atoi(field);

        field = strtok(NULL, ",");
        task.processingTime = atoi(field);
        
	jobs[jobs_size] = task;
	jobs_size++;
	
	if (jobs_size == jobs_max_size)
	{
            jobs_max_size += 16;
	    jobs = realloc(jobs, sizeof(struct Task) * jobs_max_size);
	}

    }
    
    while (1)
    {

	// printf("time: %d\n", cpu_time);

	/* Push all jobs at arrival time into priority queue */ 
	while (jobs[index].arrivalTime == cpu_time && index < jobs_size)
	{
	    PQ_enqueue(&pq, jobs[index], jobs[index].priority);
	    // printf("Pushed job of id: %d\n", jobs[index].id);
	    index++;
        }

	/* Exit simulation */
	if (index == jobs_size && PQ_empty(&pq) && is_cpu_free)
	{
	    // printf("Exiting simulation...\n");
            break;
	}
	
	/* If CPU is free, start processing job */
	if (is_cpu_free && !PQ_empty(&pq))
	{
	    int priority;

	    // printf("Heap size: %d\n", pq.size);
	    // printf("Heap: %d %d %d %d\n", pq.heap[1].task.id, pq.heap[2].task.id, pq.heap[3].task.id, pq.heap[4].task.id);
            job = PQ_dequeue(&pq);
	    // printf("CPU is free, processing job with id: %d\n", job.id);
	    priority = job.priority;
	    PQ_enqueue(&id_pq, job, job.id);

	    while (priority == PQ_front(&pq).priority && !PQ_empty(&pq))
	    {
		struct Task temp = PQ_dequeue(&pq);
		// printf("same priority job detected, popping job with id: %d\n", temp.id);
	    	// printf("Heap size: %d\n", pq.size);
                PQ_enqueue(&id_pq, temp, temp.id);
	    }
		
	    /* Order jobs with same priority by lowest id */
	    job = PQ_dequeue(&id_pq);

	    while (!PQ_empty(&id_pq))
	    {
	        struct Task temp = PQ_dequeue(&id_pq);
		PQ_enqueue(&pq, temp, temp.priority);
	    }
            
	    job_finish_time = cpu_time + job.processingTime;  
	    job_wait_time = cpu_time - job.arrivalTime; 
	    
	    is_cpu_free = 0;
	}
        
        /* Finish processing job */	
	if (cpu_time == job_finish_time) // exit condition to prvent infinite loop)
	{
	    // printf("finished processing job with id: %d\n", job.id);
	    printf("%d,%d,%d,%d,%d\n", job.id, job.arrivalTime, job.processingTime, cpu_time, job_wait_time);
            is_cpu_free = 1;
	    continue;
	}	
    
        cpu_time++;
    
    } 

    fclose(file);
    free(jobs);
    PQ_clear(&pq);

    return 0;

}


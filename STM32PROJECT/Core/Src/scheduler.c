/*
 * scheduler.c
 *
 *  Created on: Dec 12, 2024
 *      Author: ADMIN
 */

#include "scheduler.h"

uint32_t current_idx_task = 0;

sTasks SCH_tasks_G[SCH_MAX_TASKS];

void SCH_Init()
{
	for (int i = 0; i < SCH_MAX_TASKS; i++)
	{
		SCH_Delete_Task(i);
	}
	current_idx_task = 0;
}

uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	if(current_idx_task < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_idx_task].pTask = pFunction;
		SCH_tasks_G[current_idx_task].Delay = DELAY / TICK;
		SCH_tasks_G[current_idx_task].Period = PERIOD / TICK;
		SCH_tasks_G[current_idx_task].RunMe = 0;
		SCH_tasks_G[current_idx_task].TaskID = current_idx_task;

		return current_idx_task++;
	}
	else return SCH_MAX_TASKS;


}

void SCH_Update()
{
	for (int i = 0; i < SCH_MAX_TASKS; i++)
	{
		if(SCH_tasks_G[i].Delay > 0)
		{
			SCH_tasks_G[i].Delay--;
		}
		else
		{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe ++;
		}
	}
}

void SCH_Dispatch_Tasks()
{
	for (int i = 0; i < current_idx_task; i++)
	{
		if(SCH_tasks_G[i].RunMe > 0)
		{
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			if (SCH_tasks_G[i].Period == 0)
			{
				SCH_Delete_Task(i);
			}

		}

	}

}


uint8_t SCH_Delete_Task(uint32_t taskID)
{
	if (SCH_tasks_G[taskID].pTask != 0)
	{
		SCH_tasks_G[taskID].pTask = 0x0000 ;
		SCH_tasks_G[taskID].Delay = 0;
		SCH_tasks_G[taskID].Period = 0;
		SCH_tasks_G[taskID].RunMe = 0;
		for (int i = taskID; i < current_idx_task; i++)
		{
			SCH_tasks_G[i] = SCH_tasks_G[i + 1];
			if (i + 1 == current_idx_task)
			{
				current_idx_task = i;
			}
		}
		return 0;
	}
	else return 1;


}




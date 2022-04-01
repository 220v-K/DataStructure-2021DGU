
//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                       ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "ptyqueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int priority,              // Task's priority
        arrived;               // Time when task was enqueued

    void setPty(int newPty)
    {
        priority = newPty;
    }   // Set the priority

    int pty() const
    {
        return priority;
    }   // Returns the priority
};

//--------------------------------------------------------------------

void main()
{
    PtyQueue<TaskData> taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        max_wait_0 = 0,     //Longest wait
        max_wait_1 = 0;

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    srand(500); //시드값 맞추기

    for (minute = 0; minute < simLength; minute++)
    {
        cout << "Current minute: " << minute << endl;
        // Dequeue the first task in the queue (if any).

        task = taskPQ.dequeue();

        if (task.pty() != -1)
        {
            cout << "Task Dequeued" << endl;
            cout << "this task's priority: " << task.pty() << endl;
            cout << "this task was arrived at " << task.arrived << ", and waited for " << minute - task.arrived << " minutes." << endl;
        }

        if (task.pty() == 0 && max_wait_0 < minute - task.arrived)
            max_wait_0 = minute - task.arrived;
        else if (task.pty() == 1 && max_wait_1 < minute - task.arrived)
            max_wait_1 = minute - task.arrived;

        // Determine the number of new tasks and add them to
        // the queue.
        int numtask = rand() % 4;
        if (numtask == 1)   //25% enqueue 1개
        {
            TaskData temptask;
            temptask.setPty(rand() % numPtyLevels);
            temptask.arrived = minute;
            taskPQ.enqueue(temptask);
        }
        else if (numtask == 2)  //25% enqueue 2개
        {
            TaskData temptask1, temptask2;
            temptask1.setPty(rand() % numPtyLevels);
            temptask1.arrived = minute;
            taskPQ.enqueue(temptask1);

            temptask2.setPty(rand() % numPtyLevels);
            temptask2.arrived = minute;
            taskPQ.enqueue(temptask2);
        }
        else    //numtask == 0, 3   //50% enqueue 0개
            cout << "No task was added this time" << endl;

        taskPQ.showStructure();
        cout << endl << endl;

    }

    cout << "Longest wait for any low-priority(0) task : " << max_wait_0 << endl;
    cout << "Longest wait for any low-priority(1) task : " << max_wait_1 << endl;

    system("pause");
}

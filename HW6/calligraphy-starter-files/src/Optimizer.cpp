//Saagar Moradia
//CS106B
//optimization
//This program will take in a TaskGroup and return all tasks that could be optimized to reduce the overall time it takes to complete the taskGRoup
//This problem can be represented as a topological graph, with task that come before being higher in the heirarchy
//This program is very simply represented as a topological graph, with nodes that depend on no tasks making up the top of the graph. Therefore, iterating
//through the graph to find the critical path by duration shouls yield the optimizable tasks
//Sources
//Lecture Slides 23
//Textbook pages 783-788
#include "TaskGroup.h"
#include "hashset.h"
#include "set.h"
using namespace std;

int timeToComplete(const TaskGroup& process);
HashSet<Task *> optimizationChecker(const TaskGroup& process, int maxTime);
int timeToCompleteHelper(const TaskGroup& process, Task*& task, Set<Task*>& visited, int& maxTime);

/**
 * This function will return a HashSet of all tasks that are canditdates for optimization
 */
HashSet<Task *> optimizationCandidatesFor(const TaskGroup& process) {
    HashSet<Task *> result;
    int maxTime = timeToComplete(process);
    result = optimizationChecker(process, maxTime);
    return result;
}
/**
 * This function will set up variables and call a helper function to compute the total time for
 * taskGroup to run
 */
int timeToComplete(const TaskGroup& process){
    Set<Task*> visited;
    int maxTime = 0;
    int time = 0;
    //go through all tasks given
    for(Task* tasks : process){
        time = 0;
        //This is at the top of the graph, look for tasks that depend on it
        if(tasks->dependsOn.isEmpty()){
            time = timeToCompleteHelper(process, tasks, visited, time);
            //add the time of this task as well
            time+= tasks->duration.length();
        }
        visited.clear();
        if(time > maxTime){
            maxTime = time;
        }
    }

    return maxTime;
}

/**
 * This helper function will use the given task and go through the set of tasks it depends on,
 * adding the max time if it is greater than the max time already established
 */
int timeToCompleteHelper(const TaskGroup& process, Task*& task, Set<Task*>& visited, int &maxTime){
    if(visited.contains(task)){
        return 0;
    } else {
        visited.add(task);
        for(Task* tasks: process){
            //part of the path that has the node
            int time = 0;
            if(tasks->dependsOn.contains(task)){
                time+= task->duration.length();
                timeToCompleteHelper(process, tasks, visited, maxTime);
                if(time > maxTime){
                    maxTime = time;
                }
            }
        }
    }
    return maxTime;

}
/**
 * This function will iterate through all tasks and reduce its duration to 0, then calculate
 * the duration of the taskGroup.
 * If the new duration is less than the maxTime established before, then the task is a candidate for
 * optimization.
 */
HashSet<Task *> optimizationChecker(const TaskGroup& process, int maxTime){
    int newTime = 0;
    HashSet<Task *> result;
    for(Task* tasks: process){
        int hold = tasks->duration.length();
        //reduce this task's duration
        tasks->duration.operator -=(hold);
        newTime = timeToComplete(process);
        cout<<newTime<<endl;
        tasks->duration.operator +=(hold);
        //if reducing the duration decreases the total time, then it is a candidate for optimization
        if(newTime < maxTime){
            result.add(tasks);
        }
    }
    return result;
}


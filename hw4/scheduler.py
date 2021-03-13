import csv
import copy
import sys

def pid(entry): # return the process id of dict passed in
    return int(entry['ProcessID'])

def arrivalTime(entry): # return process arrival time of dict passed in
    return int(entry['Arrival Time'])

def burstTime(entry): # return burst time of dict passed in
    return int(entry['Burst Time'])

def printHeader(name): # print the header for each algorithm
    print("----------------- {} -----------------".format(name))

def printWaitTurn(wait,turn): # print out the wait / turnaround time table
    print("Process ID | Waiting Time | Turnaround Time")
    tmp = ""
    for i in range(len(wait)):
        if wait[i] == None:
            continue
        tmp += "{:^10} | {:^10} | {:^10}\n".format(i+1, wait[i], turn[i]) # Building the string to print out with correct data
    print(tmp)

def printAvg(wait, turn, time, issjfp = False):
    avgWait = 0
    avgTurn = 0
    count = 0
    for i in range(len(wait)):
        if wait[i] == None:
            continue
        avgWait += wait[i]
        avgTurn += turn[i]
        count += 1
    avgWait /= count
    avgTurn /= count #add all waits and turnaround times then average them
    throughput = count/time
    #example shown had an extra decimal for sjfp so I decided to implement that
    if issjfp == False:
        print("Average Waiting Time:  {:.1f}\nAverage Turnaround Time:  {:.1f}\nThroughput:  {:.12f}\n".format(avgWait, avgTurn, throughput))
    else:
        print("Average Waiting Time:  {:.2f}\nAverage Turnaround Time:  {:.2f}\nThroughput:  {:.12f}\n".format(avgWait, avgTurn, throughput))

def fcfs(queue):
    gant = "Gantt Chart is:\n"
    wait = [None]*10
    turnaround = [None]*10
    time = 0
    for process in queue:
        if time < arrivalTime(process):
            gant += "[ {:^4} ]-- IDLE --[ {:^4} ]\n".format(time,arrivalTime(process)) # if we aren't at the time for this process yet it is idle then jump to the next ready
            time = arrivalTime(process)
        gant += "[ {:^4} ]-- {:^4} --[ {:^4} ]\n".format(time, pid(process), time+burstTime(process))
        wait[pid(process)-1] = time-arrivalTime(process) # record how long the process waited
        time += burstTime(process) # increment time by burst time of the process
        turnaround[pid(process)-1] = time-arrivalTime(process) # record the turnaround time for the process
    printHeader("FCFS")
    printWaitTurn(wait,turnaround)
    print(gant)
    printAvg(wait,turnaround,time)

def getShortestArrived(queue, time): # Function to find the process with shortest time remaining that has already arrived
    tmp = max(queue, key=burstTime)
    for process in queue:
        if arrivalTime(process) <= time and burstTime(process) < burstTime(tmp) and burstTime(process) > 0: # process must have arrived, have the shorest burst time, and have greater than 0 burst time remaining
            tmp = process
    if arrivalTime(tmp) > time:
        return None
    if burstTime(tmp) <= 0: # if only processes arrived have already been completed, return none to signal IDLE
        return None
    return tmp

# this function is not done in the best or most efficient way but it works
def sjfp(totalQueue):
    localQueue = copy.deepcopy(totalQueue) # deep copy prevents messing up data in the original queue
    gant = "Gantt Chart is:\n"
    wait = [None]*10
    turnaround = [None]*10
    time = 0
    startTime = 0
    completedProcesses = 0 # counter for how many processes have been completed
    prevProcess = getShortestArrived(localQueue, time) # keeps track of the current process being executed 
    while True:
        currProcess = getShortestArrived(localQueue, time) # get the next process in the queue
        if currProcess != prevProcess: # if currProcess and prevProcess are not the same then we already executed and should update gant chart and turnaround times
            gant += "[ {:^4} ]-- {:^4} --[ {:^4} ]\n".format(startTime, pid(prevProcess), time)
            turnaround[pid(prevProcess)-1] = time-arrivalTime(prevProcess)
            for j in totalQueue:
                if j["ProcessID"] == pid(prevProcess):
                    wait[pid(prevProcess)-1] = turnaround[pid(prevProcess)-1]-burstTime(j) # update the total time that the process waited
            completedProcesses += 1 # increment process completed counter
            prevProcess = currProcess # next time we are checking against the new current process
            startTime = time # next process starts at the current time
        if currProcess == None:
            if completedProcesses >= len(localQueue): # if all processes have been completed break out of the while loop and print stats
                    break
            while getShortestArrived(localQueue,time) == None: # if cpu is idle but there are still processes to execute, increment time till the next process starts
                time += 1
            gant += "[ {:^4} ]-- IDLE --[ {:^4} ]\n".format(startTime,time)  #update gant chart
            startTime = time
            prevProcess = getShortestArrived(localQueue, time)
        else:
            currProcess['Burst Time'] -= 1 # decrement burst time of the current process and increment time
            time += 1
    printHeader("SJFP")
    printWaitTurn(wait,turnaround)
    print(gant)
    printAvg(wait,turnaround,time,True)

def rr(queue, quantum):
    arrivedQueue = []
    done = []
    wait = [None]*10
    bursts = [0]*10
    turnaround = [None]*10
    gant = "Gantt Chart is:\n"
    time = 0
    while True:
        for process in queue:
            if arrivalTime(process) <= time and process not in arrivedQueue and process not in done: # add all processes that have arrived to the arrived
                arrivedQueue.append(process)                                                         # queue if they aren't already done or arrived
                bursts[pid(process)-1] = burstTime(process)
        if len(arrivedQueue) == 0: # if there are no processes arrived but there will be in the future we are IDLE till the new process arrives
            for process in queue:
                if process not in done:
                    gant += "[ {:^4} ]-- IDLE --[ {:^4} ]\n".format(time,arrivalTime(process))
                    time = arrivalTime(process) # skip forward till the next process arrives
                    arrivedQueue.append(process)
                    bursts[pid(process)-1] = burstTime(process) # update the burst list
                    break
        for i in range(len(arrivedQueue)):
            cpid = pid(arrivedQueue[0])
            if bursts[cpid-1] > quantum: # if the process will not be completed in the quantum
                time += quantum
                bursts[cpid-1] -= quantum
                gant += "[ {:^4} ]-- {:^4} --[ {:^4} ]\n".format(time-quantum, cpid, time)
                for process in queue:
                    if arrivalTime(process) <= time and process not in arrivedQueue and process not in done: # check for processes that arrived in the time quantum
                        arrivedQueue.append(process)                                                         # and append them before the current process gets appended
                        bursts[pid(process)-1] = burstTime(process) # Update remaining burst time            # to the back of the queue
                arrivedQueue.append(arrivedQueue.pop(0)) # remove the process from the front of the queue and put it on the back
            else:
                time += bursts[cpid-1]
                gant += "[ {:^4} ]-- {:^4} --[ {:^4} ]\n".format(time-bursts[cpid-1], pid(arrivedQueue[0]), time) 
                turnaround[cpid-1] = time-arrivalTime(arrivedQueue[0])
                wait[cpid-1] = turnaround[cpid-1] - burstTime(arrivedQueue[0]) # process is completed so comput wait/turnaround times
                bursts[cpid-1] = 0
                done.append(arrivedQueue.pop(0)) # put completed process in the done list to keep track of how many processes we have completed
        if len(done) == len(queue): # if done and queue are the same length we have completed every process and should exit the endless loop
            break
    printHeader("Round Robin")
    printWaitTurn(wait, turnaround)
    print(gant)
    printAvg(wait, turnaround, time)

def main():
    filename = sys.argv[1]
    timeQ = int(sys.argv[2])
    with open(filename, "r") as f:
        data = csv.DictReader(f) # read everything in the file as a dictionary
        queue = []
        for tmp in data: # DictReader returns a DictReader object in the version installed on the CS server instead of dict so I convert everything
            for key in tmp.keys(): # to a normal dict and append those dicts to a list of all our processes
                tmp[key] = int(tmp[key])
            queue.append(dict(tmp))
        queue.sort(key=pid)
        queue.sort(key=arrivalTime) # sort the queue by pid then by arrival time for use in fcfs and sjfp algorithms
        fcfs(queue)
        sjfp(queue)
        rr(queue, timeQ)

if __name__ == '__main__':
    main()
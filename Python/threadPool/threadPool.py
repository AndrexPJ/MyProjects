import threading
import mutex
import knapsack
import random
import time

class threadPool:
        pool = []
        job_queue = []
        queue = []
        complexities = []
        priorities = []
        count = 0
        complexity = 0
        job_lock = threading.Lock()
        stop_flag = False
        thread_table = [] 

        def search_job(self, my_num):
                while(True):
                        if(self.stop_flag):
                                return
                        ##################################
                        ##        critical area        ###
                        self.job_lock.acquire()
                        self.thread_table[my_num] = True
                        queue_n = len(self.queue)
                        if(queue_n > 0):
                                jobs_n = len(self.job_queue)
                                if (jobs_n  < 1):#< self.count):
                                        _queue = knapsack.packKnapsack(self.priorities,self.complexities, queue_n ,self.count)
                                        #print _queue 
                                        if(_queue == []):
                                                self.priorities.pop(0);
                                                self.complexities.pop(0);
                                                self.queue.pop(0);  
                                        _queue_del = []
                                        _prior_del = []
                                        _complx_del = []
                                        for i in _queue:
                                                self.job_queue.append(self.queue[i])
                                                _prior_del.append(self.priorities[i])
                                                _complx_del.append(self.complexities[i])
                                                _queue_del.append(self.queue[i])
                                        for i in _queue:
                                                self.priorities.remove(_prior_del.pop())
                                                self.complexities.remove(_complx_del.pop())
                                                self.queue.remove(_queue_del.pop())
                        if(len(self.job_queue) < 1):
                                self.thread_table[my_num] = False
                                self.job_lock.release()
                                time.sleep(1)
                                continue
                        (f,args) = self.job_queue.pop(0)
                        self.job_lock.release()
                        ##################################
                        f(*args)
                        ##################################
                        ##        critical area        ###
                        self.job_lock.acquire()
                        for i in range(len(self.priorities)):
                                self.priorities[i]+=1
                        #self.thread_table[my_num] = False		
                        self.job_lock.release()                        
                        ##################################
                        #return


        def __init__(self,n,complexity):
                self.pool = [0] * n
                self.thread_table = [False] * n
                self.count = n
                self.complexity = complexity		

                for i in range(n):
	                self.pool[i] = threading.Thread(target=self.search_job, args=[i])
		
	
        def job(self,func,args,priority,complexity = 1):
                ##################################
                ## priorities are from 0 to 256 ##
                _priority = 255
                if((priority < 256) & (priority > -1)):
	                _priority = 255 - priority 
                ##################################

                ##################################
                ##        critical area        ###
                self.job_lock.acquire()
                self.priorities.append(_priority)
                self.queue.append((func,args))
                self.complexities.append(complexity)		
                self.job_lock.release()
                ##################################

        def start(self):
                for thr in self.pool :
                        thr.start()

        def stop(self):
                flag = True
                while  (flag):
                        self.job_lock.acquire()
                        #print self.thread_table
                        flag = reduce(lambda x, y : x|y, self.thread_table)
                        self.job_lock.release()
                self.stop_flag = True 

        def join(self):
                for thr in self.pool :
                        thr.join()
	
	

#lock = threading.Lock()

#pool = threadPool(5,100)

#def s(num):
#        lock.acquire()
#        a = 0;
#        print num
#        lock.release()
#        for i in range(10000):
#                a+=1                

#for i in range(1000):
#        pool.job(s,[i],random.randint(0,255))

#pool.start()
#pool.stop()




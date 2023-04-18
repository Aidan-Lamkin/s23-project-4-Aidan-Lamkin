#include "algorithms/mlfq/mlfq_algorithm.hpp"

#include <cassert>
#include <stdexcept>
#include "math.h"
#include <string>
#include <iostream>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the MLFQ algorithm.
*/

MFLQScheduler::MFLQScheduler(int slice) {
    if (slice != -1) {
        throw("MLFQ does NOT take a customizable time slice");
    }
}

// This is print statement -> Selected from queue Z (priority = P, runtime = R). Will run for at most Y ticks. 


std::shared_ptr<SchedulingDecision> MFLQScheduler::get_next_thread() {
        if(this->size() == 0){
            // Return null thread scheduling decision
            auto decision = std::make_shared<SchedulingDecision>();
            decision->thread = nullptr;
            decision->explanation = "No threads available for scheduling.";
            return decision;
        }
        else{
            int queueIndex = 0;
            for(queueIndex = 0; queueIndex < 10; queueIndex++){
                if(this->qArray[queueIndex].size() > 0){
                    break;
                }
            }
            std::shared_ptr<SchedulingDecision> decision = std::make_shared<SchedulingDecision>();
            decision->thread = this->qArray[queueIndex].top();
            this->qArray[queueIndex].pop();
            decision->time_slice = (int)pow(2, queueIndex);
            this->time_slice = (int)pow(2, queueIndex);
            decision->explanation = "Selected from queue " + std::to_string(queueIndex) + " (priority = " + PROCESS_PRIORITY_MAP[decision->thread->priority] + ", runtime = " + std::to_string((int)pow(2, queueIndex) - decision->thread->remainingTime) + "). Will run for at most " + std::to_string(this->time_slice) + " ticks.";
            decision->thread->remainingTime -= decision->thread->get_next_burst(BurstType::CPU)->length;
            return decision;
        }
        return nullptr;
}

void MFLQScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    if(thread->remainingTime <= 0){
        if(thread->currentQueue < 9){
            thread->currentQueue += 1;
        }
        thread->remainingTime = pow(2, thread->currentQueue);
    }
    this->qArray[thread->currentQueue].push(thread->priority, thread);
}

size_t MFLQScheduler::size() const {
        int size = 0;
        for(int i = 0; i < 10; i++){
            size += qArray[i].size();
        }
        return size;
}

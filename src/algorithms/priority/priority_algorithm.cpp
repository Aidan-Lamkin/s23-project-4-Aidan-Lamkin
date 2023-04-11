#include "algorithms/priority/priority_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"


/*
    Here is where you should define the logic for the priority algorithm.
*/

PRIORITYScheduler::PRIORITYScheduler(int slice) {
    if (slice != -1) {
        throw("PRIORITY must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> PRIORITYScheduler::get_next_thread() {
    if(this->q.size() != 0){
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = this->q.top();
        int priority = decision->thread->priority;
        std::string explanation = "[S: " + std::to_string(counts[0]) + " I: " + std::to_string(counts[1]) + " N: " + std::to_string(counts[2]) + " B: " + std::to_string(counts[3]) + "] -> ";
        counts[priority] -= 1;
        explanation += "[S: " + std::to_string(counts[0]) + " I: " + std::to_string(counts[1]) + " N: " + std::to_string(counts[2]) + " B: " + std::to_string(counts[3]) + "]. Will run to completion of burst.";
        decision->explanation = explanation;
        this->q.pop();
        return decision;
    }
    else{
        // Return null thread scheduling decision
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = nullptr;
        decision->explanation = "No threads available for scheduling.";
        return decision;
    }
}

void PRIORITYScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    this->q.push(thread->priority,thread);
    counts[thread->priority] += 1;
}

size_t PRIORITYScheduler::size() const {
    return this->q.size();
}

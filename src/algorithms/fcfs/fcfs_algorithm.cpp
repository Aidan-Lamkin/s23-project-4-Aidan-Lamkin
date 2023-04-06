#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include "utilities/fmt/format.h"

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
    //Fields (Thread, explanation (See read me), time slice (not important for FCFS))
    if(this->q.size() != 0){
        auto decision = std::make_shared<SchedulingDecision>();
        decision->thread = this->q.front();
        decision->explanation = "Selected from " + std::to_string(this->q.size()) + " threads. Will run to completion of burst.";
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

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    this->q.push(thread);
}

size_t FCFSScheduler::size() const {
    return this->q.size();
}

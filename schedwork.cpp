#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shifts_used,
    size_t position,
    size_t day
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t num_of_days = avail.size();
    size_t num_of_workers = avail[0].size();

    sched.assign(num_of_days,std::vector<Worker_T>(dailyNeed,INVALID_ID));
    std::vector<size_t> shifts_used(num_of_workers,0);

    bool answer = schedule_helper(avail,dailyNeed,maxShifts,sched,shifts_used,0,0);

    return answer; 
}


bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shifts_used,
    size_t position,
    size_t day
)
{


  size_t num_of_days = avail.size();
  size_t num_of_workers = avail[0].size();

  if(day == num_of_days)
  {
    return true;
  }

  if(position == dailyNeed)
  {
    return schedule_helper(avail,dailyNeed,maxShifts,sched,shifts_used,0,day+1);
  }
for(size_t w = 0;w<num_of_workers;++w)
  {
    if(!avail[day][w])
    {
      continue;
    }

    if(shifts_used[w] >= maxShifts)
    {
      continue;
    }

    bool previously_used = false; 

    for(size_t i = 0;i<position;++i)
    {
      if(sched[day][i] == w)
      {
      previously_used = true; 
      break;
      } 
    }

    if(previously_used)
      {
        continue;
      }
 

    sched[day][position] = w; 
    shifts_used[w]++;

    if(schedule_helper(avail,dailyNeed,maxShifts,sched,shifts_used,position+1,day))
    {
      return true;
    }

    sched[day][position] = INVALID_ID;
    shifts_used[w]--;
    }
  return false; 
}


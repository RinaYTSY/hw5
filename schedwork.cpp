#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool solveRecursive( const AvailabilityMatrix avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts, int day, int slot);


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
	for (int i = 0; i < avail.size(); i++){
		vector<Worker_T> row(dailyNeed, -1);
		sched.push_back(row);
	}
	AvailabilityMatrix aCopy=avail;


	
	vector<size_t> shifts( avail[0].size(), 0);
	return solveRecursive( aCopy, dailyNeed, maxShifts, sched, shifts, 0, 0);	// add int day = 0 and int slot = 0
}

bool solveRecursive( AvailabilityMatrix avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, vector<size_t>& shifts, int day, int slot)
{
	
  if( dailyNeed == 0) return true;
	if( avail.size() == 0) return false;

	const size_t availworkers = avail[0].size();

	
	if(day==sched.size()){
		return true;
	}


	for( size_t i = 0; i<availworkers; i++ )
	{
		if( avail[day][i] && shifts[i] < maxShifts )
		{
			sched[day][slot] = i;
			shifts[i]++;
			avail[day][i]=0;

			
			if(slot==dailyNeed-1){
        if(solveRecursive( avail, dailyNeed, maxShifts, sched, shifts, day+1,0 ) ){
          return true;
        }
			shifts[i]--;
      sched[day][slot] = -1;
			avail[day][i]=1;
      }
      else{
        if(solveRecursive( avail, dailyNeed, maxShifts, sched, shifts, day,slot+1 )){
          return true;
        }
				shifts[i]--;
     	  sched[day][slot] = -1;
				avail[day][i]=1;
			}
			
		}
	}

	return false;
}



#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Job {
public:
    string job_id;
    int deadline;
    int profit;

    Job(string id, int dl, int pf) {
        job_id = id;
        deadline = dl;
        profit = pf;
    }
};

// Function to schedule jobs and return maximum profit
pair<vector<string>, int> schedule_jobs(vector<Job>& jobs) {
    // Step 1: Sort jobs by descending order of profit
    sort(jobs.begin(), jobs.end(), [](Job& a, Job& b) {
        return a.profit > b.profit;
    });

    // Step 2: Find the maximum deadline to determine the number of time slots
    int max_deadline = 0;
    for (const auto& job : jobs) {
        max_deadline = max(max_deadline, job.deadline);
    }

    // Step 3: Initialize result (track which jobs are done) and time slots
    vector<string> result(max_deadline, "");
    vector<bool> slot_filled(max_deadline, false);
    int total_profit = 0;

    // Step 4: Assign jobs to the latest available time slot before their deadline
    for (const auto& job : jobs) {
        for (int slot = min(max_deadline, job.deadline) - 1; slot >= 0; --slot) {
            if (!slot_filled[slot]) {
                result[slot] = job.job_id;
                slot_filled[slot] = true;
                total_profit += job.profit;
                break;
            }
        }
    }

    // Collect scheduled jobs
    vector<string> scheduled_jobs;
    for (const auto& job_id : result) {
        if (!job_id.empty()) {
            scheduled_jobs.push_back(job_id);
        }
    }

    // Step 5: Return scheduled jobs and total profit
    return {scheduled_jobs, total_profit};
}

int main() {
    // Input jobs with {job_id, deadline, profit}
    vector<Job> jobs = {
        Job("Job1", 2, 100),
        Job("Job2", 1, 19),
        Job("Job3", 2, 27),
        Job("Job4", 1, 25),
        Job("Job5", 3, 15)
    };

    // Schedule jobs and get maximum profit
    pair<vector<string>, int> result = schedule_jobs(jobs);

    // Output the scheduled jobs and maximum profit
    cout << "Scheduled Jobs: ";
    for (const string& job_id : result.first) {
        cout << job_id << " ";
    }
    cout << "\nMaximum Profit: " << result.second << endl;

    return 0;
}

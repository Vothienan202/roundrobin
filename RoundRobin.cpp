
#include<iostream>
#include <algorithm> 
#include <queue> 
#include<iomanip>
#include<climits>
using namespace std;

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
}ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b)
{
    int x = a.at;
    int y = b.at;
    return x < y;
}

int main()
{

    int n, index;
    queue<int> q;
    bool visited[100] = { false }, is_first_process = true;
    int current_time = 0;
    int completed = 0, tq;
    cout << "Nhap tong so tien trinh: ";
    cin >> n;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap Arrival time cua process " << i <<": ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap Burst time cua process " << i << ": ";
        cin >> ps[i].bt;
        ps[i].bt_remaining = ps[i].bt;
    }

    cout << "\nNhap Quantume time: ";
    cin >> tq;

   
    sort(ps, ps + n, comparatorAT);

    q.push(0);
    visited[0] = true;

    while (completed != n)
    {
        index = q.front();
        q.pop();

        if (ps[index].bt_remaining == ps[index].bt)
        {
            ps[index].start_time = max(current_time, ps[index].at);
            total_idle_time += (is_first_process == true) ? 0 : ps[index].start_time - current_time;
            current_time = ps[index].start_time;
            is_first_process = false;

        }

        if (ps[index].bt_remaining - tq > 0)
        {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        }
        else
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            sum_rt += ps[index].rt;
        }


        
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        
        if (ps[index].bt_remaining > 0)
            q.push(index);

       
        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    //Output
    // chu thich: 
    // at = arival time
    // bt = burst time
    // ct = current time
    // tat = turn around time
    // wt  = waiting time
    // rt = response time
    cout << "\nProcess No.\tAT\tBurst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].start_time << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;


class Interval {
    public:
  int start, end;
  Interval(int start, int end) {
      this->start = start;
      this->end = end;
  }
};

/**
 * Definition of Interval:
 * classs Interval {
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    /**
     * @param intervals: Sorted interval list.
     * @param newInterval: new interval.
     * @return: A new interval list.
     */
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        // write your code here
        vector<Interval> result;
        int i = 0;


        while (i < intervals.size() && intervals[i].start < newInterval.start)
        {
            result.push_back(intervals[i++]);
        }

        if(result.size() > 0 && result.back().end >= newInterval.start)
        {
            result.back().end = max(result.back().end ,newInterval.end);
        }
        else
        {
            result.push_back(newInterval);
        }
        while(intervals.size() > i && result.back().end >= intervals[i].start)
        {
            result.back().end = max(intervals[i].end ,result.back().end);
            i++;
        }
        while(i < intervals.size())
        {
            result.push_back(intervals[i++]);
        }
        return result;

    }
};

int main()
{
    vector<Interval> a;

    Interval b(6,7);
    Interval c(1,5);
    a.push_back(c);

    Interval d(7,8);
    a.push_back(d);

    Interval e(10,13);
    a.push_back(e);

    Solution s;
    a = s.insert(a, b);

    return 0;
}

#include<bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};
int main()
{
   Point bottom_left_1, top_right_1;
   Point bottom_left_2, top_right_2;

   cin>>bottom_left_1.x>>bottom_left_1.y;
   cin>>top_right_1.x>>top_right_1.y;

   cin>>bottom_left_2.x>>bottom_left_2.y;
   cin>>top_right_2.x>>top_right_2.y;

   int x_distance = min(top_right_1.x, top_right_2.x) - max(bottom_left_1.x, bottom_left_2.x);
   int y_distance = min(top_right_1.y, top_right_2.y) - max(bottom_left_1.y, bottom_left_2.y);


   if(x_distance <=0 || y_distance <= 0)
   {
      cout<<"No overlap";
   }

   int overlap_area = x_distance*y_distance;
   cout<<"overlap area: "<<overlap_area<<endl;
 
  return 0;
}

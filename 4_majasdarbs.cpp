#include <iostream>
#include <cmath>

using namespace std;

class Point {
    private:
    float x_coordinate;
    float y_coordinate;

    public:
    Point(int x, int y): x_coordinate(x), y_coordinate(y) {} 
    Point(int a): Point(a, a) {}
    pair<float, float> returnCoordinate(){
        return make_pair(x_coordinate,y_coordinate);
    }
};

class Line { 
    private:
    Point startPoint = Point(1);
    Point endPoint = Point(1);
    
    public:
    Line(Point stPnt, Point endPnt): startPoint(stPnt), endPoint(endPnt) {}
    void display() {
       pair<float, float> startp = startPoint.returnCoordinate();
       pair<float, float> endp = endPoint.returnCoordinate();
       cout << "Starts  (x,y):" << startp.first << " " << startp.second << endl;
       cout << "Beigas  (x,y):" << endp.first << " " << endp.second << endl;
    }
    float distance() {
       pair<float, float> startp = startPoint.returnCoordinate();
       pair<float, float> endp = endPoint.returnCoordinate();
       float distance_res = sqrt(pow((startp.first - endp.first),2) + pow((startp.second - endp.second),2));
       return distance_res;
    }
};
int main() { 
    Point startPnt(1,5);
    Point endPnt(4);
    Line line(startPnt, endPnt);
    line.display();
    cout << "Linijas distance: " << line.distance() << endl;
    return 0;
}
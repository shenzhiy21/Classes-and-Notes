#include <iostream>
using namespace std;

int n, m;
struct Point{
    int x;
    int y;
    bool cmp(const Point& target){
        if((long long)(x) * target.y + (long long)(y) * target.x < (long long)(x) * y) return true;
        else return false;
    } //返回true代表target在当前点的左侧
}points[200002];

int binSearch(const Point& point, int left = 0, int right = n);

int main(){
    ios::sync_with_stdio(false);
	cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> points[i].x >> points[i].y;
    }
    Point point;
    for(int j = 0; j < m; j++){
        cin >> point.x >> point.y;
        cout << binSearch(point) << '\n';
    }
    return 0;
}

int binSearch(const Point& point, int left, int right){
    while(left < right){
        int mid = (left + right) >> 1;
        points[mid].cmp(point) ? right = mid : left = mid + 1;
    }
    return left;
}
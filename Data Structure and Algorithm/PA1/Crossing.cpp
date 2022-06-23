#include <iostream>
using namespace std;

typedef long long lld;

struct Pair{
    int index;
    int value;
    Pair(int _value = 0, int _index = 0){
        value = _value;
        index = _index;
    }
};

//是否在第一象限相交
bool cmp_1(int i, int j, Pair* arr){
    return arr[j].value < arr[i].value;
}
//是否在第四象限相交
bool cmp_2(int i, int j, Pair* arr){
    return (lld)arr[i].value * arr[j].index > (lld)arr[j].value * arr[i].index;
}
//是否平行
bool isParallel(int i, int j, Pair* arr){
    return (lld)arr[i].value * arr[j].index == (lld)arr[j].value * arr[i].index;
}

//模拟归并排序，计算逆序对数量
template<class Compare>
lld mergesort(int lo, int hi, Compare cmp, Pair* arr){
    if(hi - lo < 2) return 0;
    int mi = (lo + hi) >> 1;
    lld a = mergesort(lo, mi, cmp, arr);
    lld b = mergesort(mi, hi, cmp, arr);
    lld ans = 0;
    int i = lo; int j = mi;
    Pair* temp = new Pair[hi - lo + 1];
    int cnt = 0;
    while((i < mi) && (j < hi)){
        if(cmp(i, j, arr)){
            ans += mi - i;
            temp[cnt++] = arr[j++];
        }
        else{
            temp[cnt++] = arr[i++];
        }
    }
    while(i < mi) temp[cnt++] = arr[i++];
    while(j < hi) temp[cnt++] = arr[j++];
    for(int k = lo; k < hi; k++)
        arr[k] = temp[k - lo];
    delete [] temp;
    return ans + a + b;
}

//计算两两平行的直线对数
lld parallel(int length, Pair* arr){
    lld ans = 0;    //返回值
    int i = 0;  //下标
    int cnt = 0;    //统计个数
    while(++i < length){
        if(isParallel(i, i + 1, arr)){
            cnt++;
        }
        else{
            ans += (lld)cnt * (cnt + 1) / 2;
            cnt = 0;
        }
    }
    ans += (lld)cnt * (cnt + 1) / 2;
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    Pair* arr1 = new Pair[n + 1];
    Pair* arr2 = new Pair[n + 1];
    int value;
    for(int i = 1; i <= n; i++){
        cin >> value;
        arr1[i] = Pair(value, i);
        arr2[i] = arr1[i];
    }
    lld ans1 = mergesort(1, n + 1, cmp_1, arr1);
    lld ans2 = mergesort(1, n + 1, cmp_2, arr2);
    lld ans4 = (lld)n * (n - 1) / 2 - ans1 - ans2 - parallel(n, arr2);
    cout << ans1 << " " << ans2 << " " << ans4 << '\n';
    delete [] arr1;
    delete [] arr2;
    return 0;
}
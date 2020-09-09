#include<bits/stdc++.h>

using namespace std;

struct trial{
    int a = 3;
    trial& method();
};

int main(int argc, char const *argv[])
{
    const pair<int,int>& p = {45,3};
    cout<<trial().method().a;
    return 0;
}

trial& trial::method(){
    auto l  = [&](){
        this->a = 56;
    };
    l();
    return *this;
}
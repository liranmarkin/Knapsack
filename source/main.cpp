#include <bits/stdc++.h>
#include "SumApx.h"
#include "Knapsack.h"
using namespace std;

int main(int argc, char *argv[])
{
    SumApproximation F = make_sum_approximation(3);
    SumApproximation G = make_sum_approximation(5);
    for (uint i = 0; i <= 10; i++) cout << ":" << F.query(i) << ", "; cout << endl;
    for (uint i = 0; i <= 10; i++) cout << ":" << G.query(i) << ", "; cout << endl;
    for (uint i = 0; i <= 10; i++) cout << ":" << (F + G).query(i) << ", "; cout << endl;
    
    SumApproximation F_conv_G = (F * G);
    for (uint i = 0; i <= 10; i++) cout << ":" << F_conv_G.query(i) << ", "; cout << endl;
    
    SumApproximation H = (F_conv_G * F_conv_G);
    for (uint i = 0; i <= 20; i++) cout << ":" << H.query(i) << ", "; cout << endl;

    H = H.sprasify(0.5);
    for (uint i = 0; i <= 20; i++) cout << ":" << H.query(i) << ", "; cout << endl;
    cout << endl;

    vector<uint> W = {2, 3, 4, 7, 11};
    SumApproximation result = SimpleKnapsack(W, 5.0);
    for (uint c = 0; c <= 50; c++) cout << "C = " << c << " -> " <<  result.query(c) << endl;

    return 0;
}
#include "SumApx.h"
#include "Knapsack.h"

SumApproximation SimpleKnapsack(vector<uint> W, double epsilon)
{
    double delta = pow((1 + epsilon), 1.0 / W.size());
    SumApproximation result = make_empty_sum_approximation();
    for (auto w : W) 
        result = (result + result.shift(w)).sprasify(delta);
    return result;
}
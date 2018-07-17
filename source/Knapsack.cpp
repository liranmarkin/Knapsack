#include "SumApx.h"
#include "Knapsack.h"

SumApproximation simple_knapsack(vector<uint> W, double epsilon)
{
    const double delta = pow((1 + epsilon), 1.0 / W.size());
    SumApproximation result = make_empty_sum_approximation();
    for (auto w : W) 
        result = (result + result.shift(w)).sprasify(delta);
    return result;
}

SumApproximation good_knapsack_recursive(vector<uint> W, double epsilon, uint threshold, double delta)
{
    if (W.size() <= threshold) return simple_knapsack(W, epsilon);
    
    cerr << "delta: " << delta << endl;
    const vector<uint> S(W.begin(), W.begin() + W.size() / 2), T(W.begin() + W.size() / 2, W.end());
    cerr << "S: {"; for(auto s : S) cerr << s << ", "; cerr << "}" << endl;
    cerr << "T: {"; for(auto t : T) cerr << t << ", "; cerr << "}" << endl;
    const double next_epsilon = sqrt((1.0 + epsilon) / delta) - 1.0;
    SumApproximation Ks = good_knapsack_recursive(S, next_epsilon, threshold, delta / sqrt(2.0)),
                     Kt = good_knapsack_recursive(T, next_epsilon, threshold, delta / sqrt(2.0));
    return (Ks * Kt).sprasify(delta);
}

SumApproximation good_knapsack(vector<uint> W, double epsilon)
{
    const double c = sqrt(2.0) / (sqrt(2.0) - 1.0);
    const double delta = 1 + (pow(epsilon, 0.75) / (2.0 * c * pow(W.size(), 0.25)));
    return good_knapsack_recursive(W, epsilon, sqrt(W.size() / epsilon), delta);
}
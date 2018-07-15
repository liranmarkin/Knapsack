#pragma once
#include "common.h"

class SumApproximation {   
public:
    using EntryType = uint;
    using ValueType = ull;
    using FuncType = map<EntryType, ValueType>;

    SumApproximation() = default;
    SumApproximation(FuncType && func);
    SumApproximation(const SumApproximation & other) = default;

    SumApproximation & sprasify(double delta);
    SumApproximation operator+(const SumApproximation & other);
    SumApproximation shift(EntryType offset);
    static SumApproximation convolution(const SumApproximation & first, const SumApproximation & second);
    SumApproximation operator*(const SumApproximation & other);
    ValueType query(EntryType position);

private:
    FuncType func;
};

SumApproximation make_empty_sum_approximation();
SumApproximation make_sum_approximation(SumApproximation::EntryType weight);
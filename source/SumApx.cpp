#include "SumApx.h"

SumApproximation::SumApproximation(FuncType && func)
    :func(func)
{
}

SumApproximation & SumApproximation::sprasify(double delta)
{
    FuncType newfunc;
    ValueType threshold = 1, sum = 0;
    EntryType bucket_position = 0;

    for(auto const& [position, value] : func) {
        sum += value;
        if (sum >= threshold) {
            bucket_position = position;
            threshold = max(threshold + 1LL, ValueType(delta * double(threshold)));
        }
        newfunc[bucket_position] += value;
    }
    func = newfunc;
    return *this;
}

SumApproximation SumApproximation::operator+(const SumApproximation & other)
{
    SumApproximation result = *this;
    for(auto const& [position, value] : other.func)
        result.func[position] += value;
    return result;
}

SumApproximation SumApproximation::shift(EntryType offset)
{
    FuncType newfunc;
    for(auto const& [position, value] : func)
        newfunc[position + offset] = value;
    return SumApproximation(std::move(newfunc));
}

SumApproximation SumApproximation::convolution(const SumApproximation & first, const SumApproximation & second)
{
    FuncType newfunc;
    for(auto const& [position1, value1] : first.func)
    for(auto const& [position2, value2] : second.func)
        newfunc[position1 + position2] += value1 * value2;
    return SumApproximation(std::move(newfunc));
}

SumApproximation SumApproximation::operator*(const SumApproximation & other)
{
    return convolution(*this, other);
}

SumApproximation::ValueType SumApproximation::query(EntryType position)
{
    ValueType result = 0;
    for(auto const& [entry, value] : func) {
        if (entry > position)
            break;
        result += value;
    }
    return result;
}

// TODO: give large weight is identical to empty set
SumApproximation make_empty_sum_approximation()
{
    SumApproximation::FuncType f;
    f[0] += 1; 
    return SumApproximation(std::move(f));
}

SumApproximation make_sum_approximation(SumApproximation::EntryType weight)
{
    SumApproximation::FuncType f;
    f[0] += 1;
    f[weight] += 1;
    return SumApproximation(std::move(f));
}
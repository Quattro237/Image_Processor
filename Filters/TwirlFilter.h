#pragma once

#include "Filter.h"

class TwirlFilter : public Filter {
public:
    explicit TwirlFilter(const double angle);

    void ApplyFilter(Image& image) const override;

    static const double MAX_ANGLE;

private:
    const double pi_angle_ = 0;
};

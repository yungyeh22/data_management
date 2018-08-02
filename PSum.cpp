#include "PSum.h"

namespace Plugin{

PSum::PSum() : PObject(0,1) {
    setName("Sum of all elements");
}

void PSum::execute(std::shared_ptr<Vec2d> udata) {
    auto data = udata->data;
    double num = 0;
    for (const auto &row : data) {
        for (const auto &col : row) {
            num += col;
        }
    }
    data.resize(1);
    data[0].resize(1);
    data[0][0] = num;
    udata->data = std::move(data);
}

}

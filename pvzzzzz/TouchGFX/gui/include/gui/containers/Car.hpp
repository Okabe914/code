#ifndef CAR_HPP
#define CAR_HPP

#include <gui_generated/containers/CarBase.hpp>

class Car : public CarBase
{
public:
    Car();
    virtual ~Car() {}

    virtual void initialize();
protected:
};

#endif // CAR_HPP

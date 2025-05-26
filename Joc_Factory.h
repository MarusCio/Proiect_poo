//
// Created by cioba on 5/26/2025.
//

#ifndef JOC_FACTORY_H
#define JOC_FACTORY_H
#include <memory>

#include "Joc.h"


class Joc_Factory {
public:
    virtual std::unique_ptr<Joc> Creaza_joc()=0;
    virtual ~Joc_Factory()= default;
};



#endif //JOC_FACTORY_H

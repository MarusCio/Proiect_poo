//
// Created by cioba on 7/1/2025.
//

#ifndef FUNCTII_TEMPLATE_H
#define FUNCTII_TEMPLATE_H

#include <iostream>
#include <vector>

template<typename T>
void Afis_Mana(const std::vector<T>& mana) {
    for (const auto& item : mana)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<typename T>
T Max(const T&x, const T&y) {
    if (x > y) return x;
    return y;
}

#endif //FUNCTII_TEMPLATE_H

/*
** EPITECH PROJECT, 2024
** Orca
** File description:
** Extern.hpp
*/

#ifndef ORCA_EXTERN_HPP
    #define ORCA_EXTERN_HPP
    #include <memory>
    #include "Orca.hpp"

extern "C" {
    std::unique_ptr<Orca> entryPoint() {
        return std::make_unique<Orca>();
    }
}

#endif //ORCA_EXTERN_HPP

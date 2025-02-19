/* metamorphosis
 * Copyright (C) 2024 Killian Valverde.
 *
 * This file is part of metamorphosis.
 *
 * metamorphosis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * metamorphosis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with metamorphosis. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        metamorphosis/exception.hpp
 * @brief       exception class header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#ifndef METAMORPHOSIS_EXCEPTION_HPP
#define METAMORPHOSIS_EXCEPTION_HPP

#include <exception>
#include <string>


namespace metamorphosis {


/**
 * @brief       Base interface for standard metamorphosis exceptions. All objects thrown 
 *              by components metamorphosis are derived from this class. Therefore, all 
 *              metamorphosis exceptions can be caught by catching this type by reference.
 */
class exception_base : public std::exception
{
public:
    /**
     * @brief       Default constructor.
     */
    exception_base() = default;
    
    /**
     * @brief       Copy constructor.
     * @param       rhs : Object to copy.
     */
    exception_base(const exception_base& rhs) = default;
    
    /**
     * @brief       Move constructor.
     * @param       rhs : Object to move.
     */
    exception_base(exception_base&& rhs) noexcept = default;
    
    /**
     * @brief       Destructor.
     */
    ~exception_base() override = default;
    
    /**
     * @brief       Copy assignment operator.
     * @param       rhs : Object to copy.
     * @return      The object who call the method.
     */
    exception_base& operator =(const exception_base& rhs) = default;
    
    /**
     * @brief       Move assignment operator.
     * @param       rhs : Object to move.
     * @return      The object who call the method.
     */
    exception_base& operator =(exception_base&& rhs) noexcept = default;
    
    /**
     * @brief       Get the message of the exception.
     * @return      The exception message.
     */
    [[nodiscard]] const char* what() const noexcept override = 0;
};


/**
 * @brief       Base class that the metamorphosis classes will use to throw exceptions.
 */
class exception : public exception_base
{
public:
    /**
     * @brief       Get the message of the exception.
     * @return      The exception message.
     */
    [[nodiscard]] char const* what() const noexcept override
    {
        return "metamorphosis exception";
    }
};


}


#endif

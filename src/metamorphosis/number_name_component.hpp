/* metamorphosis
 * Copyright (C) 2018-2024 Killian Valverde.
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
 * along with speed. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        metamorphosis/number_name_component.hpp
 * @brief       number_name_component header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#ifndef METAMORPHOSIS_NUMBER_NAME_COMPONENT_HPP
#define METAMORPHOSIS_NUMBER_NAME_COMPONENT_HPP

#include <speed/speed.hpp>

#include "name_component.hpp"


namespace metamorphosis {


class number_name_component : public name_component
{
public:
    using integral_type = std::uint64_t;
    
    number_name_component(
            integral_type start_numbr,
            integral_type digit_cont,
            half_priority_type priorty
    )
            : current_str_()
            , start_numbr_(start_numbr)
            , current_numbr_(start_numbr)
            , digit_cont_(digit_cont)
            , priorty_(priorty)
    {
    }
    
    [[nodiscard]] inline priority_type get_absolute_priority() const noexcept override
    {
        return (static_cast<priority_type>(priorty_) << 32) + 1;
    }
    
    [[nodiscard]] inline const string_type& get_next_string() noexcept override
    {
        current_str_.clear();
        
        for (integral_type current_digit_cont = spd::scals::count_digits(current_numbr_);
             current_digit_cont < digit_cont_;
             ++current_digit_cont)
        {
            current_str_ += '0';
        }
        
        return current_str_ += std::to_string(current_numbr_++);
    }
    
    inline void set_digit_count(integral_type digit_cont) noexcept
    {
        if (digit_cont_ == 0)
        {
            digit_cont_ = digit_cont;
        }
    }
    
private:
    string_type current_str_;
    
    integral_type start_numbr_;
    
    integral_type current_numbr_;
    
    integral_type digit_cont_;
    
    half_priority_type priorty_;
};


}


#endif

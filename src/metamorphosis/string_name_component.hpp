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
 * @file        metamorphosis/string_name_component.hpp
 * @brief       string_name_component header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#ifndef METAMORPHOSIS_STRING_NAME_COMPONENT_HPP
#define METAMORPHOSIS_STRING_NAME_COMPONENT_HPP

#include "name_component.hpp"


namespace metamorphosis {


class string_name_component : public name_component
{
public:
    template<typename TpString_>
    string_name_component(TpString_&& str, half_priority_type priorty)
            : str_(std::forward<TpString_>(str))
            , priorty_(priorty)
    {
    }
    
    [[nodiscard]] inline priority_type get_absolute_priority() const noexcept override
    {
        return (static_cast<priority_type>(priorty_) << 32);
    }
    
    [[nodiscard]] inline const string_type& get_next_string() noexcept override
    {
        return str_;
    }
    
private:
    string_type str_;
    
    half_priority_type priorty_;
};


}


#endif

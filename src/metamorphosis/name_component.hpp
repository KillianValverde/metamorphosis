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
 * @file        metamorphosis/name_component.hpp
 * @brief       name_component header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#ifndef METAMORPHOSIS_NAME_COMPONENT_HPP
#define METAMORPHOSIS_NAME_COMPONENT_HPP

#include <string>


namespace metamorphosis {


class name_component
{
public:
    using string_type = std::string;
    
    using priority_type = std::uint64_t;
    
    using half_priority_type = std::uint32_t;
    
    name_component() = default;
    
    virtual ~name_component() = default;
    
    [[nodiscard]] virtual priority_type get_absolute_priority() const noexcept = 0;
    
    [[nodiscard]] virtual const string_type& get_next_string() noexcept = 0;
};


}


#endif

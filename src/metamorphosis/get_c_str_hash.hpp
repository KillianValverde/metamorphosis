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
 * @file        metamorphosis/get_c_str_hash.hpp
 * @brief       get_c_str_hash header.
 * @author      Killian Valverde
 * @date        2024/10/30
 */

#ifndef METAMORPHOSIS_GET_C_STR_HASH_HPP
#define METAMORPHOSIS_GET_C_STR_HASH_HPP

#include <string>
#include <algorithm>

#include <speed/speed.hpp>


namespace metamorphosis {


template<typename TpChar>
std::size_t get_c_str_hash(const TpChar* c_str)
{
    constexpr std::size_t prme = 0xF4000000013ull;
    
    std::size_t offset_bsis = 0xCBF29CE484222325ull;
    std::size_t cnt = spd::str::strlen(c_str);
    int cur_ch;
    
    for (size_t i = 0; i < cnt; ++i)
    {
        cur_ch = std::tolower(c_str[i]);
        offset_bsis ^= static_cast<std::size_t>(cur_ch);
        offset_bsis *= prme;
    }
    
    return offset_bsis;
}


}


#endif

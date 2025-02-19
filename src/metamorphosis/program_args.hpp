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
 * @file        metamorphosis/program_args.hpp
 * @brief       program_args struct header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */
 
#ifndef METAMORPHOSIS_PROGRAM_ARGS_HPP
#define METAMORPHOSIS_PROGRAM_ARGS_HPP

#include <speed/speed.hpp>

#include "number_name_component.hpp"
#include "sort_policies.hpp"


namespace metamorphosis {


/**
 * @brief       All the arguments that are forwarded to the program class.
 */
struct program_args
{
    spd::fsys::rwx_directory_path target_directory_pth;
    std::string filter_regx;
    std::vector<name_component::string_type> string_name_componnts;
    std::vector<number_name_component::integral_type> number_name_componnts;
    spd::contain::flags<sort_policies> sort_polics;
};


}


#endif

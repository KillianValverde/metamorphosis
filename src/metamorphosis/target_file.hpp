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
 * @file        metamorphosis/target_file.hpp
 * @brief       target_file header.
 * @author      Killian Valverde
 * @date        2024/10/24
 */

#ifndef METAMORPHOSIS_TARGET_FILE_HPP
#define METAMORPHOSIS_TARGET_FILE_HPP

#include <filesystem>
#include <iostream>

#include <speed/speed.hpp>

#include "forward_declarations.hpp"
#include "program.hpp"


namespace metamorphosis {


class target_file
{
public:
    template<typename TpPath_>
    target_file(TpPath_&& file_pth, program* progrm)
            : original_file_pth_(std::forward<TpPath_>(file_pth))
            , new_file_pth_()
            , progrm_(progrm)
            , visitd_(false)
            , dne_(false)
            , rename_succss_(false)
    {
    }
    
    virtual ~target_file() = default;
    
    bool rename();
    
    [[nodiscard]] inline const std::filesystem::path& get_original_file_path() const noexcept
    {
        return original_file_pth_;
    }
    
    template<typename TpString_>
    void set_new_file_name(const TpString_& new_file_nme)
    {
        new_file_pth_ = original_file_pth_.parent_path() / new_file_nme;
        new_file_pth_ += original_file_pth_.extension();
    }
    
    inline void print_ok_rename(const std::filesystem::path& current_new_file_pth)
    {
        std::cout << spd::ios::set_white_text
                  << "\""
                  << spd::cast::type_cast<std::string>(original_file_pth_.c_str())
                  << "\" --> "
                  << spd::ios::set_yellow_text
                  << "\""
                  << spd::cast::type_cast<std::string>(current_new_file_pth.c_str())
                  << "\""
                  << spd::ios::set_light_green_text
                  << " [ok]"
                  << spd::ios::set_default_text
                  << spd::ios::newl;
    }
    
    inline void print_fail_rename()
    {
        std::cout << spd::ios::set_white_text
                  << "\""
                  << spd::cast::type_cast<std::string>(original_file_pth_.c_str())
                  << "\" --> "
                  << spd::ios::set_yellow_text
                  << "\""
                  << spd::cast::type_cast<std::string>(new_file_pth_.c_str())
                  << "\""
                  << spd::ios::set_light_red_text
                  << " [fail]"
                  << spd::ios::set_default_text
                  << spd::ios::newl;
    }
    
private:
    std::filesystem::path original_file_pth_;
    
    std::filesystem::path new_file_pth_;
    
    program* progrm_;
    
    bool visitd_;
    
    bool dne_;
    
    bool rename_succss_;
};


}


#endif

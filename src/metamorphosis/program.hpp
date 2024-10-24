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
 * @file        metamorphosis/program.hpp
 * @brief       program class header.
 * @author      Killian Valverde
 * @date        2024/10/23
 */
 
#ifndef METAMORPHOSIS_PROGRAM_HPP
#define METAMORPHOSIS_PROGRAM_HPP

#include <speed/speed.hpp>

#include "forward_declarations.hpp"
#include "exception.hpp"
#include "program_args.hpp"
#include "target_file.hpp"


/**
 * @brief       Contians all metamorphosis resources.
 */
namespace metamorphosis {


class program
{
public:
    using string_type = std::string;
    
    /**
     * @brief       Constructor with parameters.
     * @param       prog_args : The program arguments.
     */
    explicit program(program_args&& prog_args);
    
    /**
     * @brief       Execute the program.
     * @return      The value that represents if the program succeed.
     */
    int execute();

private:
    bool get_target_files();
    
    void sort_target_files();
    
    void set_name_components();
    
    void set_new_target_files_names();
    
    string_type get_next_target_file_name();
    
    bool rename_target_files();
    
    std::shared_ptr<target_file> get_target_file(const std::filesystem::path& target_file_pth);

private:
    /** The program arguments. */
    program_args prog_args_;
    
    std::multimap<name_component::priority_type, std::unique_ptr<name_component>> name_componnts_;
    
    std::vector<std::shared_ptr<target_file>> target_fles_;
    
    std::unordered_map<std::size_t, std::shared_ptr<target_file>> target_fles_map_;
    
    friend class target_file;
};


}


#endif

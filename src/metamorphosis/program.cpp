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
 * @file        metamorphosis/program.cpp
 * @brief       program class implementation.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#include "get_c_str_hash.hpp"
#include "image_utils.hpp"
#include "number_name_component.hpp"
#include "program.hpp"
#include "sort_policies.hpp"
#include "sort_strategies.hpp"
#include "string_name_component.hpp"
#include "target_image.hpp"


namespace metamorphosis {


program::program(program_args&& prog_args)
        : prog_args_(std::move(prog_args))
        , name_componnts_()
        , target_fles_()
{
}


int program::execute()
{
    std::cout << spd::ios::set_white_text
              << "Searching target files..."
              << spd::ios::set_default_text
              << std::flush;
    
    if (!get_target_files())
    {
        std::cout << spd::ios::set_light_red_text
                  << "[fail]"
                  << spd::ios::set_default_text
                  << std::endl;
        
        return 1;
    }
    
    std::cout << spd::ios::set_light_green_text
              << "[ok]"
              << spd::ios::set_default_text
              << std::endl;
    
    sort_target_files();
    set_name_components();
    set_new_target_files_names();
    
    if (!rename_target_files())
    {
        std::cout << spd::ios::set_light_red_text
                  << "Errors were found during the renaming operation."
                  << spd::ios::set_default_text
                  << std::endl;
        
        return 1;
    }
    
    std::cout << spd::ios::set_light_green_text
              << "Operation completed successfully."
              << spd::ios::set_default_text
              << std::endl;
    
    return 0;
}


bool program::get_target_files()
{
    bool fnd = false;
    std::size_t image_wdth;
    std::size_t image_hght;
    std::shared_ptr<target_file> target_fle;
    std::shared_ptr<target_image> target_img;
    
    bool sorting_imgs = prog_args_.sort_polics.is_set(sort_policies::IMAGE_HEIGTH) ||
            prog_args_.sort_polics.is_set(sort_policies::IMAGE_WITH) ||
            prog_args_.sort_polics.is_set(sort_policies::IMAGE_SIZE);
    
    spd::fsys::directory_iteration target_directory_iteratn(prog_args_.target_directory_pth);
    target_directory_iteratn.regex_to_match(prog_args_.filter_regx)
                            .file_types(spd::sys::fsys::file_types::REGULAR_FILE)
                            .recursivity_level(0);
    
    for (auto& x : target_directory_iteratn)
    {
        if (sorting_imgs && get_image_size(x, &image_wdth, &image_hght))
        {
            target_fle = std::make_shared<target_image>(x, this, image_wdth, image_hght);
        }
        else
        {
            target_fle = std::make_shared<target_file>(x, this);
        }
        
        target_fles_.emplace_back(target_fle);
        target_fles_map_.insert({get_c_str_hash(x.c_str()), std::move(target_fle)});
        fnd = true;
    }
    
    return fnd;
}


void program::sort_target_files()
{
    if (prog_args_.sort_polics.is_set(sort_policies::ALPHABETICALLY))
    {
        std::sort(target_fles_.begin(), target_fles_.end(), sort_alphabeticaly);
    }
    if (prog_args_.sort_polics.is_set(sort_policies::IMAGE_WITH))
    {
        std::sort(target_fles_.begin(), target_fles_.end(), sort_by_image_with);
    }
    if (prog_args_.sort_polics.is_set(sort_policies::IMAGE_HEIGTH))
    {
        std::sort(target_fles_.begin(), target_fles_.end(), sort_by_image_height);
    }
    if (prog_args_.sort_polics.is_set(sort_policies::IMAGE_SIZE))
    {
        std::sort(target_fles_.begin(), target_fles_.end(), sort_by_image_size);
    }
}


void program::set_name_components()
{
    number_name_component::integral_type digit_cnt;
    std::unique_ptr<name_component> name_componnt;

    digit_cnt = spd::scals::count_digits(target_fles_.size());
    
    for (auto& x : prog_args_.string_name_componnts)
    {
        name_componnt = std::make_unique<string_name_component>(x, 0);
        name_componnts_.insert({name_componnt->get_absolute_priority(), std::move(name_componnt)});
    }
    
    if (prog_args_.number_name_componnts.empty())
    {
        name_componnts_.insert({0xFFFFFFFF00000001,
                std::make_unique<number_name_component>(1, digit_cnt, 0xFFFFFFFF)});
    }
    else
    {
        for (auto &x: prog_args_.number_name_componnts)
        {
            name_componnt = std::make_unique<number_name_component>(x, digit_cnt, 1);
            name_componnts_.insert(
                    {name_componnt->get_absolute_priority(), std::move(name_componnt)});
        }
    }
}


void program::set_new_target_files_names()
{
    for (auto& x : target_fles_)
    {
        x->set_new_file_name(get_next_target_file_name());
    }
}


program::string_type program::get_next_target_file_name()
{
    string_type nme;
    
    for (auto& x : name_componnts_)
    {
        nme += x.second->get_next_string();
    }
    
    return nme;
}


bool program::rename_target_files()
{
    bool succss = true;
    
    for (auto& x : target_fles_)
    {
        if (!x->rename())
        {
            succss = false;
        }
    }
    
    return succss;
}


std::shared_ptr<target_file> program::get_target_file(const std::filesystem::path& target_file_pth)
{
    auto it = target_fles_map_.find(get_c_str_hash(target_file_pth.c_str()));
    
    if (it == target_fles_map_.end())
    {
        return nullptr;
    }
    
    return it->second;
}


}

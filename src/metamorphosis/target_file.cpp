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
 * @file        metamorphosis/target_file.cpp
 * @brief       target_file implementation.
 * @author      Killian Valverde
 * @date        2024/10/24
 */

#include "target_file.hpp"


namespace metamorphosis {


bool target_file::rename()
{
    std::filesystem::path current_new_file_pth;
    std::error_code error_cde;
    
    if (dne_)
    {
        return rename_succss_;
    }
    else if (visitd_)
    {
        current_new_file_pth = "metamorphosis-tmp-file-name-";
        current_new_file_pth += std::to_string(spd::sys::fsys::get_file_inode(
                original_file_pth_.c_str()));
    }
    else
    {
        if (original_file_pth_ == new_file_pth_)
        {
            dne_ = true;
            rename_succss_ = true;
            print_ok_rename(new_file_pth_);
            return true;
        }
        
        visitd_ = true;
        std::shared_ptr<target_file> target_fle = progrm_->get_target_file(new_file_pth_);
        
        if (target_fle != nullptr)
        {
            target_fle->rename();
        }
        
        if (spd::sys::fsys::file_exists(new_file_pth_.c_str()))
        {
            goto exit_with_error;
        }
        
        current_new_file_pth = new_file_pth_;
    }
    
    std::filesystem::rename(original_file_pth_, current_new_file_pth, error_cde);
    if (error_cde)
    {
        goto exit_with_error;
    }
    
    dne_ = true;
    rename_succss_ = true;
    print_ok_rename(current_new_file_pth);
    original_file_pth_ = current_new_file_pth;
    return true;
    
exit_with_error:
    dne_ = true;
    print_fail_rename();
    return false;
}


}

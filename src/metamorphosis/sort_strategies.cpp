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
 * @file        metamorphosis/sort_strategies.cpp
 * @brief       sort_strategies implementation.
 * @author      Killian Valverde
 * @date        2024/10/24
 */

#include "sort_strategies.hpp"


namespace metamorphosis {


bool sort_alphabeticaly(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
)
{
    return rhs->get_original_file_path().native().compare(
            lhs->get_original_file_path().native()) < 0;
}


bool sort_by_image_with(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
)
{
    std::shared_ptr<target_image> img_rhs = std::dynamic_pointer_cast<target_image>(rhs);
    std::shared_ptr<target_image> img_lhs = std::dynamic_pointer_cast<target_image>(lhs);
    
    if (img_rhs == nullptr && img_lhs == nullptr)
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    if (img_rhs == nullptr)
    {
        return false;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    if (img_rhs->get_with() == img_lhs->get_with())
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    return img_rhs->get_with() > img_lhs->get_with();
}


bool sort_by_image_height(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
)
{
    std::shared_ptr<target_image> img_rhs = std::dynamic_pointer_cast<target_image>(rhs);
    std::shared_ptr<target_image> img_lhs = std::dynamic_pointer_cast<target_image>(lhs);
    
    if (img_rhs == nullptr && img_lhs == nullptr)
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    if (img_rhs == nullptr)
    {
        return false;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    if (img_rhs->get_height() == img_lhs->get_height())
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    return img_rhs->get_height() > img_lhs->get_height();
}


bool sort_by_image_size(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
)
{
    std::shared_ptr<target_image> img_rhs = std::dynamic_pointer_cast<target_image>(rhs);
    std::shared_ptr<target_image> img_lhs = std::dynamic_pointer_cast<target_image>(lhs);
    
    if (img_rhs == nullptr && img_lhs == nullptr)
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    if (img_rhs == nullptr)
    {
        return false;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    if (img_rhs->get_size() == img_lhs->get_size())
    {
        return sort_alphabeticaly(rhs, lhs);
    }

    return img_rhs->get_size() > img_lhs->get_size();
}


}

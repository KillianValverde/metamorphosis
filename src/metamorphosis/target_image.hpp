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
 * @file        metamorphosis/target_image.hpp
 * @brief       target_image header.
 * @author      Killian Valverde
 * @date        2024/10/24
 */

#ifndef METAMORPHOSIS_TARGET_IMAGE_HPP
#define METAMORPHOSIS_TARGET_IMAGE_HPP

#include "forward_declarations.hpp"
#include "program.hpp"
#include "target_file.hpp"


namespace metamorphosis {


class target_image : public target_file
{
public:
    template<typename TpPath_>
    target_image(
            TpPath_&& file_pth,
            program* prog,
            size_t wth,
            size_t hght
    )
            : target_file(std::forward<TpPath_>(file_pth), prog)
            , wth_(wth)
            , hght_(hght)
    {
    }
    
    [[nodiscard]] inline std::size_t get_with() const noexcept
    {
        return wth_;
    }
    
    [[nodiscard]] inline std::size_t get_height() const noexcept
    {
        return hght_;
    }
    
    [[nodiscard]] inline std::size_t get_size() const noexcept
    {
        return wth_ + hght_;
    }

private:
    std::size_t wth_;

    std::size_t hght_;
};


}


#endif

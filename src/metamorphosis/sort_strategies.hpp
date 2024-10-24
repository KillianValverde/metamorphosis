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
 * @file        metamorphosis/sort_strategies.hpp
 * @brief       sort_strategies header.
 * @author      Killian Valverde
 * @date        2024/10/24
 */

#ifndef METAMORPHOSIS_SORT_STRATEGIES_HPP
#define METAMORPHOSIS_SORT_STRATEGIES_HPP

#include "target_file.hpp"
#include "target_image.hpp"


namespace metamorphosis {


bool sort_alphabeticaly(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
);


bool sort_by_image_with(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
);


bool sort_by_image_height(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
);


bool sort_by_image_size(
        const std::shared_ptr<target_file>& rhs,
        const std::shared_ptr<target_file>& lhs
);


}


#endif

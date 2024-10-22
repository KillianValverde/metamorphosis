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
 * @file        metamorphosis_gtest/program_test.cpp
 * @brief       program unit test.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#include <gtest/gtest.h>

#include "metamorphosis/program.hpp"


TEST(metamorphosis_program, execute)
{
    int ret = -1;
    metamorphosis::program_args prog_args;
    
    metamorphosis::program prog(std::move(prog_args));
    
    EXPECT_NO_THROW(ret = prog.execute());
    EXPECT_TRUE(ret == 0);
}

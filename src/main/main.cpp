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
 * @file        main/main.hpp
 * @brief       main entry point.
 * @author      Killian Valverde
 * @date        2024/10/23
 */

#define SPEED_MULTIPLATFORM_MAIN_WITH_UNICODE_SUPPORT
#include <speed/speed.hpp>

#include "../metamorphosis/program.hpp"


int main(int argc, char* argv[])
{
    std::string messge;
    int retv;
    
    try 
    {
        metamorphosis::program_args prog_args;
        spd::ap::arg_parser ap("metamorphosis");
        
        ap.add_help_menu()
                .description("Rename a set of files following a specified patern.");

        ap.add_keyless_arg("DIR")
                .description("Directory in which perform the operation.")
                .store_into(&prog_args.target_directory_pth);

        ap.add_key_value_arg("--regex", "-x")
                .description("Case insensitive regex that all the files have to match in order "
                             "to be considered.")
                .store_into(&prog_args.filter_regx)
                .mandatory(true);

        ap.add_key_value_arg("--string", "-s")
                .description("Sting to set.")
                // .minmax_values(1, ~0ull)
                .store_into(&prog_args.string_name_componnts);

        ap.add_key_value_arg("--number", "-n")
                .description("Number to set.")
                // .minmax_values(1, ~0ull)
                .store_into(&prog_args.number_name_componnts)
                .values_with_prefix(true);

        ap.add_key_arg("--sort-alphabetically", "-sa")
                .description("Sort files alphabetically before renaming.")
                .action([&]() { prog_args.sort_polics.set(
                        metamorphosis::sort_policies::ALPHABETICALLY); });

        ap.add_key_arg("--sort-by-image-with", "-siw")
                .description("Sort files by image with before renaming.")
                .action([&]() { prog_args.sort_polics.set(
                        metamorphosis::sort_policies::IMAGE_WITH); });

        ap.add_key_arg("--sort-by-image-height", "-sih")
                .description("Sort files by image height before renaming.")
                .action([&]() { prog_args.sort_polics.set(
                        metamorphosis::sort_policies::IMAGE_HEIGTH); });

        ap.add_key_arg("--sort-by-image-size", "-sis")
                .description("Sort files by total image size before renaming.")
                .action([&]() { prog_args.sort_polics.set(
                        metamorphosis::sort_policies::IMAGE_SIZE); });
                
        ap.add_help_arg("--help", "-h")
                .description("Display this help and exit.");
                
        ap.add_version_arg("--version", "-v")
                .description("Output version information and exit.")
                .gplv3_version_information("0.0.0", "2024", "Killian Valverde");

        ap.parse_args(argc, argv);
        
        metamorphosis::program prog(std::move(prog_args));
        
        return prog.execute();
    }
    catch (const metamorphosis::exception_base& e)
    {
        messge = e.what();
        retv = 1;
    }
    catch (const std::exception& e)
    {
        messge = e.what();
        retv = -1;
    }
    catch (...)
    {
        messge = "Unknown error";
        retv = -1;
    }
    
    std::cerr << spd::ios::newl
              << spd::ios::set_light_red_text << "metamorphosis: "
              << spd::ios::set_default_text << messge
              << std::endl;

    return retv;
}

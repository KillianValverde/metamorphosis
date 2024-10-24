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
 * @file        metamorphosis/image_utils.hpp
 * @brief       image_utils header.
 * @author      Killian Valverde
 * @date        2024/05/20
 */

#include "image_utils.hpp"

#if defined(_WIN32)
#include <windows.h>
#include <wincodec.h>
#else
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif


namespace metamorphosis {


bool get_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept
{
#if defined(_WIN32)
    IWICImagingFactory* imaging_factry = nullptr;
    IWICBitmapDecoder* bitmap_decodr = nullptr;
    IWICBitmapFrameDecode* bitmap_frame_decd = nullptr;
    bool res = false;
    UINT tmp_wdth = 0;
    UINT tmp_hght = 0;
    HRESULT hres;
    
    hres = ::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (hres != S_OK && hres != S_FALSE)
    {
        return false;
    }
    
    hres = ::CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                              IID_PPV_ARGS(&imaging_factry));
    if (FAILED(hres))
    {
        goto cleanup;
    }
    
    hres = imaging_factry->CreateDecoderFromFilename(img_pth.c_str(), nullptr, GENERIC_READ,
            WICDecodeMetadataCacheOnDemand, &bitmap_decodr);
    if (FAILED(hres))
    {
        goto cleanup;
    }
    
    hres = bitmap_decodr->GetFrame(0, &bitmap_frame_decd);
    if (FAILED(hres))
    {
        goto cleanup;
    }

    hres = bitmap_frame_decd->GetSize(&tmp_wdth, &tmp_hght);
    if (SUCCEEDED(hres))
    {
        *wdth = static_cast<std::size_t>(tmp_wdth);
        *hght = static_cast<std::size_t>(tmp_hght);
        res = true;
    }

cleanup:
    if (bitmap_frame_decd != nullptr)
    {
        bitmap_frame_decd->Release();
    }
    if (bitmap_decodr != nullptr)
    {
        bitmap_decodr->Release();
    }
    if (imaging_factry != nullptr)
    {
        imaging_factry->Release();
    }
    // CoUninitialize();
    return res;
#else
    int tmp_wdth;
    int tmp_hght;
    int channels_in_fle;
    
    unsigned char* img = stbi_load(img_pth.c_str(), &tmp_wdth, &tmp_hght, &channels_in_fle, 0);
    if (img == nullptr)
    {
        return false;
    }

    *wdth = static_cast<std::size_t>(tmp_wdth);
    *hght = static_cast<std::size_t>(tmp_hght);

    stbi_image_free(img);

    return true;
#endif
}


}

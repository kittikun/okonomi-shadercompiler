// Copyright(c) 2015 Kitti Vongsay
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub license, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "dx12_constant_table.h"

namespace Okonomi
{
    // for Variable tuple
    constexpr uint_fast32_t OFFSET = 0;
    constexpr uint_fast32_t SIZE = 1;

    DX12ConstantTable::DX12ConstantTable(const std::string& name, uint_fast32_t size)
        : name_{ name }
    {
        // https://developer.nvidia.com/content/constant-buffers-without-constant-pain-0
        // All constant buffer data that is passed to XXSetConstantBuffers1() needs to be aligned to 256 byte boundaries.
        size = (size + 255) & ~255;

        data_.resize(size);
    }

    DX12ConstantTable::DX12ConstantTable(DX12ConstantTable&& other)
    {
    }

    void DX12ConstantTable::addVariable(const std::string& name, uint_fast32_t offset, uint_fast32_t size)
    {
        offsetMap_.insert(std::make_pair(name, std::make_tuple(offset, size)));
    }
} // namespace Okonomi
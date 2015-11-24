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

#pragma once

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Okonomi
{
    class DX12ConstantTable
    {
        DX12ConstantTable(const DX12ConstantTable&) = delete;
        DX12ConstantTable& operator=(const DX12ConstantTable&) = delete;
        DX12ConstantTable& operator=(DX12ConstantTable&&) = delete;
    public:
        DX12ConstantTable(const std::string&, uint_fast32_t);
        DX12ConstantTable(DX12ConstantTable&&);

        using Variable = std::tuple<uint_fast32_t, uint_fast32_t>;

    private:
        void addVariable(const std::string&, uint_fast32_t, uint_fast32_t);

    private:
        std::string name_;
        std::vector<uint8_t> data_;
        std::unordered_map<std::string, Variable> offsetMap_;     // not thread-safe but should be ok

        friend class DX12ShaderParser;
    };
} // namespace Okonomi